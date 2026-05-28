/**
 * Sesión 7: Registro de Datos y Análisis
 * Proyecto: Estación Meteorológica Inteligente
 * Trayecto: NovaMakers Avanzado (9 a 12 años)
 * 
 * Descripción: Modifica el código final para transmitir los datos medidos
 * por puerto serie estructurados como texto plano separado por comas (formato CSV).
 * Los datos se envían de forma automática en un intervalo configurable para
 * permitir que los estudiantes los recopilen mediante el Monitor Serial, los copien,
 * y los peguen en herramientas como Microsoft Excel o Google Sheets para trazar
 * gráficos de tendencias y analizar series temporales.
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
// 📊 INTERVALO DE MUESTREO (PARA REGISTRO)
// ==========================================
// Para pruebas en el aula, registramos datos cada 5 segundos (5000 ms).
// En una estación real, esto podría configurarse cada 5 minutos (300000 ms).
const unsigned long INTERVALO_CSV = 5000; 

// ==========================================
// 🔌 OBJETOS Y VARIABLES GLOBALES
// ==========================================
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

unsigned long tiempoUltimoRegistro = 0;
unsigned long segundosTranscurridos = 0;

void setup() {
  // Iniciamos puerto Serie a 9600 baudios. Es crítico que coincida en Excel/Sheets.
  Serial.begin(9600);
  
  dht.begin();
  lcd.begin(16, 2);
  
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Imprimimos el encabezado CSV en la primera línea.
  // Esto le indicará a las planillas de cálculo los nombres de cada columna.
  Serial.println(F("Tiempo(s),Temperatura(C),Humedad(%),CalidadAire(Analogico)"));
  
  lcd.setCursor(0, 0);
  lcd.print("Registrador CSV");
  lcd.setCursor(0, 1);
  lcd.print("Iniciado... OK");
  delay(1500);
  lcd.clear();
}

void loop() {
  // Leemos las variables
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int aire = analogRead(MQ_PIN);
  
  // Manejo de Alertas del Semáforo (Verde / Amarillo / Rojo)
  if (isnan(temp) || isnan(hum)) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARILLO, HIGH);
    digitalWrite(LED_ROJO, LOW);
  } else if (temp >= 40.0 || aire >= 350) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARILLO, LOW);
    digitalWrite(LED_ROJO, HIGH);
  } else if (temp >= 35.0 || hum >= 80.0) {
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_AMARILLO, HIGH);
    digitalWrite(LED_ROJO, LOW);
  } else {
    digitalWrite(LED_VERDE, HIGH);
    digitalWrite(LED_AMARILLO, LOW);
    digitalWrite(LED_ROJO, LOW);
  }

  // Actualización del LCD local (Muestra básica de variables)
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temp, 1);
  lcd.print("C H:");
  lcd.print(hum, 0);
  lcd.print("% ");
  lcd.setCursor(0, 1);
  lcd.print("Aire: ");
  lcd.print(aire);
  lcd.print("     ");

  // REGISTRO DE DATOS: Verificamos si ya pasó el tiempo de intervalo
  if (millis() - tiempoUltimoRegistro >= INTERVALO_CSV) {
    tiempoUltimoRegistro = millis();
    segundosTranscurridos = tiempoUltimoRegistro / 1000;
    
    // Imprimimos la fila de datos formateados con comas (CSV)
    if (!isnan(temp) && !isnan(hum)) {
      Serial.print(segundosTranscurridos);
      Serial.print(F(","));
      Serial.print(temp, 1);
      Serial.print(F(","));
      Serial.print(hum, 1);
      Serial.print(F(","));
      Serial.println(aire);
    }
  }
}
