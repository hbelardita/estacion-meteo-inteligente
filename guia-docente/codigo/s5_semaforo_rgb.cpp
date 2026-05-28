// Sesión 5 (Variante) — Semáforo Ambiental con LED RGB
// Componentes: DHT11 (Temp/Hum), MQ-135 (Calidad Aire), LED RGB Cátodo Común y Buzzer.

#include <Arduino.h>
#include <DHT.h>

// Configuración de pines de sensores
#define DHTPIN 2
#define DHTTYPE DHT11
#define MQ_PIN A0

// Configuración de pines para el LED RGB
#define PIN_ROJO 8
#define PIN_VERDE 9
#define PIN_AZUL 10
#define BUZZER_PIN 3

// Umbrales configurables
const float TEMP_UMBRAL_ALTA = 35.0;      // Alerta amarilla por calor
const float TEMP_UMBRAL_CRITICA = 40.0;    // Alerta roja por calor extremo
const float HUM_UMBRAL_ALTA = 80.0;       // Alerta amarilla por humedad alta
const int AIRE_UMBRAL_CRITICO = 350;       // Alerta roja por gas (MQ-135 crudo)

DHT dht(DHTPIN, DHTTYPE);

// Declaración de funciones para controlar los colores del LED RGB
void encenderColor(bool r, bool g, bool b);
void emitirAlertaSonora(int duracion, int frecuencia);

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  // Configuramos los pines del LED RGB y Buzzer como salidas
  pinMode(PIN_ROJO, OUTPUT);
  pinMode(PIN_VERDE, OUTPUT);
  pinMode(PIN_AZUL, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Test inicial de colores: Rojo -> Verde -> Azul -> Apagado
  encenderColor(true, false, false); // Rojo
  delay(300);
  encenderColor(false, true, false); // Verde
  delay(300);
  encenderColor(false, false, true); // Azul
  delay(300);
  encenderColor(false, false, false); // Apagado
  
  Serial.println("=== Semaforo Ambiental (Variante LED RGB) Inicializado ===");
}

void loop() {
  // 1. Lectura de sensores
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();
  int gas = analogRead(MQ_PIN);
  
  // Control de errores de lectura
  if (isnan(temperatura) || isnan(humedad)) {
    Serial.println("Error: No se puede leer del sensor DHT11.");
    // En caso de error, encendemos el color Azul para avisar al docente
    encenderColor(false, false, true);
    delay(2000);
    return;
  }
  
  // 2. Lógica del Semáforo Ambiental con LED RGB
  
  // Nivel 3: PELIGRO (Rojo)
  if (temperatura >= TEMP_UMBRAL_CRITICA || gas >= AIRE_UMBRAL_CRITICO) {
    Serial.print("[PELIGRO] Aire: ");
    Serial.print(gas);
    Serial.print(" | Temp: ");
    Serial.println(temperatura);
    
    encenderColor(true, false, false); // Luz Roja pura
    emitirAlertaSonora(100, 2500);     // Alarma rápida y aguda
  }
  // Nivel 2: ADVERTENCIA (Amarillo)
  else if (temperatura >= TEMP_UMBRAL_ALTA || humedad >= HUM_UMBRAL_ALTA) {
    Serial.print("[ADVERTENCIA] Temp: ");
    Serial.print(temperatura);
    Serial.print(" | Hum: ");
    Serial.println(humedad);
    
    // Para hacer Amarillo: Rojo = encendido, Verde = encendido, Azul = apagado
    encenderColor(true, true, false);  
    emitirAlertaSonora(300, 1000);     // Alarma lenta y más grave
  }
  // Nivel 1: NORMAL (Verde)
  else {
    Serial.println("[ESTADO NORMAL] Todo en orden.");
    encenderColor(false, true, false); // Luz Verde pura
  }
  
  delay(1000); // Muestreo cada 1 segundo
}

/**
 * Función auxiliar para encender o apagar los componentes del LED RGB.
 * Al ser un LED de Cátodo Común:
 * - HIGH enciende el canal.
 * - LOW apaga el canal.
 */
void encenderColor(bool r, bool g, bool b) {
  digitalWrite(PIN_ROJO, r ? HIGH : LOW);
  digitalWrite(PIN_VERDE, g ? HIGH : LOW);
  digitalWrite(PIN_AZUL, b ? HIGH : LOW);
}

/**
 * Función para emitir tonos sin bloquear el flujo principal de forma agresiva.
 */
void emitirAlertaSonora(int duracion, int frecuencia) {
  static unsigned long ultimoSonido = 0;
  if (millis() - ultimoSonido >= (duracion + 400)) {
    tone(BUZZER_PIN, frecuencia, duracion);
    ultimoSonido = millis();
  }
}
