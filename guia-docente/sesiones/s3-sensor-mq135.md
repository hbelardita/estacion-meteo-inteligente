# Sesión 3: ¿Qué Respiramos? — Calidad del Aire (MQ-135)
## Trayecto: NovaMakers Avanzado (9 a 12 años)

En esta sesión, los estudiantes expandirán su estación meteorológica incorporando una "nariz electrónica" analógica: el sensor **MQ-135**. Conectarán el sensor al pin analógico A0, aprenderán cómo el Arduino lee voltajes variables en una escala de 0 a 1023, y realizarán una calibración básica para establecer una línea de base (baseline) que diferencie el aire limpio de los contaminantes.

---

## 🎯 Objetivos de Aprendizaje

Al finalizar la sesión, los estudiantes serán capaces de:
1. Diferenciar una señal de entrada digital (como la del DHT11) de una señal analógica (voltaje variable en pin A0).
2. Conectar un sensor analógico MQ-135 usando alimentación estable de 5V.
3. Explicar el concepto de "Calibración" y "Línea de Base" en la recolección de datos científicos.

---

## 📦 Materiales Necesarios

* Placa Arduino Uno y cable USB.
* Protoboard.
* Sensor MQ-135 en módulo de 4 pines (con placa trasera).
* Cables Dupont Macho-Macho.
* Computadora con PlatformIO.
* Alcohol en gel, marcadores de pizarra con olor fuerte, o un perfume (para simular contaminación).
* Enlace al diagrama de conexión: [Diagrama Conexión MQ-135](../diagramas/s3-mq135.md).
* Código fuente de la sesión: [s3_mq135_basico.cpp](../codigo/s3_mq135_basico.cpp).

---

## ⏱️ Estructura de la Sesión

### 🎬 Inicio: Actividad Disparadora (~15 minutos)
1. **El Superolfato:** Pregunta al grupo: *"¿Cómo hace nuestra nariz para detectar cuando la comida se está quemando en la cocina antes de que veamos el humo?"*. Explícales que los humanos tenemos células receptoras de químicos en la nariz, y que el sensor MQ-135 imita este comportamiento usando un compuesto químico caliente que reacciona con gases del aire.
2. **Introducción a lo Analógico:** Dibuja en el pizarrón una bombilla de luz con llave de encendido/apagado (Digital: ON/OFF) y compárala con una perilla giratoria que permite ajustar la intensidad de la luz de forma gradual (Analógico: rango continuo). Explica que el MQ-135 mide de forma analógica qué tan "cargado" está el ambiente en una escala de 0 a 1023.

### 🛠️ Desarrollo: Actividad Principal (~60 minutos)
1. **Roles Activos:** El **Líder de Hardware** prepara la protoboard e introduce el sensor MQ-135. El **Líder de Software** prepara el archivo del código.
2. **Armado del Circuito:** 
   * Los estudiantes siguen el [Diagrama Conexión MQ-135](../diagramas/s3-mq135.md).
   * **¡Importante!** Asegurarse de conectar el pin **AO** (Analog Out) al pin **A0** del Arduino. No usar el pin DO.
3. **Carga y Calibración:**
   * El **Líder de Software** carga el código [s3_mq135_basico.cpp](../codigo/s3_mq135_basico.cpp).
   * Al iniciar el programa, el Arduino pedirá que el aula esté ventilada para tomar 100 muestras iniciales. Esto definirá el valor de referencia de "Aire Limpio".
4. **Prueba de Contaminación Controlada:**
   * Una vez completada la calibración, el Monitor Serial mostrará lecturas estables (cercanas a 0 de diferencia).
   * **El Experimento:** El **Científico de Datos** destapará un marcador con aroma fuerte o se colocará una gotita de alcohol en gel en el dedo y la acercará (sin tocar el sensor) al protector metálico del MQ-135.
   * Observen el Monitor Serial: ¿Cómo cambia el valor analógico y la diferencia relativa? ¿Qué tan rápido se recupera el sensor cuando retiramos la fuente de olor?

### 📝 Cierre: Reflexión y Bitácora (~15 minutos)
1. **Registro Científico:** Anoten en el cuaderno:
   * El valor crudo del aire limpio del aula (por ejemplo: 150).
   * El valor crudo máximo alcanzado con el alcohol/marcador (por ejemplo: 450).
2. **Debate sobre Umbrales:** Conversen: *"Si tuviéramos que encender una campana de extracción de aire en una fábrica, ¿en qué número de diferencia activaríamos la alarma? ¿Por qué?"*.

---

## 💡 Tips para el Docente Facilitador

* **El sensor se calienta:** Es completamente normal que el MQ-135 se sienta tibio. Tiene una resistencia de calentamiento interna que necesita calentarse para operar químicamente.
* **Valores iniciales inestables:** Si al encender el sensor por primera vez los valores son extremadamente altos (ej. 800) y van bajando muy lento, explícales a los alumnos que es el proceso de "limpieza química interna". Deben esperar unos 2 o 3 minutos hasta que el valor se estabilice antes de reiniciar la placa para que calibre bien.

---

## 🚀 Extensiones (Para grupos veloces)
Pídeles que editen el código de la sesión 3 para modificar los rangos de la calidad de aire. Por ejemplo, hacer la escala de alerta más sensible si el aula es muy pequeña y poco ventilada.
