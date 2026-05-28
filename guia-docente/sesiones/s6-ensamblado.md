# Sesión 6: Ensamblado y Código Definitivo
## Trayecto: NovaMakers Avanzado (9 a 12 años)

En esta sesión, los estudiantes consolidarán su aprendizaje técnico. Pasarán del circuito suelto de pruebas en la protoboard a un prototipo de producto real integrado. Escribirán el código modular final en la placa, adaptarán el bus de alimentación común y montarán toda la electrónica de forma segura dentro de la carcasa física diseñada en la Sesión 1.

---

## 🎯 Objetivos de Aprendizaje

Al finalizar la sesión, los estudiantes serán capaces de:
1. Utilizar un código estructurado modularmente mediante funciones de software independientes para mejorar la legibilidad.
2. Montar componentes electrónicos dentro de un contenedor rígido asegurando ventilación adecuada para los sensores.
3. Evaluar la calidad y resistencia física de un prototipo interactivo (ingeniería de producto).

---

## 📦 Materiales Necesarios

* Placa Arduino Uno, protoboard, sensores y actuadores integrados en el circuito.
* Carcasa física (caja de cartón mediana, planchas de plástico, madera MDF o piezas impresas en 3D).
* Herramientas de montaje seguras (cinta bifaz, pegamento de silicona fría, bandas elásticas, cúter o tijeras supervisados por el docente).
* Enlace al diagrama de conexión completo: [Diagrama Integración Completa](../diagramas/s6-completo.md).
* Código fuente definitivo: [s6_estacion_completa.cpp](../codigo/s6_estacion_completa.cpp).

---

## ⏱️ Estructura de la Sesión

### 🎬 Inicio: Actividad Disparadora (~15 minutos)
1. **La Prueba del Terremoto:** Muestra un circuito suelto lleno de cables volando y sacúdelo suavemente. Pregúntales: *"Si instalamos esta estación en el techo de la escuela y sopla un viento fuerte, ¿cuánto tiempo creen que durará funcionando antes de que se suelte un cable?"*. Conversen sobre la importancia de proteger los circuitos con una carcasa protectora.
2. **Explicación del Software Modular:** Explica que el código definitivo es modular. Es como tener organizados los juguetes en cajas separadas: hay una función exclusiva para leer datos (`leerSensores()`), otra para prender las luces (`controlarAlertas()`) y otra para dibujar la pantalla (`actualizarLcd()`). Esto ayuda a que el código sea fácil de entender y reparar.

### 🛠️ Desarrollo: Actividad Principal (~60 minutos)
1. **Actualización del Software Final:**
   * El **Líder de Software** copia el código [s6_estacion_completa.cpp](../codigo/s6_estacion_completa.cpp) a su proyecto principal de PlatformIO.
   * Compila y carga el programa. El LCD mostrará una rotación automática de pantallas cada 3 segundos, mostrando temperatura, humedad, sensación térmica y calidad de aire con iconos personalizados.
2. **Preparación de la Carcasa:**
   * El **Diseñador de Interfaz y Carcasa** toma el boceto creado en la sesión 1.
   * Usando regla y lápiz, marcan sobre el contenedor de cartón o plástico las aberturas necesarias:
     * Una ventana rectangular de 7.2 cm x 2.4 cm para la pantalla LCD.
     * Tres orificios redondos para que asomen los cabezales de los LEDs.
     * Una ventana con rejilla o perforaciones pequeñas para que el sensor DHT11 y el MQ-135 tengan acceso al aire exterior.
     * Un orificio lateral para pasar el cable USB de alimentación hacia el Arduino.
3. **Corte y Montaje de la Electrónica:**
   * Con la ayuda del docente, corten las aberturas de la caja.
   * El **Líder de Hardware** fija el Arduino, la protoboard y la pantalla LCD en el interior de la caja usando cinta bifaz o soportes plásticos.
   * Cierren la caja con cuidado asegurando que ningún cable Dupont quede presionado o estrangulado por las paredes.

### 📝 Cierre: Reflexión y Bitácora (~15 minutos)
1. **Control de Calidad (Q&A):** Enciendan la estación a través de su puerto USB externo. Realicen movimientos suaves en la caja para verificar que ningún componente se suelte por dentro.
2. **Registro:** El **Científico de Datos** toma una fotografía del prototipo terminado o dibuja un esquema del prototipo físico real indicando el lugar de cada sensor.

---

## 💡 Tips para el Docente Facilitador

* **Supervisión de herramientas cortantes:** El uso de cúters o tijeras para calar ventanas en el cartón o plástico debe ser realizado únicamente por el docente o bajo supervisión directa individual.
* **El calor del sensor dentro de la caja:** Dado que el MQ-135 calienta, es crucial que la caja tenga pequeños orificios de ventilación arriba y abajo para generar corriente de convección natural de aire, evitando que el calor del propio sensor altere la lectura de temperatura del DHT11 dentro del contenedor cerrado.

---

## 🚀 Extensiones (Para grupos veloces)
Los grupos que terminen pueden agregar elementos estéticos a la carcasa: pintar la caja con pintura acrílica, etiquetar con marcadores las luces del semáforo con las palabras "ÓPTIMO", "PREVENCIÓN", "PELIGRO", o fabricar un pequeño parasol de cartón para proteger la estación si simulan colocarla a la intemperie.
