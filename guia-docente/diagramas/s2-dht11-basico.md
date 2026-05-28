# Diagrama de Conexión: DHT11 Básico (Sesión 2)
## Medición de Temperatura y Humedad

Este diagrama muestra cómo conectar el sensor de temperatura y humedad **DHT11** a la placa Arduino Uno. Se incluye una resistencia de pull-up de 10kΩ para asegurar la estabilidad en la línea de datos.

---

## 📋 Tabla de Conexiones Pin a Pin

| Pin del Sensor DHT11 | Pin en Arduino Uno | Nota / Descripción |
| :---: | :---: | :--- |
| **VCC (Pin 1)** | **5V** | Alimentación de energía (+5 Voltios) |
| **DATA (Pin 2)** | **D2 (Digital 2)** | Línea de comunicación de datos. Requiere resistencia de pull-up a 5V. |
| **NC (Pin 3)** | *No Conectar* | No se utiliza en este sensor. |
| **GND (Pin 4)** | **GND** | Conexión de tierra (0 Voltios) |

*Nota: Si estás usando un módulo DHT11 ya montado en una plaquita de 3 pines, normalmente viene rotulado como **VCC (+)**, **GND (-)** y **OUT (S)**. En ese caso, el módulo suele traer integrada la resistencia de pull-up y no es necesario agregarla externamente.*

---

## 🔌 Esquema de Conexiones (Diagrama ASCII)

```text
         Arduino Uno
       ┌───────────────┐
       │            5V ├───(Rojo)───┬─────────────── VCC (Pin 1)
       │               │            │
       │               │          [10kΩ] (Resistencia de Pull-up)
       │               │            │
       │            D2 ├───(Azul)───┴─────────────── DATA (Pin 2)
       │               │
       │               │                            NC (Pin 3 - Vacío)
       │               │
       │           GND ├───(Negro)────────────────── GND (Pin 4)
       └───────────────┘
                                                       DHT11
                                                      ┌─────┐
                                                      │ █ █ │
                                                      │ █ █ │
                                                      └┬┬┬┬┘
                                                       ││││
                                                       1234
```

---

## ⚠️ Errores Comunes y Consejos del Detective de Hardware

1. **Invertir VCC y GND:** El sensor DHT11 se calienta rápidamente si se conecta al revés y puede dañarse permanentemente. Verifica siempre con cuidado que el pin VCC vaya a los 5V y el pin GND a tierra antes de encender la placa.
2. **Olvidar la resistencia de pull-up:** Si usas el sensor suelto de 4 pines y no colocas la resistencia de 10kΩ entre DATA y VCC, el Arduino leerá valores erróneos o devolverá error de lectura.
3. **Pines doblados:** A veces los terminales del sensor DHT11 son muy delgados y se doblan al insertarlos en la protoboard, haciendo falso contacto. Asegúrate de introducirlos firmemente.
