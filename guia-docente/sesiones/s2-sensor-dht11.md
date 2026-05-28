# Sesión 2: Mi Primer Sensor — Temperatura y Humedad (DHT11)
## Trayecto: NovaMakers Avanzado (9 a 12 años)

En esta sesión, los estudiantes comenzarán a trabajar con hardware real. Conectarán el sensor de temperatura y humedad digital **DHT11** a la placa Arduino Uno y aprenderán a programar un código simple para leer sus valores y mostrarlos en la pantalla de la computadora a través del Monitor Serial.

---

## 🎯 Objetivos de Aprendizaje

Al finalizar la sesión, los estudiantes serán capaces de:
1. Comprender la diferencia entre un pin de alimentación (VCC/GND) y un pin de señal de datos digitales.
2. Armar el circuito básico del DHT11 en la protoboard usando una resistencia de pull-up de 10kΩ.
3. Usar el Monitor Serial del entorno de desarrollo para recibir y observar datos físicos en tiempo real.

---

## 📦 Materiales Necesarios

* Placa Arduino Uno y cable USB.
* Protoboard.
* Sensor DHT11 (suelto de 4 pines o en módulo de 3 pines).
* Resistencia de 10 kΩ (solo si se usa el sensor suelto de 4 pines).
* Cables Dupont Macho-Macho.
* Computadora con PlatformIO configurado.
* Enlace al diagrama de conexión: [Diagrama Conexión DHT11](../diagramas/s2-dht11-basico.md).
* Código fuente de la sesión: [s2_dht11_basico.cpp](../codigo/s2_dht11_basico.cpp).

---

## ⏱️ Estructura de la Sesión

### 🎬 Inicio: Actividad Disparadora (~15 minutos)
1. **La Caja Sorpresa:** Muestra a los alumnos el sensor DHT11 y pregúntales: *"¿Ven estas rejillas que tiene encima la carcasa azul? ¿Para qué creen que sirven?"*. Explícales que sirve para dejar pasar el aire hacia el sensor de humedad que tiene adentro.
2. **Explicación del Flujo de Datos:** Explica brevemente cómo el sensor toma mediciones físicas analógicas, las convierte en datos binarios (ceros y unos) dentro de su propio chip, y los envía como un tren de pulsos súper rápido a través del pin DATA al Arduino.

### 🛠️ Desarrollo: Actividad Principal (~60 minutos)
1. **Roles Activos:** El **Líder de Hardware** prepara la protoboard, el sensor DHT11 y los cables. El **Líder de Software** abre el editor de código en la computadora.
2. **Armado del Circuito:** 
   * Los alumnos siguen detalladamente el [Diagrama Conexión DHT11](../diagramas/s2-dht11-basico.md).
   * **¡Importante!** Si usan el sensor de 4 pines, deben colocar la resistencia de 10kΩ puenteando las líneas de VCC y DATA.
   * El **Diseñador** y el **Científico de Datos** revisan pin a pin que el cableado sea idéntico al diagrama antes de energizar la placa.
3. **Carga del Código:**
   * El **Líder de Software** carga el código [s2_dht11_basico.cpp](../codigo/s2_dht11_basico.cpp) en el proyecto PlatformIO.
   * Compilan el código y lo suben al Arduino.
4. **Prueba de Sensibilidad (El experimento del soplido):**
   * Abran el Monitor Serial (configurado a 9600 baudios).
   * Verifiquen que la tabla de datos empiece a llenarse con valores reales de temperatura y humedad ambiental del aula.
   * **El Desafío:** Pídeles que hagan un soplido suave y prolongado (aire húmedo y tibio de sus pulmones) directamente sobre el sensor. Observen en el Monitor Serial si la humedad y la temperatura suben de inmediato. ¡Eso confirma que su sensor funciona!

### 📝 Cierre: Reflexión y Bitácora (~15 minutos)
1. **Registro Científico:** En la bitácora grupal, el **Científico de Datos** debe anotar los valores iniciales del aula en reposo y los valores máximos alcanzados con el soplido.
2. **Preguntas de Reflexión:** Conversen: *"¿Por qué cuando soplamos sube más la humedad que la temperatura?"* (El vapor de agua exhalado satura las rejillas del sensor).

---

## 💡 Tips para el Docente Facilitador

* **Fallo común "Nan" o "Read error":** Si el Monitor Serial muestra continuamente `isnan` o "Error: no se pudo leer el sensor", desconecten el Arduino y revisen:
  * ¿La resistencia de pull-up está bien puesta?
  * ¿Se conectó el sensor al pin digital D2 o se confundieron con el pin analógico A2?
  * ¿El cable de datos del sensor hace buen contacto en la protoboard?
* **Pies de componentes:** Asegúrate de que las patas metálicas de la resistencia no se toquen entre sí, ya que esto provocaría lecturas incorrectas.

---

## 🚀 Extensiones (Para grupos veloces)
Invita a los alumnos a modificar el código en la línea `delay(2000);` cambiando el valor a `delay(500);` para ver los datos pasar mucho más rápido. Pregúntales: *"¿Es útil leer la temperatura 2 veces por segundo en la vida real? ¿Cambia el clima tan rápido?"*. Debatan sobre optimizar la energía de la estación meteorológica.
