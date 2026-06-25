/**
 * Estación Meteorológica Inteligente — Código Definitivo Integrado (ESP32 - Faniot Kitmaker 2.0)
 * Proyecto final para el trayecto NovaMakers Avanzado
 *
 * Descripción: Integra lectura de temperatura y humedad (HTU21D),
 * luz ambiente (TEMT6000), y humedad de suelo (Analógico).
 * Visualización en OLED I2C 128x64. Control de semáforo ambiental con Neopíxeles
 * y alertas acústicas (buzzer pasivo). Envío de datos como CSV.
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_NeoPixel.h>

// ==========================================
// ⚙️ CONFIGURACIÓN DE PINES Y HARDWARE
// ==========================================
#define LUZ_PIN 39           // TEMT6000 en Kitmaker 2.0
#define SUELO_PIN 34         // Pin de expansión sugerido para sensor de humedad de suelo
#define BUZZER_PIN 12        // Buzzer en Kitmaker 2.0
#define NEOPIXEL_PIN 27      // Neopíxeles en Kitmaker 2.0
#define NUMPIXELS 4

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// ==========================================
// 📊 CONSTANTES Y UMBRALES CONFIGURABLES
// ==========================================
const float TEMP_LIMITE_ALTA = 35.0;
const float TEMP_LIMITE_CRITICA = 40.0;
const int SUELO_LIMITE_BAJO = 40;         // % de humedad de suelo (Advertencia)
const int SUELO_LIMITE_CRITICO = 20;      // % de humedad de suelo (Peligro, muy seco)

// Valores de calibración para la humedad de suelo (12 bits ADC: 0-4095)
// Ajustar estos valores según las lecturas reales del sensor en seco y sumergido
const int VALOR_SECO = 4095;
const int VALOR_HUMEDO = 1000;

const unsigned long INTERVALO_CSV = 5000;   // Intervalo de registro serial CSV (ms)

// ==========================================
// 🔌 OBJETOS Y VARIABLES GLOBALES
// ==========================================
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_HTU21DF htu = Adafruit_HTU21DF();
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Variables físicas
float temperatura = 0.0;
float humedadAmbiente = 0.0;
int luzCruda = 0;
int porcentajeLuz = 0;
int sueloCrudo = 0;
int porcentajeSuelo = 0;

// Tiempos de software
unsigned long tiempoUltimoRegistro = 0;
unsigned long segundosTranscurridos = 0;

// Declaración de funciones modulares
void leerSensores();
void controlarAlertas();
void actualizarOLED();
void registrarCsv();
void emitirPito(int duracion, int frecuencia);
void apagarSemaforo();
void encenderSemaforo(uint32_t color);

// ==========================================
// ▶️ SETUP (CONFIGURACIÓN INICIAL)
// ==========================================
void setup() {
  Serial.begin(115200);

  // Inicializar I2C para HTU21D y OLED
  Wire.begin();

  if (!htu.begin()) {
    Serial.println("No se encontró el sensor HTU21D!");
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Fallo al iniciar pantalla OLED");
  }

  pixels.begin();
  pixels.setBrightness(50); // Brillo de los LEDs (0-255)
  pixels.show(); // Apagar todos inicialmente

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LUZ_PIN, INPUT);
  pinMode(SUELO_PIN, INPUT);

  // Test inicial de luces
  encenderSemaforo(pixels.Color(255, 255, 255)); // Blanco
  delay(500);
  apagarSemaforo();

  // Cabecera del archivo CSV por puerto Serial
  Serial.println(F("Tiempo(s),Temperatura(C),HumAmbiente(%),Luz(%),HumSuelo(%)"));

  // Mensaje de bienvenida en el OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println(F(" Estacion Meteo"));
  display.setCursor(0, 35);
  display.println(F(" RED MAKER"));
  display.display();
  delay(2000);
}

// ==========================================
// 🔄 LOOP (CICLO CONTINUO)
// ==========================================
void loop() {
  leerSensores();
  controlarAlertas();
  actualizarOLED();
  registrarCsv();

  delay(200); // Frecuencia de ciclo de la CPU
}

// ==========================================
// 📦 DESARROLLO DE FUNCIONES MODULARES
// ==========================================

void leerSensores() {
  temperatura = htu.readTemperature();
  humedadAmbiente = htu.readHumidity();

  luzCruda = analogRead(LUZ_PIN);
  porcentajeLuz = map(luzCruda, 0, 4095, 0, 100);
  porcentajeLuz = constrain(porcentajeLuz, 0, 100);

  sueloCrudo = analogRead(SUELO_PIN);
  // Mapear la lectura invertida típica de sensores resistivos/capacitivos
  porcentajeSuelo = map(sueloCrudo, VALOR_SECO, VALOR_HUMEDO, 0, 100);
  porcentajeSuelo = constrain(porcentajeSuelo, 0, 100);
}

void controlarAlertas() {
  // 1. Peligro (Rojo): Temperatura extrema o suelo muy seco
  if (temperatura >= TEMP_LIMITE_CRITICA || porcentajeSuelo <= SUELO_LIMITE_CRITICO) {
    encenderSemaforo(pixels.Color(255, 0, 0)); // Rojo
    emitirPito(100, 2500);
  }
  // 2. Advertencia (Amarillo): Temperatura alta o suelo secándose
  else if (temperatura >= TEMP_LIMITE_ALTA || porcentajeSuelo <= SUELO_LIMITE_BAJO) {
    encenderSemaforo(pixels.Color(255, 150, 0)); // Amarillo/Naranja
    emitirPito(300, 1000);
  }
  // 3. Normal (Verde)
  else {
    encenderSemaforo(pixels.Color(0, 255, 0)); // Verde
  }
}

void actualizarOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Título
  display.setCursor(0, 0);
  display.print(F("--- DATOS ACTUALES ---"));

  // Temperatura
  display.setCursor(0, 15);
  display.print(F("Temp: "));
  if (isnan(temperatura) || temperatura > 120.0) display.print(F("Error"));
  else {
    display.print(temperatura, 1);
    display.print(F(" C"));
  }

  // Humedad Ambiente
  display.setCursor(0, 27);
  display.print(F("Hum Amb: "));
  if (isnan(humedadAmbiente) || humedadAmbiente > 100.0) display.print(F("Error"));
  else {
    display.print(humedadAmbiente, 1);
    display.print(F(" %"));
  }

  // Humedad del Suelo
  display.setCursor(0, 39);
  display.print(F("Hum Suelo: "));
  display.print(porcentajeSuelo);
  display.print(F(" %"));

  // Luz
  display.setCursor(0, 51);
  display.print(F("Luz: "));
  display.print(porcentajeLuz);
  display.print(F(" %"));

  display.display();
}

void registrarCsv() {
  if (millis() - tiempoUltimoRegistro >= INTERVALO_CSV) {
    tiempoUltimoRegistro = millis();
    segundosTranscurridos = tiempoUltimoRegistro / 1000;

    Serial.print(segundosTranscurridos);
    Serial.print(F(","));
    Serial.print(temperatura, 1);
    Serial.print(F(","));
    Serial.print(humedadAmbiente, 1);
    Serial.print(F(","));
    Serial.print(porcentajeLuz);
    Serial.print(F(","));
    Serial.println(porcentajeSuelo);
  }
}

void emitirPito(int duracion, int frecuencia) {
  static unsigned long ultimoSonido = 0;
  if (millis() - ultimoSonido >= (duracion + 500)) {
    tone(BUZZER_PIN, frecuencia, duracion);
    ultimoSonido = millis();
  }
}

void apagarSemaforo() {
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

void encenderSemaforo(uint32_t color) {
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}
