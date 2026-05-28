# Diagrama de Conexión: LCD 16x2 Paralelo (Sesión 4)
## Interfaz de Visualización de Datos (Conexión Tradicional de 16 Pines)

Este diagrama detalla cómo conectar la pantalla LCD de 16 caracteres y 2 líneas de forma directa (paralela de 4 bits) a la placa Arduino Uno utilizando la librería nativa `<LiquidCrystal.h>`, un potenciómetro de 10kΩ para ajustar el contraste, y una resistencia para la retroiluminación.

---

## 📋 Tabla de Conexiones Pin a Pin

| Pin del LCD Paralelo | Pin en Arduino Uno / Componente | Color Sugerido | Nota / Descripción |
| :---: | :---: | :---: | :--- |
| **1 (VSS)** | **GND** | Negro | Conexión a tierra común (0 Voltios). |
| **2 (VDD)** | **5V** | Rojo | Alimentación de energía (+5 Voltios). |
| **3 (V0)** | **Pin central del Potenciómetro** | Blanco / Amarillo | Voltaje de contraste. Regula la visibilidad de las letras. |
| **4 (RS)** | **Pin 12** | Marrón | Selección de Registro (Command/Data Register). |
| **5 (RW)** | **GND** | Negro | Modo lectura/escritura (GND permanente = Escritura). |
| **6 (E / Enable)** | **Pin 11** | Naranja | Habilitación de la pantalla (sincronización). |
| **7 a 10 (D0-D3)** | **Sin conectar** | - | Pines de datos de 8 bits (no se usan en modo 4 bits). |
| **11 (D4)** | **Pin 4** | Verde | Bit de datos 4 (Línea de datos de 4 bits). |
| **12 (D5)** | **Pin 5** | Azul | Bit de datos 5 (Línea de datos de 4 bits). |
| **13 (D6)** | **Pin 6** | Morado | Bit de datos 6 (Línea de datos de 4 bits). |
| **14 (D7)** | **Pin 7** | Gris | Bit de datos 7 (Línea de datos de 4 bits). |
| **15 (A / LED+)** | **5V (Vía Resistencia 220Ω)** | Rojo | Ánodo del LED de retroiluminación (+5V con R220Ω). |
| **16 (K / LED-)** | **GND** | Negro | Cátodo del LED de retroiluminación (GND). |

---

## 🔌 Esquema de Conexiones (Diagrama ASCII)

```text
          Arduino Uno
        ┌───────────────┐
        │            5V ├───(Rojo)─────────────────────── Bus de +5V
        │           GND ├───(Negro)────────────────────── Bus de GND
        │               │
        │            12 ├───(Marrón)── RS (Pin 4)
        │            11 ├───(Naranja)─ EN (Pin 6)
        │               │
        │             4 ├───(Verde)─── D4 (Pin 11)
        │             5 ├───(Azul)──── D5 (Pin 12)
        │             6 ├───(Morado)── D6 (Pin 13)
        │             7 ├───(Gris)──── D7 (Pin 14)
        └───────────────┘

                 [ Potenciómetro de Contraste ]
                   ┌──────────────┐
                   │  Ext1   Vout   Ext2 │
                   └───o──────o──────o───┘
                       │      │      │
                      GND    V0(Pin3) 5V

                                        LCD 16x2 Paralelo (16 Pines)
                                       ┌────────────────────────────────────────────────────────┐
                                       │ VSS VDD V0  RS  RW  E   D0 D1 D2 D3 D4  D5  D6  D7  A   K  │
                                       │  1   2   3   4   5   6   7  8  9  10 11  12  13  14  15  16 │
                                       │  o   o   o   o   o   o   o  o  o  o  o   o   o   o   o   o  │
                                       │  │   │   │   │   │   │               │   │   │   │   │   │  │
                                       │  │   │   │   │   └─GND               │   │   │   │  ┌┴┐  │  │
                                       │  │   │   │   └───────────────────────┼───┼───┼───┼─┤R├─5V │  (R = 220Ω)
                                       │  │   │   └───────────────────────────┼───┼───┼───┼─└┬┘      │
                                       │  │   └───────────────────────────────┼───┼───┼───┼──┼───────┘
                                       │  └───────────────────────────────────┼───┼───┼───┼──┼─────── GND
                                       │                                      │   │   │   │  └─────── GND (K)
                                       └──────────────────────────────────────┴───┴───┴───┴──────────────┘
```

---

## ⚠️ Errores Comunes y Consejos del Detective de Hardware

1. **Pantalla encendida pero vacía (sin texto):** Este es el error número uno. Si la pantalla brilla pero no muestra las letras, gira suavemente la perilla del **potenciómetro de contraste** (conectado a V0, Pin 3). Esto regula la visualización de los caracteres.
2. **Confundir los pines RS y EN (Enable):** Asegúrate de que RS (Pin 4 del LCD) esté conectado al Pin 12 de tu Arduino, y que EN (Pin 6 del LCD) esté conectado al Pin 11 de tu Arduino. Si los intercambias, la pantalla no entenderá los datos enviados.
3. **Olvidar la resistencia del Backlight (LED+):** El Pin 15 (A) alimenta el LED trasero que ilumina la pantalla. **Siempre** se debe usar una resistencia limitadora (típicamente de 220Ω) conectada a 5V para evitar quemar este LED.
4. **Olvidar conectar RW a GND:** El Pin 5 (RW) determina si leemos o escribimos en el LCD. Para enviar datos desde Arduino, este pin debe estar firmemente conectado a tierra (GND).
