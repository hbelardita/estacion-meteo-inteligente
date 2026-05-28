/**
 * Sesión 4: Pantalla en Acción — DHT11 en LCD I2C
 * Proyecto: Estación Meteorológica Inteligente
 * Trayecto: NovaMakers Avanzado (9 a 12 años)
 * 
 * Descripción: Este programa integra el sensor DHT11 y la pantalla LCD I2C.
 * Enseña cómo configurar la pantalla y crear iconos personalizados
 * dibujando píxeles usando matrices binarias. Muestra la temperatura
 * y la humedad en pantalla usando caracteres personalizados de
 * termómetro y gota de agua.
 */

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <DHT.h>

// Definición de pines y sensores
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// Configuración de la pantalla LCD paralela: RS=12, EN=11, D4=4, D5=5, D6=6, D7=7
LiquidCrystal lcd(12, 11, 4, 5, 6, 7);

// Diseño de caracteres personalizados (Iconos de 5x8 píxeles)
// El número 1 enciende el píxel y el 0 lo apaga.

// Icono 1: Termómetro de temperatura
byte iconoTermometro[8] = {
  B00100, //   *  
  B01010, //  * * 
  B01010, //  * * 
  B01010, //  * * 
  B01110, //  *** 
  B11111, // *****
  B11111, // *****
  B01110  //  *** 
};

// Icono 2: Gota para la humedad
byte iconoGota[8] = {
  B00100, //   *  
  B00100, //   *  
  B01010, //  * * 
  B01010, //  * * 
  B10001, // *   *
  B10001, // *   *
  B10001, // *   *
  B01110  //  *** 
};

// Icono 3: Grado centígrado (*)
byte iconoGrado[8] = {
  B00110, //  **  
  B01001, // *  * 
  B01001, // *  * 
  B00110, //  **  
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  // Iniciamos el sensor DHT
  dht.begin();
  
  // Iniciamos la pantalla LCD (16 columnas y 2 filas)
  lcd.begin(16, 2);
  
  // Registramos los caracteres personalizados en la memoria interna del LCD (CGRAM).
  // Se les asigna una dirección numérica de 0 a 7.
  lcd.createChar(0, iconoTermometro);
  lcd.createChar(1, iconoGota);
  lcd.createChar(2, iconoGrado);
  
  // Mensaje de bienvenida en pantalla
  lcd.setCursor(0, 0); // Columna 0, Fila 0 (Línea superior)
  lcd.print("Estacion Meteo");
  lcd.setCursor(0, 1); // Columna 0, Fila 1 (Línea inferior)
  lcd.print("Iniciando...");
  delay(2000); // Mostramos el mensaje durante 2 segundos
  lcd.clear(); // Limpiamos la pantalla
}

void loop() {
  // Leemos las variables ambientales
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  // Si hay error en la lectura de sensores, lo indicamos en el LCD
  if (isnan(temp) || isnan(hum)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error Sensor!");
    lcd.setCursor(0, 1);
    lcd.print("Revisa Cables");
  } else {
    // Línea 1: Mostrar Temperatura
    lcd.setCursor(0, 0);
    lcd.write((uint8_t)0); // Escribe el carácter personalizado 0 (Termómetro)
    lcd.print(" Temp: ");
    lcd.print(temp, 1); // Temperatura con 1 decimal
    lcd.write((uint8_t)2); // Escribe el carácter personalizado 2 (Símbolo de Grado)
    lcd.print("C");

    // Línea 2: Mostrar Humedad
    lcd.setCursor(0, 1);
    lcd.write((uint8_t)1); // Escribe el carácter personalizado 1 (Gota)
    lcd.print(" Hum:  ");
    lcd.print(hum, 1);  // Humedad con 1 decimal
    lcd.print(" %");
  }

  // Esperamos 2 segundos antes de volver a leer y actualizar
  delay(2000);
}
