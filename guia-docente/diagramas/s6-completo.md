# Diagrama de Conexión: Integración Completa (Sesión 6)
## Circuito Final Estación Meteorológica Inteligente

Este diagrama muestra la integración de **todos** los componentes del proyecto (DHT11, MQ-135, LCD Paralelo de 16 pines, potenciómetro de contraste, LEDs del semáforo y buzzer pasivo) conectados simultáneamente a una sola placa Arduino Uno.

---

## 📋 Distribución Completa de Pines (Pinout)

Para esta sesión, la organización de los cables en la protoboard es crítica. Utiliza los canales longitudinales superior e inferior de la protoboard para crear las líneas comunes de alimentación (**5V** en rojo y **GND** en negro) y colocar el potenciómetro de contraste cerca del display LCD.

| Pin Arduino | Tipo | Componente | Descripción de la Conexión |
| :---: | :---: | :--- | :--- |
| **5V** | Salida | Protoboard Canal (+) | Distribuye energía de 5V a DHT11, MQ-135, LCD (VDD y LED+) y Potenciómetro. |
| **GND** | Tierra | Protoboard Canal (-) | Conecta a tierra común de todos los sensores, LCD (VSS, RW, LED-), Buzzer y LEDs. |
| **D2** | Digital (I) | **DHT11 DATA** | Lee datos del sensor DHT11 (con resistencia Pull-up si el módulo no la tiene integrada). |
| **D3** | Digital (O) | **Buzzer (+)** | Genera tonos de advertencia acústicos (se reubicó para liberar el pin 11). |
| **D4** | Digital (O) | **LCD D4 (Pin 11)**| Bit de datos 4 para la interfaz del display LCD. |
| **D5** | Digital (O) | **LCD D5 (Pin 12)**| Bit de datos 5 para la interfaz del display LCD. |
| **D6** | Digital (O) | **LCD D6 (Pin 13)**| Bit de datos 6 para la interfaz del display LCD. |
| **D7** | Digital (O) | **LCD D7 (Pin 14)**| Bit de datos 7 para la interfaz del display LCD. |
| **D8** | Digital (O) | **LED Verde** | Activa indicador de estado óptimo (requiere resistencia de 220Ω). |
| **D9** | Digital (O) | **LED Amarillo** | Activa advertencia intermedia (requiere resistencia de 220Ω). |
| **D10** | Digital (O) | **LED Rojo** | Activa alerta de peligro (requiere resistencia de 220Ω). |
| **D11** | Digital (O) | **LCD EN (Pin 6)**  | Pin de habilitación (Enable) del display LCD. |
| **D12** | Digital (O) | **LCD RS (Pin 4)**  | Pin de selección de registro (Register Select) del LCD. |
| **A0** | Analógico (I) | **MQ-135 AO** | Mide concentración analógica de gases y calidad del aire. |

---

## 🔌 Esquema Completo del Circuito (Diagrama ASCII)

```text
                                       PROTOBOARD (Líneas Comunes)
    ┌───────────────────────────────────────────────────────────────────────────────┐
    │  (+)  5V Common ──────────────────┬─────────────────┬──────────────┬────────  │
    │  (-)  GND Common ───────┬─────────┼───────┬─────────┼───────┬──────┼────────  │
    └─────────────────────────┼─────────┼───────┼─────────┼───────┼──────┼────────┘
                              │         │       │         │       │      │
                             (C)       (A)     (-)       (+)     GND    VCC
                            LEDs      LEDs   Buzzer    Buzzer   MQ-135 MQ-135
                              │         │       │         │       │      │
     Arduino Uno              │         │       │         │       │      │
   ┌─────────────┐            │         │       │         │       │      │
   │          5V ├────────────┼─────────┘       │         │       │      │
   │         GND ├────────────┘                 │         │       │      │
   │             │                              │         │       │      │
   │          D2 ├────────[ 10kΩ Pullup ]───────┼─────────┼───────┼──────┼── DATA (DHT11)
   │             │        (Conectado a 5V)      │         │       │      │
   │          D3 ├──────────────────────────────┼─────────┘       │      │
   │             │                              │                 │      │
   │          D4 ├──────────────────────────────┼─────────────────┼──────┼── D4 (LCD Pin 11)
   │          D5 ├──────────────────────────────┼─────────────────┼──────┼── D5 (LCD Pin 12)
   │          D6 ├──────────────────────────────┼─────────────────┼──────┼── D6 (LCD Pin 13)
   │          D7 ├──────────────────────────────┼─────────────────┼──────┼── D7 (LCD Pin 14)
   │             │                              │                 │      │
   │          D8 ├────────[ 220Ω ]──────────────┼─────────────────┼──────┼── (A) LED Verde
   │          D9 ├────────[ 220Ω ]──────────────┼─────────────────┼──────┼── (A) LED Amarillo
   │         D10 ├────────[ 220Ω ]──────────────┼─────────────────┼──────┼── (A) LED Rojo
   │         D11 ├──────────────────────────────┼─────────────────┼──────┼── EN (LCD Pin 6)
   │         D12 ├──────────────────────────────┼─────────────────┼──────┼── RS (LCD Pin 4)
   │             │                              │                 │      │
   │          A0 ├──────────────────────────────┼─────────────────┼──────┼── AO (MQ-135)
   └─────────────┘                              │                 │      │
                                                │                 │      │
                                               GND               GND    VCC (LCD Pin 2)
                                             DHT11             (Pin 1)
                                                               
      * Nota LCD Paralelo:
        - VSS (Pin 1) y RW (Pin 5) y K (Pin 16) van a GND.
        - VDD (Pin 2) va a 5V.
        - A (Pin 15) va a 5V a través de una resistencia de 220Ω.
        - V0 (Pin 3) va al pin central de un potenciómetro de 10kΩ cuyos extremos van a 5V y GND.
```

---

## 🔍 Guía de Depuración de Fallas para Prototipos Integrados

Cuando se conectan tantos componentes a la vez (especialmente el LCD paralelo con sus 12 cables necesarios), las probabilidades de cometer pequeños errores aumentan. Enseña a tus alumnos a revisar las conexiones en este orden (el método del checklist de ingeniería):

1. **Chequeo de Alimentación (Luz de la Placa):** Si al conectar el Arduino a la computadora la luz "ON" de la placa parpadea o se apaga por completo, ¡desconéctala de inmediato! Hay un **cortocircuito** directo entre 5V y GND. Revisa minuciosamente dónde se cruzan los cables de corriente en la protoboard.
2. **Contraste del LCD:** Si la retroiluminación enciende pero no ves texto, gira lentamente el potenciómetro de contraste conectado al Pin 3 (V0) del LCD. Las letras suelen aparecer en un rango muy estrecho del giro.
3. **Cables cruzados en el bus de datos del LCD:** Verifica dos veces que los cables conectados a los pines D4, D5, D6, D7 de Arduino vayan exactamente a los pines correspondientes del LCD (Pines 11, 12, 13 y 14 respectivamente). Si el LCD muestra caracteres extraños o símbolos raros, el problema suele ser cables de datos cruzados.
4. **RW no conectado a GND:** Si olvidas mandar el pin 5 (RW) a GND, el LCD se pondrá en modo lectura y ignorará las instrucciones enviadas por Arduino.
5. **Verificación de Tierras:** Asegúrate de que todos los pines marcados como GND de los sensores, LEDs, buzzer y LCD terminen en el canal común de tierra que conecta a la placa Arduino.
