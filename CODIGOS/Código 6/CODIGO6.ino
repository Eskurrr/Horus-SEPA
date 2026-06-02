#include <WiFi.h>
 // Definimos constantes de credenciales wifi
const char* ssid     = "ESP32SEPA";
const char* password = "zeri3333";
// Definimos puerto del servidor
WiFiServer server(5000);
// Definimos cada pin de cada sensor
#define SENSOR1 34
#define SENSOR2 35
#define SENSOR3 32
#define SENSOR4 33
// Definimos el periodo de pruebas
#define SAMPLE_PERIOD_US 4000UL

void setup() {
    Serial.begin(115200); // hacemos el setup a 115200 baudios
    analogSetAttenuation(ADC_11db);   // rango ADC 0–3.3V completo
    WiFi.softAP(ssid, password);  // Setup de la esp32 en modo access point
    Serial.print("IP ESP32: ");
    Serial.println(WiFi.softAPIP());
    server.begin(); // inicia el servidor tcp
    Serial.println("Servidor TCP iniciado");
}

void loop() {
    WiFiClient client = server.available(); // Comprobamos si hay algun cliente conectandose

    if (client) {
        client.setNoDelay(true); // Funcion para sacar el delay del envio de datos
        Serial.println("PC conectado");
        client.println("ESP32_OK");

        unsigned long lastSample = micros(); // Marca de tiempo del ultimo muestreo

        String cmdBuffer = "";           // fuera del while, sin static

        while (client.connected()) {

            while (client.available()) {
                char c = client.read();
                if (c == '\n') {
                    cmdBuffer.trim(); // elimina espacios y saltos de linea
                    if (cmdBuffer.length() > 0) {
                        Serial.println("Recibido: " + cmdBuffer);
                    }
                    cmdBuffer = ""; // limpia el buffer para el siguiente comando 
                } else {
                    cmdBuffer += c; // acumula el caracter en el buffer
                }
            }

            unsigned long now = micros(); // control de tiempo para muestrear a intervalos fijos 
            if (now - lastSample >= SAMPLE_PERIOD_US) {
                lastSample += SAMPLE_PERIOD_US; // avanza marca de tiempo

                int s1 = analogRead(SENSOR1); // leemos todos los sensores
                int s2 = analogRead(SENSOR2);
                int s3 = analogRead(SENSOR3);
                int s4 = analogRead(SENSOR4);

                client.printf("%d,%d,%d,%d\n", s1, s2, s3, s4); // envia todos los datos al client
            }
        }

        client.stop(); 
        Serial.println("PC desconectado");
    }
}