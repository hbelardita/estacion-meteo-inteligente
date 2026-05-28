# Guía — Cómo Usar los Archivos Markdown como Presentaciones Navegables

Todos los archivos de la guía docente están escritos en **Markdown (`.md`)**. Esto te permite editarlos fácilmente como texto plano, pero también existen herramientas que pueden transformarlos automáticamente en **diapositivas visuales** o **sitios web interactivos tipo libro** para proyectar en el aula ante tus estudiantes.

A continuación, te presentamos las 3 formas más sencillas y potentes de lograrlo:

---

## 🛠️ Opción 1: Diapositivas con Marp (Recomendada en VS Code)

Dado que estás utilizando VS Code (`code .`), la forma más rápida y profesional de crear presentaciones es usando **Marp (Markdown Presentation Ecosystem)**.

### Paso a paso:
1. **Instala la extensión:** En VS Code, ve a la sección de extensiones (`Ctrl + Shift + X`), busca **"Marp for VS Code"** e instálala.
2. **Crea las diapositivas:** Marp interpreta los guiones horizontales `---` como saltos de página (diapositivas).
3. **Activa la vista previa:** Abre cualquiera de tus archivos `.md` de la carpeta `guia-docente/sesiones/` y haz clic en el icono del **Marp (un triángulo azul con doble flecha)** en la esquina superior derecha de VS Code y selecciona **"Toggle Marp feature on current Markdown"**. Luego, abre la previsualización de Markdown de VS Code (`Ctrl + Shift + V`).
4. **Exportar a PDF o HTML:** Presiona el botón de Marp en VS Code y selecciona **"Export Slide Deck..."**. Podrás guardarlo como:
   * **HTML interactivo:** Una presentación navegable con las flechas del teclado en cualquier navegador web.
   * **PDF:** Listo para imprimir o compartir.

### Ejemplo de cómo estructurar un archivo para Marp:
Solo debes añadir esta cabecera en el inicio de tu archivo Markdown para que Marp le aplique un tema visual elegante:
```markdown
---
marp: true
theme: gaia
_class: lead
paginate: true
backgroundColor: #f5f5f5
color: #333
---

# Sesión 5: Semáforo Ambiental 🚦
## NovaMakers Avanzado

---

# 🎯 Objetivos de la clase

1. Aprender a programar condicionales.
2. Controlar la potencia de un buzzer.
3. Crear alertas visuales.
```

---

## 🌐 Opción 2: Docsify (Sitio Web Navegable Instantáneo)

Si en lugar de diapositivas quieres tener un **sitio web estilo manual o libro digital** donde puedas navegar por todas las sesiones y diagramas con un menú lateral indexado, **Docsify** es la mejor opción porque no requiere que instales programas complejos ni que compiles nada.

Hemos configurado Docsify directamente dentro de la carpeta `guia-docente/` para que los enlaces se resuelvan de forma correcta y nativa.

### Cómo utilizar tu nueva Wiki Web:
1. Asegúrate de tener instalado Python en tu computadora (suele venir preinstalado en Linux) o cualquier servidor web local.
2. Abre tu terminal en la carpeta `/home/horacio/Documents/tmp/estacion-meteo-inteligente/guia-docente` y ejecuta:
   * Con Python: `python3 -m http.server 3000`
   * Con Node.js (si lo usas): `npx serve` (dentro de esa misma carpeta)
3. Abre tu navegador web e ingresa a `http://localhost:3000`.
4. ¡Listo! Verás un sitio web moderno con diseño interactivo, barra de búsqueda y un menú lateral navegable para acceder rápidamente a las 8 sesiones, los diagramas de circuitos y los códigos de programación de manera fluida.


---

## 💻 Opción 3: Herramientas Web Rápidas (Sin instalar nada)

Si estás en otra computadora y necesitas proyectar de inmediato:

1. **Slidev (slidev.org) / Sli.dev:** Una herramienta muy popular basada en la web para desarrolladores que convierte Markdown en hermosas diapositivas interactivas en HTML5.
2. **HackMD (hackmd.io):** 
   * Sube o copia el contenido de cualquiera de tus archivos `.md` a HackMD.
   * Haz clic en el botón **Menu** y selecciona **Slide Mode**.
   * HackMD convertirá automáticamente los títulos e ítems separados por `---` en una presentación navegable.
3. **Marp Web (web.marp.app):** Puedes arrastrar y soltar tus archivos `.md` directamente en esta web para verlos como diapositivas al instante y descargarlos en HTML sin instalar extensiones de VS Code.
