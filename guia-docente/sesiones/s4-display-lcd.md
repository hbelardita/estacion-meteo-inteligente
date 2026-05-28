# Sesión 4: Pantalla en Acción — Display LCD Paralelo
## Trayecto: NovaMakers Avanzado (9 a 12 años)

En esta sesión, los estudiantes desconectarán la computadora como pantalla de visualización. Conectarán un display **LCD 16x2 paralelo tradicional (sin I2C)** a la placa Arduino Uno para mostrar las lecturas de temperatura y humedad en tiempo real directamente en la pantalla física de la estación. Además, diseñarán y programarán iconos personalizados en el LCD y aprenderán a ajustar el contraste analógico mediante un potenciómetro.

---

## 🎯 Objetivos de Aprendizaje

Al finalizar la sesión, los estudiantes serán capaces de:
1. Entender la diferencia entre comunicación en paralelo de 4 bits y cómo se envían los datos a través de múltiples pines a la vez.
2. Dibujar y cargar iconos personalizados en la memoria del LCD (CGRAM) usando matrices binarias.
3. Posicionar texto de forma precisa en una cuadrícula de coordenadas de 16x2.
4. Ajustar el contraste analógico de una pantalla LCD usando un divisor de tensión (potenciómetro).

---

## 📦 Materiales Necesarios

* Placa Arduino Uno y cable USB.
* Protoboard.
* Sensor DHT11 + resistencia pull-up (ya conectados en la protoboard).
* Pantalla LCD 16x2 paralelo tradicional de 16 pines.
* Potenciómetro rotativo de 10kΩ.
* Resistencia de 220Ω (para la retroiluminación LED).
* Cables Dupont Macho-Macho.
* Computadora con PlatformIO.
* Hojas cuadriculadas de 5x8 para diseñar iconos.
* Enlace al diagrama de conexión: [Diagrama Conexión LCD Paralelo](../diagramas/s4-lcd.md).
* Código fuente de la sesión: [s4_lcd_datos.cpp](../codigo/s4_lcd_datos.cpp).

---

## ⏱️ Estructura de la Sesión

### 🎬 Inicio: Actividad Disparadora (~15 minutos)
1. **La Carrera de Cables:** Conversa con los estudiantes: *"Si quisiéramos enviar cartas a 8 amigos a la vez, ¿sería mejor tener un mensajero para cada amigo (conexión en paralelo) o un solo cartero que lleve todas las cartas una por una (conexión en serie)?"*. Explica que hoy usaremos una conexión en paralelo de 4 bits, donde enviamos partes de la información al mismo tiempo a través de varios pines de datos independientes (D4 a D7), junto con pines de control (RS y EN) para coordinar el tráfico de datos.
2. **El Arte de los Píxeles:** Muestra cómo el LCD forma las letras encendiendo y apagando puntitos (píxeles) organizados en pequeñas rejillas de 5 columnas por 8 filas.

### 🛠️ Desarrollo: Actividad Principal (~60 minutos)
1. **Diseñando Iconos en Papel:**
   * Reparte hojas cuadriculadas a cada grupo.
   * El **Diseñador de Interfaz** dibuja una cuadrícula de 5 de ancho por 8 de alto.
   * Pinten los cuadrados correspondientes para formar un icono (por ejemplo, un sol, una nube o una carita feliz).
   * Traduzcan el dibujo a lenguaje binario: cada fila será una serie de ceros (apagado) e unos (encendido), precedidos por la letra `B` (ejemplo: `B00100`).
2. **Conexión de la Electrónica:**
   * El **Líder de Hardware** realiza la conexión del LCD paralelo (16 pines) al Arduino Uno:
     - RS al Pin 12, EN al Pin 11, y los pines de datos D4, D5, D6, D7 a los pines 4, 5, 6, 7 del Arduino.
     - VSS, RW y el cátodo de retroiluminación LED- (Pin 16) a la línea de tierra común (GND).
     - VDD a la línea de 5V.
     - Conecten el potenciómetro de 10kΩ en la protoboard: las patas externas a 5V y GND, y la pata central al pin V0 (Pin 3) del LCD.
     - Conecten la resistencia de 220Ω entre los 5V y el ánodo LED+ (Pin 15) del LCD.
     - Mantengan las conexiones previas del sensor DHT11.
3. **Carga y Depuración del Software:**
   * El **Líder de Software** abre el código [s4_lcd_datos.cpp](../codigo/s4_lcd_datos.cpp) e introduce las matrices de bits correspondientes a los iconos de temperatura y humedad en el código.
   * Suban el código a la placa.
   * **El Reto:** Ajusten la perilla del potenciómetro en la protoboard si la pantalla brilla pero no muestra las letras. Gírenlo suavemente hasta que aparezca el texto con nitidez.

### 📝 Cierre: Reflexión y Bitácora (~15 minutos)
1. **Verificación de la Interfaz:** Los grupos muestran su pantalla funcionando. El **Científico de Datos** verifica si las mediciones que se muestran en el LCD coinciden con la sensación ambiental.
2. **Registro:** Dibujen en su bitácora cómo quedó la distribución de caracteres en la pantalla y el icono diseñado por ellos.

---

## 💡 Tips para el Docente Facilitador

* **El LCD se enciende pero no muestra letras:** En la gran mayoría de los casos, se debe al potenciómetro de contraste mal regulado. Pide a los alumnos que giren lentamente el potenciómetro de 10kΩ hasta que las letras aparezcan. También asegúrate de que el pin RW del LCD (Pin 5) esté firmemente conectado a GND.
* **Cables sueltos o cruzados:** Debido a la gran cantidad de cables necesarios para el display paralelo (12 cables en total), es común que se crucen o hagan mal contacto. Si el display muestra símbolos raros ("basura"), detengan la alimentación y verifiquen que D4 a D7 del LCD vayan respectivamente a los pines 4 a 7 de Arduino.

---

## 🚀 Extensiones (Para grupos veloces)
Pídeles que modifiquen el código para que en la línea inferior del LCD, además de la humedad, se desplace un texto de marquesina que diga: *"Estacion Inteligente NovaMakers"*. Investiguen la función `lcd.scrollDisplayLeft()`.
