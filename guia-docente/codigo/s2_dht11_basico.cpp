/**
 * Sesión 2: Mi Primer Sensor — Lectura del DHT11
 * Proyecto: Estación Meteorológica Inteligente
 * Trayecto: NovaMakers Avanzado (9 a 12 años)
 * 
 * Descripción: Este programa lee los datos de temperatura y humedad
 * del sensor DHT11 conectado al pin digital 2 y los muestra a través
 * del Monitor Serial en formato de tabla fácil de leer. También calcula
 * la sensación térmica basada en estos dos parámetros.
 */

#include <Arduino.h>
#include <DHT.h>

// Definición de pines y tipo de sensor
#define DHTPIN 2      // Pin digital al que conectamos la línea DATA del DHT11
#define DHTTYPE DHT11 // Especificamos que usamos el modelo DHT11 (y no DHT22)

// Inicialización del sensor DHT
DHT dht(DHTPIN, DHTTYPE);

// Variable global para contar el número de lecturas que realizamos
int lecturaNumero = 0;

void setup() {
  // Iniciamos la comunicación serial a 9600 baudios para hablar con la computadora
  Serial.begin(9600);
  
  // Iniciamos el sensor de temperatura y humedad DHT
  dht.begin();
  
  // Imprimimos un encabezado de bienvenida al Monitor Serial
  Serial.println(F("============================================="));
  Serial.println(F("       ESTACION METEOROLOGICA INTELIGENTE    "));
  Serial.println(F("           Sesion 2: Sensor DHT11            "));
  Serial.println(F("============================================="));
  Serial.println(F("Lectura | Temperatura (*C) | Humedad (%) | Sensacion Termica (*C)"));
  Serial.println(F("---------------------------------------------"));
}

void loop() {
  // El DHT11 es un sensor lento. Las lecturas pueden tardar hasta 2 segundos.
  // Por lo tanto, esperamos 2 segundos (2000 ms) antes de realizar una nueva lectura.
  delay(2000);

  // Leemos la humedad relativa (en porcentaje)
  float humedad = dht.readHumidity();
  // Leemos la temperatura en grados Celsius
  float temperatura = dht.readTemperature();

  // Comprobamos si las lecturas fallaron (isnan significa "Is Not a Number" o "No es un Número")
  if (isnan(humedad) || isnan(temperatura)) {
    Serial.println(F("Error: No se pudo leer del sensor DHT11. Revisa tus conexiones."));
    return; // Si falló, volvemos a empezar el loop sin ejecutar el resto del código
  }

  // Calculamos el índice de calor (Sensación Térmica) en grados Celsius.
  // El tercer parámetro 'false' indica que queremos el resultado en Celsius (no Fahrenheit).
  float sensacionTermica = dht.computeHeatIndex(temperatura, humedad, false);

  // Incrementamos el contador de lecturas
  lecturaNumero++;

  // Mostramos los datos formateados en la consola Serial
  Serial.print(F("   "));
  Serial.print(lecturaNumero);
  Serial.print(F("    |        "));
  Serial.print(temperatura, 1); // El ", 1" indica que queremos mostrar solo un decimal
  Serial.print(F("      |    "));
  Serial.print(humedad, 1);
  Serial.print(F("     |        "));
  Serial.println(sensacionTermica, 1);
}
