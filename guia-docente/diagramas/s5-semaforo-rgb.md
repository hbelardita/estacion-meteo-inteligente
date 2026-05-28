# Diagrama de Conexión — Variante LED RGB (Cátodo Común)

Esta variante reemplaza los 3 LEDs individuales por un único **LED RGB de Cátodo Común**. Esto simplifica el espacio en la protoboard y permite introducir el concepto físico de la **síntesis aditiva de color** (cómo obtener amarillo mezclando rojo y verde).

---

## Pinout del LED RGB

Un LED RGB tiene 4 patas. La pata más larga suele ser el **Cátodo Común** (tierra / GND).

```
         ┌───┐
         │   │
         └───┘
        │ │ │ │
        │ │ │ │
        R C G B
        │ │ │ │
        │ │ │ └─ Ánodo Azul (Pin 10)
        │ │ └─── Ánodo Verde (Pin 9)
        │ └───── Cátodo Común (GND)
        └─────── Ánodo Rojo (Pin 8)
```

---

## Conexión al Arduino Uno

| Pin LED RGB | Componente intermedio | Pin Arduino Uno |
|:---|:---|:---|
| **R (Rojo)** | Resistencia 220Ω | **Pin 8** |
| **- (Cátodo / Pata larga)** | Directo a tierra | **GND** |
| **G (Verde)** | Resistencia 220Ω | **Pin 9** |
| **B (Azul)** | Resistencia 220Ω | **Pin 10** |
| **Buzzer (+)** | Directo | **Pin 3** |
| **Buzzer (-)** | Directo | **GND** |

---

## Diagrama ASCII del Circuito

```
            Arduino Uno
          ┌─────────────┐
          │             │
          │         GND ├───────┬────────────────────────── GND (Buzzer -)
          │             │       │
          │             │       └─────── [Cátodo Común]    ─┐
          │             │                                   │
          │          D8 ├───────[ 220Ω ]──── [Ánodo Rojo]   ├── LED RGB
          │          D9 ├───────[ 220Ω ]──── [Ánodo Verde]  │
          │         D10 ├───────[ 220Ω ]──── [Ánodo Azul]   ─┘
          │             │
          │          D3 ├────────────────────────────────── (+) Buzzer
          │             │
          └─────────────┘
```

---

## 🕵️ Detective de Hardware (Errores comunes)

1. **El color azul no enciende o enciende muy tenue:**
   * Verifica que la resistencia esté bien colocada y que el pin 10 esté configurado como `OUTPUT`. Aunque no usamos luz azul pura para el semáforo tradicional, el pin debe estar conectado para pruebas y futuras expansiones (como indicar aire frío o húmedo).
2. **Los colores están cruzados (ej. programo verde y prende rojo):**
   * Es muy común confundir las patas R, G y B del LED. Si la pata larga (cátodo) está en GND, intercambia los cables en los pines 8, 9 y 10 hasta que coincidan con su color.
3. **¿Ánodo Común o Cátodo Común?:**
   * **Este diagrama es para Cátodo Común** (la pata común va a GND). Si tu LED es de **Ánodo Común** (la pata larga debe ir a 5V), la lógica del programa se invierte: para apagar un color debes poner el pin en `HIGH`, y para encenderlo en `LOW`.
4. **Mezcla de color amarillo:**
   * Dado que un LED RGB no tiene un filamento amarillo físico, encendemos el **Rojo** y el **Verde** juntos. En algunos LEDs, debido a la diferencia de brillo, el amarillo puede verse un poco anaranjado o verdoso. Esto se soluciona modificando la corriente (cambiando el valor de la resistencia) o usando PWM (`analogWrite`).
