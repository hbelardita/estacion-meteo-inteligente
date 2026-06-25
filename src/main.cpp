/**
 * Estación Meteorológica Inteligente — Código Definitivo Integrado (ESP32 - Faniot Kitmaker 2.0)
 * Proyecto final para el trayecto NovaMakers Avanzado
 *
 * Descripción: Integra lectura de temperatura y humedad (HTU21D),
 * luz ambiente (TEMT6000), y humedad de suelo (Analógico).
 * Visualización en OLED I2C 128x64. Control de semáforo ambiental con Neopíxeles
 * y alertas acústicas (buzzer pasivo). Envío de datos como CSV.
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_HTU21DF.h>
#include <Adafruit_NeoPixel.h>
#include <LittleFS.h>

// ==========================================
// 🌐 CONFIGURACIÓN DEL SERVIDOR WIFI (OPCIONAL)
// ==========================================
// Comentar la siguiente línea para desactivar el servidor Web y el WiFi AP
#define ENABLE_WIFI_SERVER

#ifdef ENABLE_WIFI_SERVER
#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Estacion_Meteo";
const char* password = ""; // Red abierta para fácil acceso en el aula

WebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Estación Meteorológica</title>
  <style>
    body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; background-color: #121212; color: #ffffff; text-align: center; margin: 0; padding: 20px;}
    .container { max-width: 800px; margin: auto; }
    .grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(180px, 1fr)); gap: 15px; margin-bottom: 25px; }
    .card { background: #1e1e1e; padding: 20px; border-radius: 8px; box-shadow: 0 4px 6px rgba(0,0,0,0.2); }
    .val { font-size: 2em; font-weight: bold; color: #4CAF50; margin-top: 10px; }
    .temp-val { color: #ff4d4d; }
    .hum-val { color: #36a2eb; }
    .suelo-val { color: #8bc34a; }
    .luz-val { color: #ffeb3b; }
    canvas { background-color: #1e1e1e; border-radius: 8px; margin-top: 20px; box-shadow: 0 4px 6px rgba(0,0,0,0.3); width: 100%; max-width: 600px; height: 300px;}
    .btn { background: #4CAF50; color: white; padding: 12px 24px; text-decoration: none; border-radius: 5px; font-weight: bold; margin: 10px; display: inline-block; border: none; cursor: pointer;}
    .btn-danger { background: #f44336; }
  </style>
</head>
<body>
  <div class="container">
    <h1>Estación Meteorológica 🌦️</h1>
    
    <div class="grid">
      <div class="card">
        <div>Temperatura</div>
        <div class="val temp-val" id="curTemp">-- °C</div>
      </div>
      <div class="card">
        <div>Hum. Ambiente</div>
        <div class="val hum-val" id="curHum">-- %</div>
      </div>
      <div class="card">
        <div>Hum. Suelo</div>
        <div class="val suelo-val" id="curSuelo">-- %</div>
      </div>
      <div class="card">
        <div>Luz Ambiente</div>
        <div class="val luz-val" id="curLuz">-- %</div>
      </div>
    </div>

    <a href="/datos.csv" class="btn" download="datos_clima.csv">Descargar CSV</a>
    <button onclick="borrarDatos()" class="btn btn-danger">Borrar Datos Históricos</button>
    
    <h2>Tendencia (Temperatura)</h2>
    <canvas id="chart" width="600" height="300"></canvas>
  </div>
  <script>
    async function cargarDatos() {
      try {
        const response = await fetch('/datos.csv');
        const data = await response.text();
        const rows = data.split('\n').slice(1).filter(r => r.trim() !== '');
        
        if (rows.length === 0) return;
        
        // Actualizar valores actuales en las tarjetas
        const lastRow = rows[rows.length - 1].split(',');
        if (lastRow.length >= 5) {
          document.getElementById('curTemp').innerText = lastRow[1] + ' °C';
          document.getElementById('curHum').innerText = lastRow[2] + ' %';
          document.getElementById('curLuz').innerText = lastRow[3] + ' %';
          document.getElementById('curSuelo').innerText = lastRow[4] + ' %';
        }
        
        // Graficar tendencia
        const canvas = document.getElementById('chart');
        const ctx = canvas.getContext('2d');
        const width = canvas.width; const height = canvas.height;
        const pad = 40;
        const temps = rows.map(r => parseFloat(r.split(',')[1]));
        
        const maxT = Math.max(...temps) + 2;
        const minT = Math.min(...temps) - 2;
        
        ctx.clearRect(0,0,width,height);
        
        // Dibujar Ejes
        ctx.strokeStyle = '#555'; ctx.lineWidth = 1;
        ctx.beginPath(); ctx.moveTo(pad, pad); ctx.lineTo(pad, height-pad); ctx.lineTo(width-pad, height-pad); ctx.stroke();
        
        // Dibujar Línea
        ctx.strokeStyle = "#ff4d4d"; ctx.lineWidth = 3; ctx.beginPath();
        temps.forEach((t, i) => {
          const x = pad + (i * (width - 2 * pad) / Math.max(1, temps.length - 1));
          const y = height - pad - ((t - minT) / (maxT - minT)) * (height - 2 * pad);
          if(i === 0) ctx.moveTo(x, y); else ctx.lineTo(x, y);
        });
        ctx.stroke();
        
        // Puntos
        ctx.fillStyle = "#ffffff";
        temps.forEach((t, i) => {
          const x = pad + (i * (width - 2 * pad) / Math.max(1, temps.length - 1));
          const y = height - pad - ((t - minT) / (maxT - minT)) * (height - 2 * pad);
          ctx.beginPath(); ctx.arc(x, y, 4, 0, Math.PI*2); ctx.fill();
        });
      } catch (e) { console.error(e); }
    }
    
    function borrarDatos() {
      if(confirm('¿Seguro que querés borrar todos los datos del historial?')) {
        fetch('/reset').then(() => { alert('Datos borrados'); location.reload(); });
      }
    }
    
    cargarDatos();
    setInterval(cargarDatos, 5000); // Auto-refrescar cada 5 segundos
  </script>
</body>
</html>
)rawliteral";
#endif

// ==========================================
// ⚙️ CONFIGURACIÓN DE PINES Y HARDWARE
// ==========================================
#define LUZ_PIN 39           // TEMT6000 en Kitmaker 2.0
#define SUELO_PIN 34         // Pin de expansión sugerido para sensor de humedad de suelo
#define BUZZER_PIN 12        // Buzzer en Kitmaker 2.0
#define NEOPIXEL_PIN 27      // Neopíxeles en Kitmaker 2.0
#define NUMPIXELS 4

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// ==========================================
// 📊 CONSTANTES Y UMBRALES CONFIGURABLES
// ==========================================
const float TEMP_LIMITE_ALTA = 35.0;
const float TEMP_LIMITE_CRITICA = 40.0;
const int SUELO_LIMITE_BAJO = 40;         // % de humedad de suelo (Advertencia)
const int SUELO_LIMITE_CRITICO = 20;      // % de humedad de suelo (Peligro, muy seco)

// Valores de calibración para la humedad de suelo (12 bits ADC: 0-4095)
const int VALOR_SECO = 4095;
const int VALOR_HUMEDO = 1000;

// Intervalo de registro CSV (300000 ms = 5 minutos)
const unsigned long INTERVALO_CSV = 300000; 

// ==========================================
// 🔌 OBJETOS Y VARIABLES GLOBALES
// ==========================================
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_HTU21DF htu = Adafruit_HTU21DF();
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Variables físicas
float temperatura = 0.0;
float humedadAmbiente = 0.0;
int luzCruda = 0;
int porcentajeLuz = 0;
int sueloCrudo = 0;
int porcentajeSuelo = 0;

// Tiempos de software
unsigned long tiempoUltimoRegistro = 0;
unsigned long segundosTranscurridos = 0;

// Declaración de funciones modulares
void leerSensores();
void controlarAlertas();
void actualizarOLED();
void registrarCsv();
void emitirPito(int duracion, int frecuencia);
void apagarSemaforo();
void encenderSemaforo(uint32_t color);
void iniciarFS();

#ifdef ENABLE_WIFI_SERVER
void iniciarWiFiServer();
#endif

// ==========================================
// ▶️ SETUP (CONFIGURACIÓN INICIAL)
// ==========================================
void setup() {
  Serial.begin(115200);

  Wire.begin();

  if (!htu.begin()) {
    Serial.println("No se encontró el sensor HTU21D!");
  }

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Fallo al iniciar pantalla OLED");
  }

  pixels.begin();
  pixels.setBrightness(50);
  pixels.show();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LUZ_PIN, INPUT);
  pinMode(SUELO_PIN, INPUT);

  encenderSemaforo(pixels.Color(255, 255, 255));
  delay(500);
  apagarSemaforo();

  // El guardado en FS y salida CSV se configuran e inician siempre
  iniciarFS();

#ifdef ENABLE_WIFI_SERVER
  iniciarWiFiServer();
#endif

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 20);
  display.println(F(" Estacion Meteo"));
  display.setCursor(0, 35);
#ifdef ENABLE_WIFI_SERVER
  display.println(F(" Server AP listo"));
#else
  display.println(F(" Datalogger activo"));
#endif
  display.display();
  delay(2000);
}

// ==========================================
// 🔄 LOOP (CICLO CONTINUO)
// ==========================================
void loop() {
  leerSensores();
  controlarAlertas();
  actualizarOLED();
  registrarCsv();
  
#ifdef ENABLE_WIFI_SERVER
  server.handleClient();
#endif

  delay(200);
}

// ==========================================
// 📦 DESARROLLO DE FUNCIONES MODULARES
// ==========================================

void iniciarFS() {
  if (!LittleFS.begin(true)) {
    Serial.println("Error montando LittleFS");
  }
  
  // Abrir y validar/escribir cabecera CSV si es nuevo
  File file = LittleFS.open("/datos.csv", "a");
  if (file && file.size() == 0) {
    file.println("Tiempo(s),Temperatura(C),HumAmbiente(%),Luz(%),HumSuelo(%)");
  }
  if (file) file.close();
  
  Serial.println(F("Sistema de archivos inicializado. Guardado CSV activo."));
}

#ifdef ENABLE_WIFI_SERVER
void iniciarWiFiServer() {
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP Iniciado");
  Serial.print("IP del servidor: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", []() {
    server.send(200, "text/html", index_html);
  });

  server.on("/datos.csv", []() {
    if (LittleFS.exists("/datos.csv")) {
      File file = LittleFS.open("/datos.csv", "r");
      server.streamFile(file, "text/csv");
      file.close();
    } else {
      server.send(404, "text/plain", "Archivo no encontrado");
    }
  });

  server.on("/reset", []() {
    LittleFS.remove("/datos.csv");
    File file = LittleFS.open("/datos.csv", "a");
    if(file) {
      file.println("Tiempo(s),Temperatura(C),HumAmbiente(%),Luz(%),HumSuelo(%)");
      file.close();
    }
    server.send(200, "text/plain", "OK");
  });

  server.begin();
}
#endif

void leerSensores() {
  temperatura = htu.readTemperature();
  humedadAmbiente = htu.readHumidity();

  luzCruda = analogRead(LUZ_PIN);
  porcentajeLuz = map(luzCruda, 0, 4095, 0, 100);
  porcentajeLuz = constrain(porcentajeLuz, 0, 100);

  sueloCrudo = analogRead(SUELO_PIN);
  porcentajeSuelo = map(sueloCrudo, VALOR_SECO, VALOR_HUMEDO, 0, 100);
  porcentajeSuelo = constrain(porcentajeSuelo, 0, 100);
}

void controlarAlertas() {
  if (temperatura >= TEMP_LIMITE_CRITICA || porcentajeSuelo <= SUELO_LIMITE_CRITICO) {
    encenderSemaforo(pixels.Color(255, 0, 0));
    emitirPito(100, 2500);
  } else if (temperatura >= TEMP_LIMITE_ALTA || porcentajeSuelo <= SUELO_LIMITE_BAJO) {
    encenderSemaforo(pixels.Color(255, 150, 0));
    emitirPito(300, 1000);
  } else {
    encenderSemaforo(pixels.Color(0, 255, 0));
  }
}

void actualizarOLED() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print(F("--- DATOS ACTUALES ---"));

  display.setCursor(0, 15);
  display.print(F("Temp: "));
  if (isnan(temperatura) || temperatura > 120.0) display.print(F("Error"));
  else { display.print(temperatura, 1); display.print(F(" C")); }

  display.setCursor(0, 27);
  display.print(F("Hum Amb: "));
  if (isnan(humedadAmbiente) || humedadAmbiente > 100.0) display.print(F("Error"));
  else { display.print(humedadAmbiente, 1); display.print(F(" %")); }

  display.setCursor(0, 39);
  display.print(F("Hum Suelo: "));
  display.print(porcentajeSuelo); display.print(F(" %"));

  display.setCursor(0, 51);
#ifdef ENABLE_WIFI_SERVER
  display.print(F("IP: "));
  display.print(WiFi.softAPIP().toString());
#else
  display.print(F("Luz: "));
  display.print(porcentajeLuz); display.print(F(" %"));
#endif

  display.display();
}

void registrarCsv() {
  if (millis() - tiempoUltimoRegistro >= INTERVALO_CSV || tiempoUltimoRegistro == 0) {
    if (tiempoUltimoRegistro == 0) {
        tiempoUltimoRegistro = millis();
    }
    
    segundosTranscurridos = millis() / 1000;
    
    String lineaCsv = String(segundosTranscurridos) + "," + 
                      String(temperatura, 1) + "," + 
                      String(humedadAmbiente, 1) + "," + 
                      String(porcentajeLuz) + "," + 
                      String(porcentajeSuelo);

    // Guardado persistente en LittleFS (Siempre activo)
    File file = LittleFS.open("/datos.csv", "a");
    if (file) {
      file.println(lineaCsv);
      file.close();
      Serial.println("Dato Guardado FS: " + lineaCsv);
    } else {
      Serial.println("Error al abrir CSV en FS");
    }

    tiempoUltimoRegistro = millis();
  }
}

void emitirPito(int duracion, int frecuencia) {
  static unsigned long ultimoSonido = 0;
  if (millis() - ultimoSonido >= (duracion + 500)) {
    tone(BUZZER_PIN, frecuencia, duracion);
    ultimoSonido = millis();
  }
}

void apagarSemaforo() {
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}

void encenderSemaforo(uint32_t color) {
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, color);
  }
  pixels.show();
}
