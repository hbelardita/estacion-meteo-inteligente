/**
 * Sesión 5: Alertas Ambientales — Semáforo y Sonidos
 * Proyecto: Estación Meteorológica Inteligente
 * Trayecto: NovaMakers Avanzado (9 a 12 años)
 * 
 * Descripción: Integra sensores (DHT11 y MQ-135) y actuadores (LEDs y Buzzer)
 * para crear un sistema de alerta ambiental multinivel. El código toma decisiones
 * lógicas basadas en umbrales definidos y reacciona de tres maneras:
 * - Verde (Seguro): Sin alertas.
 * - Amarillo (Advertencia): Problema moderado (calor o humedad alta), pitido lento.
 * - Rojo (Peligro): Problema grave (temperatura extrema o humo), pitido rápido.
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>

// Definición de pines de Sensores
#define DHTPIN 2
#define DHTTYPE DHT11
#define MQ_PIN A0

// Definición de pines de Actuadores (Semáforo + Buzzer)
#define LED_VERDE 8
#define LED_AMARILLO 9
#define LED_ROJO 10
#define BUZZER_PIN 3

// Inicialización de componentes
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

// Umbrales de Alerta
const float LIMITE_TEMP_ADVERTENCIA = 35.0; // En grados Celsius
const float LIMITE_TEMP_PELIGRO = 40.0;     // En grados Celsius
const float LIMITE_HUM_ADVERTENCIA = 80.0;  // En porcentaje
const int UMBRAL_AIRE_PELIGRO = 350;        // Lectura analógica MQ-135

void setup() {
  // Inicialización de sensores
  dht.begin();
  
  // Inicialización del LCD
  lcd.begin(16, 2);
  
  // Configuración de pines de actuadores como SALIDA
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Encendemos todos los LEDs un instante al inicio para testear el circuito (Test de Lámparas)
  digitalWrite(LED_VERDE, HIGH);
  digitalWrite(LED_AMARILLO, HIGH);
  digitalWrite(LED_ROJO, HIGH);
  delay(500);
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);
}

// Función auxiliar para emitir pitidos con el Buzzer pasivo
void sonarBuzzer(int duracion, int frecuencia, int repeticiones) {
  for (int i = 0; i < repeticiones; i++) {
    tone(BUZZER_PIN, frecuencia, duracion);
    delay(duracion + 50); // Tiempo del sonido + silencio
  }
}

// Función para apagar todos los LEDs del semáforo
void apagarSemaforo() {
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_ROJO, LOW);
}

void loop() {
  // Leemos sensores
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int aire = analogRead(MQ_PIN);

  // Si hay error en sensores, mostramos advertencia y parpadeamos luces
  if (isnan(temp) || isnan(hum)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error Lectura!");
    lcd.setCursor(0, 1);
    lcd.print("Revisa Sensores");
    
    // Parpadeo de LEDs para llamar la atención del técnico
    digitalWrite(LED_AMARILLO, HIGH);
    delay(500);
    digitalWrite(LED_AMARILLO, LOW);
    delay(500);
    return;
  }

  lcd.clear();

  // EVALUACIÓN DE NIVELES DE ALERTA (De mayor peligro a menor peligro)
  
  // CASO A: PELIGRO (Nivel Rojo)
  // Se activa si la temperatura supera los 40°C o la calidad del aire supera el umbral crítico.
  if (temp >= LIMITE_TEMP_PELIGRO || aire >= UMBRAL_AIRE_PELIGRO) {
    apagarSemaforo();
    digitalWrite(LED_ROJO, HIGH);
    
    lcd.setCursor(0, 0);
    lcd.print("ALERTA: PELIGRO");
    lcd.setCursor(0, 1);
    if (temp >= LIMITE_TEMP_PELIGRO) {
      lcd.print("Temp Extrema: ");
      lcd.print(temp, 0);
    } else {
      lcd.print("Aire Contaminado");
    }
    
    // Pitido rápido y agudo
    sonarBuzzer(100, 2000, 2); 
  }
  // CASO B: ADVERTENCIA (Nivel Amarillo)
  // Se activa si la temperatura supera 35°C o la humedad supera el 80% (pero no estamos en peligro).
  else if (temp >= LIMITE_TEMP_ADVERTENCIA || hum >= LIMITE_HUM_ADVERTENCIA) {
    apagarSemaforo();
    digitalWrite(LED_AMARILLO, HIGH);
    
    lcd.setCursor(0, 0);
    lcd.print("ATENCION: AVISO");
    lcd.setCursor(0, 1);
    if (temp >= LIMITE_TEMP_ADVERTENCIA) {
      lcd.print("Calor: ");
      lcd.print(temp, 0);
      lcd.print("C");
    } else {
      lcd.print("Humedad Alta: ");
      lcd.print(hum, 0);
      lcd.print("%");
    }
    
    // Pitido lento
    sonarBuzzer(300, 1000, 1);
  }
  // CASO C: SEGURO (Nivel Verde)
  // Todo está dentro de los límites seguros.
  else {
    apagarSemaforo();
    digitalWrite(LED_VERDE, HIGH);
    
    // Mostramos los valores normales de la estación
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(temp, 1);
    lcd.print("C  H:");
    lcd.print(hum, 0);
    lcd.print("%");
    
    lcd.setCursor(0, 1);
    lcd.print("Estado: NORMAL ");
  }

  // Esperamos 2 segundos antes de volver a verificar el ambiente
  delay(2000);
}
