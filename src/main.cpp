/**
 * Estación Meteorológica Inteligente — Código Definitivo Integrado
 * Proyecto final para el trayecto NovaMakers Avanzado (9 a 12 años)
 * 
 * Descripción: Integra lectura de temperatura y humedad (DHT11),
 * calidad del aire (MQ-135), visualización en LCD I2C con iconos personalizados
 * y rotación de pantallas, control de semáforo ambiental (LEDs) y alertas
 * acústicas (buzzer pasivo), y envío de datos formateados como CSV por
 * el puerto serie para análisis científico en planillas de cálculo.
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>

// ==========================================
// ⚙️ CONFIGURACIÓN DE PINES
// ==========================================
#define DHTPIN 2
#define DHTTYPE DHT11
#define MQ_PIN A0

#define LED_VERDE 8
#define LED_AMARILLO 9
#define LED_ROJO 10
#define BUZZER_PIN 3

// ==========================================
// 📊 CONSTANTES Y UMBRALES CONFIGURABLES
// ==========================================
const float TEMP_LIMITE_ALTA = 35.0;      // Umbral advertencia calor (Celsius)
const float TEMP_LIMITE_CRITICA = 40.0;    // Umbral peligro calor extremo (Celsius)
const float HUM_LIMITE_ALTA = 80.0;       // Umbral advertencia humedad (%)
const int AIRE_LIMITE_CRITICO = 350;       // Umbral peligro gases (MQ-135 crudo)

const unsigned long TIEMPO_ROTACION = 3000; // Tiempo alternar pantalla LCD (ms)
const unsigned long INTERVALO_CSV = 5000;   // Intervalo de registro serial CSV (ms)

// ==========================================
// 🔌 OBJETOS Y VARIABLES GLOBALES
// ==========================================
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

// Variables físicas
float temperatura = 0.0;
float humedad = 0.0;
float sensacion = 0.0;
int gasCrudo = 0;

// Tiempos de software
unsigned long tiempoUltimoCambio = 0;
unsigned long tiempoUltimoRegistro = 0;
unsigned long segundosTranscurridos = 0;
bool mostrarPantallaSecundaria = false; 

// ==========================================
// 🎨 CARACTERES CUSTOM (ICONOS)
// ==========================================
byte iconoTermometro[8] = { B00100, B01010, B01010, B01010, B01110, B11111, B11111, B01110 };
byte iconoGota[8]       = { B00100, B00100, B01010, B01010, B10001, B10001, B10001, B01110 };
byte iconoGrado[8]      = { B00110, B01001, B01001, B00110, B00000, B00000, B00000, B00000 };
byte iconoRostroFeliz[8] = { B00000, B01010, B00000, B00000, B10001, B01110, B00000, B00000 };

// Declaración de funciones modulares
void leerSensores();
void controlarAlertas();
void actualizarLcd();
void registrarCsv();
void emitirPito(int duracion, int frecuencia);
void apagarSemaforo();

// ==========================================
// ▶️ SETUP (CONFIGURACIÓN INICIAL)
// ==========================================
void setup() {
  // Inicializamos comunicación serie para registro CSV
  Serial.begin(9600);
  
  dht.begin();
  
  lcd.begin(16, 2);
  
  // Guardamos caracteres custom en el LCD
  lcd.createChar(0, iconoTermometro);
  lcd.createChar(1, iconoGota);
  lcd.createChar(2, iconoGrado);
  lcd.createChar(3, iconoRostroFeliz);
  
  // Configuración de pines de actuadores
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Test inicial de luces
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_AMARILLO, HIGH);
  digitalWrite(LED_ROJO, HIGH);
  delay(500);
  apagarSemaforo();
  
  // Cabecera del archivo CSV por puerto Serial
  Serial.println(F("Tiempo(s),Temperatura(C),Humedad(%),CalidadAire(Crudo)"));
  
  // Mensaje de bienvenida en el LCD
  lcd.setCursor(0, 0);
  lcd.print("Estacion Meteo");
  lcd.setCursor(0, 1);
  lcd.print("NovaMaker Final");
  delay(1500);
  lcd.clear();
}

// ==========================================
// 🔄 LOOP (CICLO CONTINUO)
// ==========================================
void loop() {
  leerSensores();
  controlarAlertas();
  
  // Alternancia de pantallas en el LCD sin detener el loop
  if (millis() - tiempoUltimoCambio >= TIEMPO_ROTACION) {
    mostrarPantallaSecundaria = !mostrarPantallaSecundaria;
    tiempoUltimoCambio = millis();
    lcd.clear();
  }
  actualizarLcd();
  
  // Registro de datos por puerto Serie
  registrarCsv();
  
  delay(200); // Frecuencia de ciclo de la CPU
}

// ==========================================
// 📦 DESARROLLO DE FUNCIONES MODULARES
// ==========================================

void leerSensores() {
  temperatura = dht.readTemperature();
  humedad = dht.readHumidity();
  sensacion = dht.computeHeatIndex(temperatura, humedad, false);
  gasCrudo = analogRead(MQ_PIN);
}

void controlarAlertas() {
  // Caso de error en sensores
  if (isnan(temperatura) || isnan(humedad)) {
    apagarSemaforo();
    digitalWrite(LED_AMARILLO, HIGH);
    return;
  }
  
  // 1. Peligro (Rojo)
  if (temperatura >= TEMP_LIMITE_CRITICA || gasCrudo >= AIRE_LIMITE_CRITICO) {
    apagarSemaforo();
    digitalWrite(LED_ROJO, HIGH);
    emitirPito(100, 2500); // Pitidos cortos y agudos (agresivo)
  }
  // 2. Advertencia (Amarillo)
  else if (temperatura >= TEMP_LIMITE_ALTA || humedad >= HUM_LIMITE_ALTA) {
    apagarSemaforo();
    digitalWrite(LED_AMARILLO, HIGH);
    emitirPito(300, 1000); // Pitido más largo y grave (moderado)
  }
  // 3. Normal (Verde)
  else {
    apagarSemaforo();
    digitalWrite(LED_VERDE, HIGH);
  }
}

void actualizarLcd() {
  // Caso de error
  if (isnan(temperatura) || isnan(humedad)) {
    lcd.setCursor(0, 0);
    lcd.print("Error Lectura!");
    lcd.setCursor(0, 1);
    lcd.print("Chequear Cables");
    return;
  }
  
  if (!mostrarPantallaSecundaria) {
    // Pantalla 1: Temperatura y Humedad
    lcd.setCursor(0, 0);
    lcd.write((uint8_t)0); // Icono termómetro
    lcd.print(" Temp: ");
    lcd.print(temperatura, 1);
    lcd.write((uint8_t)2); // Simbolo de grado
    lcd.print("C");
    
    lcd.setCursor(0, 1);
    lcd.write((uint8_t)1); // Icono gota
    lcd.print(" Hum:  ");
    lcd.print(humedad, 1);
    lcd.print(" %");
  } else {
    // Pantalla 2: Calidad Aire y Sensación Térmica
    lcd.setCursor(0, 0);
    lcd.print("Aire: ");
    lcd.print(gasCrudo);
    
    if (gasCrudo < 250) {
      lcd.print(" OK ");
      lcd.write((uint8_t)3); // Carita feliz
    } else if (gasCrudo >= 250 && gasCrudo < AIRE_LIMITE_CRITICO) {
      lcd.print(" REG");
    } else {
      lcd.print(" MAL!");
    }
    
    lcd.setCursor(0, 1);
    lcd.print("Sens.T: ");
    lcd.print(sensacion, 1);
    lcd.write((uint8_t)2);
    lcd.print("C");
  }
}

void registrarCsv() {
  if (millis() - tiempoUltimoRegistro >= INTERVALO_CSV) {
    tiempoUltimoRegistro = millis();
    segundosTranscurridos = tiempoUltimoRegistro / 1000;
    
    if (!isnan(temperatura) && !isnan(humedad)) {
      Serial.print(segundosTranscurridos);
      Serial.print(F(","));
      Serial.print(temperatura, 1);
      Serial.print(F(","));
      Serial.print(humedad, 1);
      Serial.print(F(","));
      Serial.println(gasCrudo);
    }
  }
}

void emitirPito(int duracion, int frecuencia) {
  static unsigned long ultimoSonido = 0;
  // Controlamos no pisar el buzzer constantemente con delay()
  if (millis() - ultimoSonido >= (duracion + 500)) {
    tone(BUZZER_PIN, frecuencia, duracion);
    ultimoSonido = millis();
  }
}

void apagarSemaforo() {
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);
}
