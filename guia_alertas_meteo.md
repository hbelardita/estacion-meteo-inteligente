# Guía de Alertas: Semáforo y Buzzer 🚨

Esta guía detalla el funcionamiento de las alarmas visuales y sonoras de la **Estación Meteorológica Inteligente** (adaptada para la placa Faniot Kitmaker 2.0).

El sistema evalúa de manera constante los valores de **Temperatura** y **Humedad de Suelo** para disparar las alarmas, ignorando deliberadamente los niveles de luz y humedad ambiental.

## 🔴 Alerta Crítica (Peligro)

Se dispara cuando las condiciones son extremas.

* **Condiciones de Activación (basta que se cumpla una):**
  * **Temperatura:** Llega o supera los **40.0 °C**
  * **Humedad del Suelo:** Cae al **20% o menos** (muy seco)
* **Respuesta del Sistema:**
  * **Semáforo (Neopíxeles):** Color ROJO.
  * **Buzzer (GPIO12):** Pitido corto y agudo (100 milisegundos a 2500 Hz). Es un sonido molesto de emergencia.

> [!CAUTION]
> Cuando se activa esta alerta, es necesario revisar las plantas o regar la tierra de inmediato.

---

## 🟡 Alerta de Advertencia (Precaución)

Se dispara cuando las condiciones no son ideales y están empeorando, pero aún no llegan a niveles críticos.

* **Condiciones de Activación (basta que se cumpla una):**
  * **Temperatura:** Llega o supera los **35.0 °C**
  * **Humedad del Suelo:** Cae al **40% o menos** (empezando a secarse)
* **Respuesta del Sistema:**
  * **Semáforo (Neopíxeles):** Color AMARILLO/NARANJA.
  * **Buzzer (GPIO12):** Pitido más largo y grave (300 milisegundos a 1000 Hz).

> [!WARNING]
> Esta alerta indica que hay que estar atentos. Es el momento ideal para empezar a regar de a poco, o revisar si la estación está expuesta al sol directo en exceso.

---

## 🟢 Estado Normal

Se activa cuando todas las variables están dentro del rango ideal y seguro.

* **Condiciones de Activación (deben cumplirse ambas):**
  * **Temperatura:** Menor a **35.0 °C**
  * **Humedad del Suelo:** Mayor al **40%**
* **Respuesta del Sistema:**
  * **Semáforo (Neopíxeles):** Color VERDE.
  * **Buzzer (GPIO12):** Completamente en SILENCIO.

---

## ⚙️ Cómo Cambiar los Umbrales

> [!TIP]
> Si deseas ajustar las temperaturas o niveles de humedad que disparan estas alertas, busca y modifica las siguientes constantes en la parte superior de tu archivo [main.cpp](file:///home/horacio/Documents/tmp/estacion-meteo-inteligente/src/main.cpp):

```cpp
// ==========================================
// 📊 CONSTANTES Y UMBRALES CONFIGURABLES
// ==========================================
const float TEMP_LIMITE_ALTA = 35.0;      
const float TEMP_LIMITE_CRITICA = 40.0;    
const int SUELO_LIMITE_BAJO = 40;         
const int SUELO_LIMITE_CRITICO = 20; 
```
