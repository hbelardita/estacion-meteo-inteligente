# Walkthrough del Proyecto: Estación Meteorológica Inteligente
## Resumen final de entrega de la Guía Docente

Este documento ofrece una guía rápida para el docente sobre cómo está estructurada la información del proyecto, qué archivos se han creado en el workspace, cómo verificar su correcto funcionamiento y los pasos recomendados para su dictado.

---

## 🗂️ Estructura Completa de Archivos Creados

Hemos organizado la guía en carpetas según su propósito pedagógico y técnico:

```text
estacion-meteo-inteligente/
├── platformio.ini                    ← Configuración de dependencias (DHT, LCD)
├── src/
│   └── main.cpp                      ← Código definitivo final integrado
├── guia-docente/
│   ├── README.md                     ← Introducción y mapa de progresión de sesiones
│   ├── materiales.md                 ← Inventario de componentes y roles rotativos
│   ├── preguntas-debate.md           ← Respuestas didácticas para debates científicos
│   ├── walkthrough.md                ← Este archivo (Resumen de entrega)
│   ├── diagramas/
│   │   ├── s2-dht11-basico.md        ← Circuito de lectura DHT11
│   │   ├── s3-mq135.md               ← Circuito de sensor de gas MQ-135
│   │   ├── s4-lcd.md                 ← Circuito de pantalla LCD paralela
│   │   ├── s5-semaforo.md            ← Circuito de LEDs y Buzzer
│   │   ├── s5-semaforo-rgb.md        ← Variante: Circuito con LED RGB
│   │   └── s6-completo.md            ← Circuito integrado final
│   ├── codigo/
│   │   ├── s2_dht11_basico.cpp       ← Código aislado sesión 2
│   │   ├── s3_mq135_basico.cpp       ← Código aislado sesión 3
│   │   ├── s4_lcd_datos.cpp          ← Código aislado sesión 4
│   │   ├── s5_semaforo.cpp           ← Código integrado sesión 5
│   │   ├── s5_semaforo_rgb.cpp       ← Variante: Código semáforo con LED RGB
│   │   ├── s6_estacion_completa.cpp  ← Código definitivo modular sesión 6
│   │   ├── s6_estacion_completa_rgb.cpp ← Variante: Código integrado final con LED RGB
│   │   └── s7_registro_datos.cpp     ← Código registro CSV sesión 7
│   ├── sesiones/
│   │   ├── s1-introduccion.md        ← Planificación sesión 1 (Diseño)
│   │   ├── s2-sensor-dht11.md        ← Planificación sesión 2 (DHT11)
│   │   ├── s3-sensor-mq135.md        ← Planificación sesión 3 (MQ-135)
│   │   ├── s4-display-lcd.md         ← Planificación sesión 4 (LCD Paralelo)
│   │   ├── s5-semaforo-ambiental.md  ← Planificación sesión 5 (Semáforo/Buzzer)
│   │   ├── s6-ensamblado.md          ← Planificación sesión 6 (Montaje)
│   │   ├── s7-registro-datos.md      ← Planificación sesión 7 (Series Temporales)
│   │   └── s8-congreso.md            ← Planificación sesión 8 (Congreso Final)
│   └── recursos/
│       ├── plantilla-tabla-umbrales.md ← Ficha para configurar los umbrales
│       ├── plantilla-informe-tecnico.md ← Plantilla de informe científico escolar
│       └── rubrica-congreso.md        ← Rúbrica de evaluación grupal
```

---

## 🛠️ Verificación y Validación del Código

El código definitivo del proyecto se encuentra en [src/main.cpp](../src/main.cpp). Ha sido configurado con las bibliotecas oficiales necesarias en el archivo `platformio.ini`:
1. `Adafruit DHT Sensor Library` para leer el sensor DHT11.
2. `LiquidCrystal` nativa para manejar la pantalla LCD paralela (16 pines).

Para compilar y verificar la sintaxis del proyecto utilizando la herramienta PlatformIO del entorno de desarrollo, se puede ejecutar el comando:
```bash
pio run
```

### 🔌 Comprobación Física de Pines del Arduino

Si la estación se comporta de forma incorrecta, revisa el cableado usando los diagramas ASCII. Los pines definidos en el código final son:

* **Pin 2:** Línea de datos (DATA) del sensor DHT11.
* **Pin A0:** Entrada analógica del sensor de calidad de aire MQ-135.
* **Pin 12:** Línea RS del display LCD paralelo.
* **Pin 11:** Línea EN (Enable) del display LCD paralelo.
* **Pin 4:** Línea D4 del display LCD paralelo.
* **Pin 5:** Línea D5 del display LCD paralelo.
* **Pin 6:** Línea D6 del display LCD paralelo.
* **Pin 7:** Línea D7 del display LCD paralelo.
* **Pin 3:** Buzzer pasivo.
* **Conexión de Alertas Luminosas (Según la opción elegida):**
  * **Opción A (3 LEDs estándar):**
    * **Pin 8:** LED Verde (Seguro).
    * **Pin 9:** LED Amarillo (Advertencia).
    * **Pin 10:** LED Rojo (Peligro).
  * **Opción B (1 LED RGB Cátodo Común):**
    * **Pin 8:** Ánodo Rojo (R).
    * **Pin 9:** Ánodo Verde (G).
    * **Pin 10:** Ánodo Azul (B) — *Nota: Se enciende en conjunto con el Rojo para generar el Amarillo*.


---

## 💡 Cómo Guiar el Proyecto en el Aula (Paso a Paso)

1. **Mantén los códigos a mano:** Si un equipo se atrasa o pierde su código, puedes indicarle que cargue directamente el archivo `.cpp` de la sesión correspondiente que se encuentra en la carpeta `guia-docente/codigo/` para que no pierda el ritmo de la clase.
2. **Promueve la experimentación:** Incentiva a los alumnos a alterar los umbrales definidos en las variables de `src/main.cpp` (por ejemplo, bajar el umbral crítico de aire a 250) para ver cómo responde la estación de forma inmediata.
3. **El valor científico de los datos:** En la sesión 7, dedica tiempo a que los chicos entiendan que los datos no son estáticos y que graficar la información recopilada les permite predecir comportamientos climáticos reales del aula.

¡Todo listo para arrancar el proyecto!
