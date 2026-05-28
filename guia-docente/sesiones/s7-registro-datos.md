# Sesión 7: El Tiempo Pasa — Registro de Datos (Series Temporales)
## Trayecto: NovaMakers Avanzado (9 a 12 años)

En esta sesión, los estudiantes actuarán como científicos ambientales de datos. Programarán su estación para enviar datos climáticos formateados como valores separados por comas (CSV) por el puerto serie. Aprenderán a recopilar estos datos de forma continua durante un período de tiempo, copiarlos en una hoja de cálculo (Excel o Google Sheets), y generar gráficos estadísticos para analizar tendencias y patrones del entorno.

---

## 🎯 Objetivos de Aprendizaje

Al finalizar la sesión, los estudiantes serán capaces de:
1. Comprender el concepto de "serie temporal" y su importancia en la investigación científica.
2. Identificar el formato de intercambio de datos CSV (valores separados por comas).
3. Importar datos de texto plano a una hoja de cálculo electrónica y generar un gráfico de líneas para representar tendencias.

---

## 📦 Materiales Necesarios

* Prototipo de la Estación Meteorológica Inteligente armada en su carcasa.
* Cable USB conectado a la computadora.
* Computadora con PlatformIO y una hoja de cálculo instalada (Excel o Google Sheets abierto en el navegador).
* Ficha de trabajo: [Plantilla de Informe Técnico](../recursos/plantilla-informe-tecnico.md).
* Código de registro CSV: [s7_registro_datos.cpp](../codigo/s7_registro_datos.cpp).

---

## ⏱️ Estructura de la Sesión

### 🎬 Inicio: Actividad Disparadora (~15 minutos)
1. **La Máquina del Tiempo:** Haz la siguiente pregunta: *"Si medimos la calidad del aire del aula justo al entrar por la mañana y nos da excelente, ¿podemos asegurar que la calidad del aire sigue siendo excelente al mediodía luego de estar 4 horas con la ventana cerrada?"*. Conversen sobre cómo cambian las variables con el tiempo y por qué los científicos necesitan registrar datos constantemente (series temporales) para tomar decisiones de salud pública.
2. **El Lenguaje CSV:** Explica que el CSV (Comma Separated Values) es el lenguaje universal que usan las computadoras de todo el mundo para intercambiar bases de datos de forma simple y liviana.

### 🛠️ Desarrollo: Actividad Principal (~60 minutos)
1. **Subir el Programa de Registro:**
   * El **Líder de Software** carga el código [s7_registro_datos.cpp](../codigo/s7_registro_datos.cpp) en el Arduino.
   * Compila y sube el programa.
2. **Recolección de Datos en Vivo (Muestreo):**
   * Abran el Monitor Serial de PlatformIO. Observen cómo cada 5 segundos aparece una nueva línea de texto con números separados por comas (Tiempo, Temp, Humedad, CalidadAire).
   * Dejen la estación registrando datos durante 10 o 15 minutos en el aula.
   * **Dinámica para generar variaciones:** Durante el tiempo de registro, provoquen un cambio en la estación: soplen el sensor a los 2 minutos, ventilen abriendo la ventana a los 4 minutos o acerquen alcohol al sensor de aire a los 6 minutos.
3. **Migración a la Planilla de Cálculo:**
   * Detengan el autodesplazamiento del Monitor Serial.
   * Seleccionen todas las líneas de datos transmitidas, hagan clic derecho y seleccionen **Copiar**.
   * Abran una hoja de cálculo en Excel o Google Sheets.
   * Peguen los datos en la primera celda (A1).
   * **El Truco del Mago (Texto a Columnas):** Utilicen la función "Texto en columnas" indicando que el carácter separador es la **coma (,)**. ¡Verán cómo los datos se ordenan instantáneamente en columnas ordenadas!
4. **Graficar los Cambios:**
   * Seleccionen las columnas correspondientes a la Temperatura o Calidad del Aire.
   * Inserten un **Gráfico de Líneas (Dispersión con líneas suavizadas)**.
   * El **Científico de Datos** rotula los ejes (Eje X: Tiempo en segundos, Eje Y: Temperatura o Lectura del Gas) y exporta el gráfico al [Plantilla de Informe Técnico](../recursos/plantilla-informe-tecnico.md).

### 📝 Cierre: Reflexión y Bitácora (~15 minutos)
1. **Análisis de Resultados:** Miren los gráficos de cada grupo. Pregúntales: *"¿En qué segundo exacto ocurrió el pico de humedad en su gráfico? ¿Cuánto tiempo tardó el sensor de calidad del aire en recuperarse tras retirar el perfume?"*.
2. **Registro:** Peguen el gráfico impreso o dibujen a mano alzada las curvas obtenidas en su bitácora.

---

## 💡 Tips para el Docente Facilitador

* **El separador en Excel (Comas vs Punto y Coma):** Dependiendo de la configuración regional de la computadora (idioma español o inglés), Excel puede usar la coma (`,`) o el punto y coma (`;`) como separador de columnas. Si al pegar los datos no se separan bien, muestra a los alumnos cómo usar la herramienta "Texto en Columnas" en la pestaña "Datos" de Excel para forzar el separador por coma.
* **Copiar sin los textos extraños:** Asegúrate de que los estudiantes copien únicamente las filas de números con comas, ignorando cualquier mensaje de inicio o error de la placa.

---

## 🚀 Extensiones (Para grupos veloces)
Pide a los grupos que calculen funciones estadísticas automáticas en su planilla de cálculo usando las fórmulas matemáticas básicas: `=PROMEDIO()`, `=MAX()`, y `=MIN()` para encontrar los valores extremos registrados durante la clase.
