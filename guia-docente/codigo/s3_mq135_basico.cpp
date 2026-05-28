/**
 * Sesión 3: ¿Qué Respiramos? — Lectura del MQ-135
 * Proyecto: Estación Meteorológica Inteligente
 * Trayecto: NovaMakers Avanzado (9 a 12 años)
 * 
 * Descripción: Este programa lee los valores analógicos crudos del sensor
 * de calidad del aire MQ-135 conectado al pin analógico A0.
 * Explica cómo funciona la escala analógica del Arduino (0 a 1023) y
 * calcula un promedio de referencia en "aire limpio" para usarlo como
 * línea de base (baseline) para clasificar la calidad del aire.
 */

#include <Arduino.h>

// Definición del pin analógico del sensor
#define GAS_PIN A0

// Variables globales para la calibración básica
unsigned long sumaCalibracion = 0;
int lecturasCalibracion = 100; // Tomaremos 100 muestras iniciales para promediar
float valorAireLimpio = 0.0;   // Aquí guardaremos la línea de base (baseline)
bool calibrado = false;

void setup() {
  // Iniciamos comunicación serial
  Serial.begin(9600);
  
  // Imprimimos el encabezado del sensor MQ-135
  Serial.println(F("============================================="));
  Serial.println(F("       ESTACION METEOROLOGICA INTELIGENTE    "));
  Serial.println(F("        Sesion 3: Calidad del Aire (MQ-135)   "));
  Serial.println(F("============================================="));
  
  // Proceso de Calibración
  Serial.println(F("Iniciando calibracion automatica..."));
  Serial.println(F("Asegurate de que el sensor este en un ambiente de AIRE LIMPIO."));
  Serial.print(F("Tomando muestras"));
  
  // Tomamos varias muestras para obtener un promedio estable
  for (int i = 0; i < lecturasCalibracion; i++) {
    sumaCalibracion += analogRead(GAS_PIN);
    delay(50); // Pequeño retraso entre lecturas
    if (i % 10 == 0) {
      Serial.print(F(".")); // Efecto visual de progreso
    }
  }
  
  // Calculamos el promedio del aire limpio
  valorAireLimpio = (float)sumaCalibracion / lecturasCalibracion;
  calibrado = true;
  
  Serial.println();
  Serial.println(F("¡Calibracion completada con exito!"));
  Serial.print(F("Valor promedio de referencia (Línea de Base): "));
  Serial.println(valorAireLimpio, 1);
  Serial.println(F("---------------------------------------------"));
  Serial.println(F("Lectura Cruda | Diferencia | Estado de la Calidad del Aire"));
  Serial.println(F("---------------------------------------------"));
}

void loop() {
  // Leemos el valor analógico actual del sensor MQ-135 (rango 0 a 1023)
  int valorCrudo = analogRead(GAS_PIN);
  
  // Calculamos la diferencia relativa con respecto a nuestra línea de base
  float diferencia = (float)valorCrudo - valorAireLimpio;
  
  // Determinamos el estado del aire de forma amigable para los chicos
  String estadoAire = "";
  
  if (diferencia <= 20) {
    estadoAire = F("EXCELENTE / LIMPIO");
  } else if (diferencia > 20 && diferencia <= 80) {
    estadoAire = F("MODERADO / ACEPTABLE");
  } else if (diferencia > 80 && diferencia <= 180) {
    estadoAire = F("CARGADO (Ventilar ambiente)");
  } else {
    estadoAire = F("¡ALERTA! GASES / HUMO DETECTADO");
  }
  
  // Imprimimos los datos en el Monitor Serial
  Serial.print(F("     "));
  Serial.print(valorCrudo);
  Serial.print(F("      |    "));
  if (diferencia >= 0) Serial.print(F("+")); // Ponemos signo + si subió
  Serial.print(diferencia, 1);
  Serial.print(F("   |  "));
  Serial.println(estadoAire);
  
  // Esperamos 1.5 segundos para la próxima lectura
  delay(1500);
}
