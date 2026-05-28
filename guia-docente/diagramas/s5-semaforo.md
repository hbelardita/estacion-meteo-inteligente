# Diagrama de Conexión: Semáforo y Alertas (Sesión 5)
## Indicadores Visuales y Sonoros

Este diagrama muestra cómo conectar tres diodos LEDs (Verde, Amarillo y Rojo) junto con sus resistencias limitadoras de corriente de 220Ω y un buzzer pasivo para alertar sobre niveles extremos de temperatura, humedad o mala calidad del aire.

---

## 📋 Tabla de Conexiones Pin a Pin

| Componente | Pin en Arduino Uno | Nota / Descripción |
| :---: | :---: | :--- |
| **LED Verde (Ánodo / Pata larga)** | **D8** | Conectar en serie con resistencia de 220Ω al pin D8. Indica estado Normal. |
| **LED Amarillo (Ánodo / Pata larga)** | **D9** | Conectar en serie con resistencia de 220Ω al pin D9. Indica Advertencia. |
| **LED Rojo (Ánodo / Pata larga)** | **D10** | Conectar en serie con resistencia de 220Ω al pin D10. Indica Alerta / Peligro. |
| **Cátodos de LEDs (Pata corta)** | **GND** | Todos los cátodos van conectados a la línea de tierra común (GND). |
| **Buzzer (+) (Pata larga o pin "+")** | **D3** | Entrada de señal para generar sonidos. |
| **Buzzer (-) (Pata corta o pin "-")** | **GND** | Conectar a la línea de tierra común (GND). |

---

## 🔌 Esquema de Conexiones (Diagrama ASCII)

```text
         Arduino Uno
       ┌───────────────┐
       │            D8 ├───(Verde)──────[ 220Ω ]────(A) LED Verde (C)────┐
       │               │                                                 │
       │            D9 ├───(Amarillo)───[ 220Ω ]────(A) LED Amar. (C)────┤
       │               │                                                 │
       │           D10 ├───(Rojo)───────[ 220Ω ]────(A) LED Rojo  (C)────┤
       │               │                                                 │
       │            D3 ├───(Azul/Gris)──────────────(+) Buzzer    (-)────┤
       │               │                                                 │
       │           GND ├───(Negro)───────────────────────────────────────┴─ Tierra Común (GND)
       └───────────────┘
       
       * Leyenda del LED: (A) = Ánodo (Pata larga), (C) = Cátodo (Pata corta, lado plano del LED)
```

---

## ⚠️ Errores Comunes y Consejos del Detective de Hardware

1. **LEDs conectados al revés:** Los LEDs son componentes polarizados. Si se conectan al revés, no se quemarán, pero no encenderán. Recuerda: la pata **larga** (Ánodo) va hacia la señal del Arduino (pasando por la resistencia) y la pata **corta** (Cátodo) va a la línea negativa de tierra (GND).
2. **Olvidar las resistencias o usar el valor incorrecto:** Si conectas los LEDs directamente a los pines del Arduino sin resistencia de 220Ω, circulará demasiada corriente y quemarás el LED o dañarás el pin del Arduino. Si usas resistencias muy altas (como 10kΩ), el LED prenderá con un brillo tan débil que casi no se verá.
3. **Buzzer ruidoso continuo:** Si el buzzer pita sin detenerse apenas enciendes la placa, verifica tu código. Los buzzers pasivos necesitan la función `tone()` para oscilar a una frecuencia específica y sonar como notas musicales. Si los configuras simplemente con `digitalWrite(3, HIGH)`, emitirán un zumbido constante y forzarán la placa.
