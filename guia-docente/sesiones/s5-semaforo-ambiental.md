# Sesión 5: Semáforo Ambiental y Alarmas
## Trayecto: NovaMakers Avanzado (9 a 12 años)

En esta sesión, los estudiantes dotarán a su estación de capacidad reactiva. Conectarán tres LEDs (Verde, Amarillo, Rojo) y un buzzer pasivo a la placa Arduino. Programarán condicionales lógicos para evaluar las lecturas de los sensores en tiempo real y cambiar el estado del semáforo luminoso, emitiendo tonos audibles diferenciados en caso de situaciones de emergencia ambiental.

---

## 🎯 Objetivos de Aprendizaje

Al finalizar la sesión, los estudiantes serán capaces de:
1. Comprender la estructura lógica de los condicionales anidados (`if`, `else if`, `else`) para la toma de decisiones algorítmicas.
2. Proteger físicamente componentes optoelectrónicos (LEDs) utilizando resistencias limitadoras de corriente de 220Ω.
3. Programar el buzzer pasivo utilizando frecuencias de sonido para generar tonos agudos o graves según el nivel de alerta.

---

## 📦 Materiales Necesarios

* Placa Arduino Uno y cable USB.
* Protoboard con sensores DHT11 y MQ-135 y pantalla LCD ya conectados.
* **Opción A (Estándar):** 3 LEDs individuales (Verde, Amarillo, Rojo) + 3 resistencias de 220 Ω.
* **Opción B (Variante RGB):** 1 LED RGB de Cátodo Común + 3 resistencias de 220 Ω.
* 1 Buzzer pasivo.
* Cables Dupont Macho-Macho.
* Computadora con PlatformIO.
* Alcohol en gel o perfume (para pruebas).
* Ficha de trabajo: [Plantilla de Tabla de Umbrales](../recursos/plantilla-tabla-umbrales.md).
* Enlaces a diagramas de conexión:
  * [Diagrama Conexión Semáforo Estándar (3 LEDs)](../diagramas/s5-semaforo.md)
  * [Diagrama Conexión Semáforo Variante (LED RGB)](../diagramas/s5-semaforo-rgb.md)
* Códigos fuente de la sesión:
  * [Código Semáforo Estándar (s5_semaforo.cpp)](../codigo/s5_semaforo.cpp)
  * [Código Semáforo Variante (s5_semaforo_rgb.cpp)](../codigo/s5_semaforo_rgb.cpp)


---

## ⏱️ Estructura de la Sesión

### 🎬 Inicio: Actividad Disparadora (~15 minutos)
1. **La Fábrica de Decisiones:** Pregunta a los estudiantes: *"Si conducen un auto y el semáforo cambia a amarillo, ¿qué deciden hacer? ¿Y si cambia a rojo? ¿Cómo hace la computadora del auto para saber si una puerta quedó abierta?"*.
2. **Introducción a los Condicionales:** Explica cómo el procesador del Arduino evalúa las variables de los sensores usando preguntas lógicas: *"Si la temperatura es mayor a 35 grados, entonces haz X; de lo contrario, si la temperatura es..."*. Dibuja un diagrama de flujo simple en el pizarrón.

### 🛠️ Desarrollo: Actividad Principal (~60 minutos)
1. **Completar la Ficha de Umbrales:** 
   * Antes de armar el circuito, los equipos completan la [Plantilla de Tabla de Umbrales](../recursos/plantilla-tabla-umbrales.md) decidiendo a qué valores de temperatura, humedad y gases se activarán las luces del semáforo.
2. **Ensamblado del Semáforo y Buzzer (Elegir una opción):**
   * **Opción A (3 LEDs individuales):** El **Líder de Hardware** coloca los 3 LEDs. Conecta cada ánodo (pata larga) a un pin del Arduino (D8, D9, D10) a través de una resistencia de 220Ω, y todos los cátodos al GND de la placa. ([Diagrama Conexión Semáforo Estándar](../diagramas/s5-semaforo.md)).
   * **Opción B (1 LED RGB Cátodo Común):** El **Líder de Hardware** coloca el LED RGB en la protoboard. Conecta la pata larga (Cátodo Común) al GND general. Las patas R (Rojo), G (Verde) y B (Azul) se conectan a los pines D8, D9 y D10 respectivamente, interponiendo una resistencia de 220Ω en cada una. ([Diagrama Conexión Semáforo Variante RGB](../diagramas/s5-semaforo-rgb.md)).
   * En ambas opciones, conecta el Buzzer: la pata (+) al pin D3 y la pata (-) a GND.
3. **Carga y Prueba de Estrés de la Estación:**
   * El **Líder de Software** sube el código correspondiente a la opción elegida ([s5_semaforo.cpp](../codigo/s5_semaforo.cpp) o [s5_semaforo_rgb.cpp](../codigo/s5_semaforo_rgb.cpp)).
   * **Test Normal (Verde):** Inicialmente, se debe ver luz verde (LED Verde o canal Verde en el RGB).
   * **Test Humedad (Amarillo):** Al soplar sobre el DHT11 y superar el 80% de humedad, el semáforo cambia a Amarillo (mezcla de Rojo y Verde encendidos en el caso del LED RGB) y el buzzer emite un pitido lento.
   * **Test Gas (Rojo):** Al acercar alcohol al MQ-135, el semáforo cambia a Rojo puro y suena una alarma rápida.


### 📝 Cierre: Reflexión y Bitácora (~15 minutos)
1. **El Informe de Seguridad:** El **Científico de Datos** documenta en la bitácora si todos los umbrales funcionaron correctamente y los tiempos que tardó el sistema en volver a la normalidad (LED Verde) una vez retirados los estímulos.
2. **Reflexión Grupal:** Conversen sobre por qué las alarmas no deben sonar todo el tiempo y cómo los programadores evitan generar "fatiga de alarmas" en sistemas de seguridad reales.

---

## 💡 Tips para el Docente Facilitador

* **Polaridad de LEDs y Buzzer:** Es muy frecuente que los alumnos conecten los LEDs al revés. Recuerda: pata larga = positivo (al pin de Arduino), pata corta = negativo (a GND). Si un LED no enciende, antes de tocar el código, pruébenlo girándolo 180 grados en la protoboard.
* **Resistencias mezcladas:** Verifica que no hayan usado la resistencia de 10kΩ (marcas marrón-negro-naranja) en lugar de las de 220Ω (marcas rojo-rojo-marrón) para los LEDs, ya que de lo contrario brillarán de forma casi imperceptible.

---

## 🚀 Extensiones (Para grupos veloces)
Desafía a los estudiantes a crear un código de pitidos especial para fallas técnicas. Por ejemplo, si el sensor DHT11 se desconecta físicamente (detectado mediante `isnan`), la estación debe emitir un SOS sonoro alternando tonos agudos y graves para avisar al operador.
