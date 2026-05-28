/**
 * Sesión 6: Ensamblado y Código Definitivo Modular
 * Proyecto: Estación Meteorológica Inteligente
 * Trayecto: NovaMakers Avanzado (9 a 12 años)
 * 
 * Descripción: Esta es la versión limpia, ordenada y modular del software
 * de la estación. Agrupa el código en funciones específicas (lectura, visualización,
 * control de alertas) y utiliza constantes claras en la parte superior para
 * facilitar que los estudiantes calibren y personalicen sus estaciones sin
 * romper la lógica del programa. Incluye rotación de pantallas en el LCD
 * y caracteres personalizados para íconos.
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>

// ==========================================
// ⚙️ CONFIGURACIÓN DE PINES Y SENSORES
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
const float TEMP_LIMITE_ALTA = 35.0;   // Umbral advertencia calor (Celsius)
const float TEMP_LIMITE_CRITICA = 40.0; // Umbral peligro calor extremo (Celsius)
const float HUM_LIMITE_ALTA = 80.0;    // Umbral advertencia humedad (%)
const int AIRE_LIMITE_CRITICO = 350;    // Umbral peligro gases (MQ-135 crudo)

const unsigned long TIEMPO_ROTACION = 3000; // Tiempo para alternar pantallas (ms)

// ==========================================
// 🔌 OBJETOS Y VARIABLES GLOBALES
// ==========================================
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

// Variables para almacenar las mediciones actuales
float temperatura = 0.0;
float humedad = 0.0;
float sensacion = 0.0;
int gasCrudo = 0;

// Variables de tiempo para alternar la pantalla sin bloquear con delay()
unsigned long tiempoUltimoCambio = 0;
bool mostrarPantallaSecundaria = false; 

// ==========================================
// 🎨 CARACTERES CUSTOM (ICONOS)
// ==========================================
byte iconoTermometro[8] = { B00100, B01010, B01010, B01010, B01110, B11111, B11111, B01110 };
byte iconoGota[8]       = { B00100, B00100, B01010, B01010, B10001, B10001, B10001, B01110 };
byte iconoGrado[8]      = { B00110, B01001, B01001, B00110, B00000, B00000, B00000, B00000 };
byte iconoRostroFeliz[8] = { B00000, B01010, B00000, B00000, B10001, B01110, B00000, B00000 };

// ==========================================
// 🛠️ DECLARACIÓN DE FUNCIONES PROPIAS
// ==========================================
void leerSensores();
void actualizarLcd();
void controlarAlertas();
void emitirPito(int duracion, int frecuencia, int pausas);
void apagarSemaforo();

// ==========================================
// ▶️ SETUP (CONFIGURACIÓN INICIAL)
// ==========================================
void setup() {
  Serial.begin(9600);
  dht.begin();
  
  lcd.begin(16, 2);
  
  // Guardamos los caracteres custom en el LCD
  lcd.createChar(0, iconoTermometro);
  lcd.createChar(1, iconoGota);
  lcd.createChar(2, iconoGrado);
  lcd.createChar(3, iconoRostroFeliz);
  
  // Configuración de actuadores
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Saludo de inicio en LCD
  lcd.setCursor(0, 0);
  lcd.print("Estacion Meteo");
  lcd.setCursor(0, 1);
  lcd.print("NovaMaker S6 v1.0");
  emitirPito(100, 1500, 2);
  delay(1500);
  lcd.clear();
}

// ==========================================
// 🔄 LOOP (CICLO CONTINUO)
// ==========================================
void loop() {
  // 1. Leer datos de los sensores
  leerSensores();
  
  // 2. Controlar semáforo y emitir advertencias acústicas
  controlarAlertas();
  
  // 3. Manejo inteligente de la visualización en pantalla
  if (millis() - tiempoUltimoCambio >= TIEMPO_ROTACION) {
    mostrarPantallaSecundaria = !mostrarPantallaSecundaria;
    tiempoUltimoCambio = millis();
    lcd.clear();
  }
  actualizarLcd();
  
  // Pequeña espera para no sobrecargar el microcontrolador
  delay(200);
}

// ==========================================
// 📦 DESARROLLO DE FUNCIONES MODULARES
// ==========================================

// Función para obtener datos actualizados
void leerSensores() {
  temperatura = dht.readTemperature();
  humedad = dht.readHumidity();
  sensacion = dht.computeHeatIndex(temperatura, humedad, false);
  gasCrudo = analogRead(MQ_PIN);
}

// Función de control del Semáforo y Alertas
void controlarAlertas() {
  // Caso de Fallo de Sensores
  if (isnan(temperatura) || isnan(humedad)) {
    apagarSemaforo();
    digitalWrite(LED_AMARILLO, HIGH); // Luz amarilla encendida como falla técnica
    return;
  }
  
  // 1. Nivel de Alerta Roja (Peligro)
  if (temperatura >= TEMP_LIMITE_CRITICA || gasCrudo >= AIRE_LIMITE_CRITICO) {
    apagarSemaforo();
    digitalWrite(LED_ROJO, HIGH);
    emitirPito(80, 2500, 1); // Sonido rápido y agudo
  } 
  // 2. Nivel de Alerta Amarilla (Advertencia)
  else if (temperatura >= TEMP_LIMITE_ALTA || humedad >= HUM_LIMITE_ALTA) {
    apagarSemaforo();
    digitalWrite(LED_AMARILLO, HIGH);
    emitirPito(250, 1000, 0); // Sonido lento
  } 
  // 3. Nivel Verde (Clima Óptimo)
  else {
    apagarSemaforo();
    digitalWrite(LED_VERDE, HIGH);
  }
}

// Función para actualizar los datos en el LCD
void actualizarLcd() {
  // Caso de error
  if (isnan(temperatura) || isnan(humedad)) {
    lcd.setCursor(0, 0);
    lcd.print("Error Lectura!");
    lcd.setCursor(0, 1);
    lcd.print("Chequear cables");
    return;
  }
  
  // Pantalla Principal: Temp, Humedad y Confort
  if (!mostrarPantallaSecundaria) {
    // Fila 0: Temp
    lcd.setCursor(0, 0);
    lcd.write((uint8_t)0); // Icono termómetro
    lcd.print(" Temp: ");
    lcd.print(temperatura, 1);
    lcd.write((uint8_t)2); // Grado
    lcd.print("C");
    
    // Fila 1: Humedad
    lcd.setCursor(0, 1);
    lcd.write((uint8_t)1); // Icono gota
    lcd.print(" Hum:  ");
    lcd.print(humedad, 1);
    lcd.print(" %");
  } 
  // Pantalla Secundaria: Calidad del aire y Sensación Térmica
  else {
    // Fila 0: Calidad de Aire
    lcd.setCursor(0, 0);
    lcd.print("Aire: ");
    lcd.print(gasCrudo);
    
    if (gasCrudo < 250) {
      lcd.print(" OK ");
      lcd.write((uint8_t)3); // Rostro feliz
    } else if (gasCrudo >= 250 && gasCrudo < AIRE_LIMITE_CRITICO) {
      lcd.print(" REG"); // Aire regular
    } else {
      lcd.print(" MAL!"); // Calidad mala
    }
    
    // Fila 1: Sensación Térmica (ST)
    lcd.setCursor(0, 1);
    lcd.print("Sens.T: ");
    lcd.print(sensacion, 1);
    lcd.write((uint8_t)2);
    lcd.print("C");
  }
}

// Emite sonidos sin bloquear totalmente el código
void emitirPito(int duracion, int frecuencia, int pausas) {
  // Usamos variables de tiempo de software para el control acústico no bloqueante
  static unsigned long ultimoPito = 0;
  if (millis() - ultimoPito >= (duracion + 300 + (pausas * 100))) {
    tone(BUZZER_PIN, frecuencia, duracion);
    ultimoPito = millis();
  }
}

void apagarSemaforo() {
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);
}
