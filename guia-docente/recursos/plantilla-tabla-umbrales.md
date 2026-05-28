# Ficha de Trabajo: Tabla de Umbrales del Semáforo Ambiental
## Nombre del Equipo: ____________________________________
## Integrantes:
1. ____________________________________
2. ____________________________________
3. ____________________________________
4. ____________________________________

---

## 🎯 Instrucciones de Trabajo

Antes de escribir la programación en el microcontrolador, debemos definir con precisión matemática a partir de qué números exactos nuestra estación decidirá prender la luz Verde (Seguro), la luz Amarilla (Advertencia) o la luz Roja (Peligro). 

Completen esta tabla investigando valores reales de temperatura confort y límites perjudiciales de calidad de aire en sus bitácoras.

---

## 📊 Definición de Umbrales del Equipo

| Nivel de Alerta | Variable Física | Rango Elegido (Números) | Estado Físico del Semáforo | Acción Recomendada para los Humanos |
| :---: | :--- | :--- | :---: | :--- |
| **ÓPTIMO / NORMAL** | **Temperatura**<br>**Humedad**<br>**Gases (MQ-135)** | Menor a ____ °C<br>Menor a ____ %<br>Menor a ____ unidades | 🟢 **LED Verde Encendido**<br>🔇 Buzzer en Silencio | *¡El ambiente es agradable! Es un gran momento para estudiar o jugar sin problemas.* |
| **ADVERTENCIA** | **Temperatura**<br>**o Humedad** | Entre ____ y ____ °C<br>Mayor a ____ % | 🟡 **LED Amarillo Encendido**<br>🔊 Buzzer con Pitido Lento | *El ambiente está caluroso o muy húmedo. Ventilar el lugar o encender ventiladores.* |
| **CRÍTICO / PELIGRO** | **Temperatura**<br>**o Gases (MQ-135)** | Mayor a ____ °C<br>Mayor a ____ unidades | 🔴 **LED Rojo Encendido**<br>🚨 Buzzer con Pitido Rápido | *¡Alerta ambiental! Aire muy sucio o temperatura extrema. Salir del lugar o abrir ventanas urgente.* |

---

## ✏️ Preguntas para el Equipo Técnico

1. **¿Por qué decidieron que el LED Amarillo no dependiera del sensor MQ-135 en su diseño?**
   __________________________________________________________________________________________
   __________________________________________________________________________________________

2. **Si el sensor MQ-135 da un valor analógico crudo de 420, ¿qué luz se encenderá en su semáforo y qué debería hacer la clase ante esta alerta?**
   __________________________________________________________________________________________
   __________________________________________________________________________________________

3. **¿Cuál es la diferencia entre el umbral de advertencia y el umbral de peligro para la Temperatura?**
   __________________________________________________________________________________________
   __________________________________________________________________________________________
