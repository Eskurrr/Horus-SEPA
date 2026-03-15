// WIFI AP https://www.prometec.net/wifi-modo-acces-point/
#include <WiFi.h> // METEMOS LA LIBRERIA DE COMANDOS WIFI


const char* ssid = "ESP32SEPA"; // NOMBRE DE LA RED A CREAR
const char* password = "zeri3333";   // PASSWORD DE LA RED (MINIMO 8CHAR)

WiFiServer server(5000); // CREAMOS SERVIDOR TCP CON PUERTO 5000 PARA QUE SE CONECTE MATLAB


#define SENSOR1 34 // PONEMOS VALOR DEL PIN EN EL QUE ESTA CONECTADO EL OUTPUT ANALOG. DE NUESTRO PRIMER SENSOR
#define SENSOR2 35 // PONEMOS VALOR DEL PIN EN EL QUE ESTA CONECTADO EL OUTPUT ANALOG. DE NUESTRO SEGUNDO SENSOR
#define SENSOR3 32
#define SENSOR4 33
void setup() {

  Serial.begin(115200);  // INICIAMOS LA COMUNICACION CON ARDUINO A 115200 BAUDIOS
  WiFi.softAP(ssid, password); // ACTIVA EL ACCESS POINT DEL MODULO WIFI DE LA ESP32 CON LA SSID Y PASSWORD ANTERIOR
  Serial.println("WiFi creada"); // IMPRIMIMOS CONSOLA
  Serial.print("IP ESP32: "); // IMPRIMIMOS CONSOLA
  Serial.println(WiFi.softAPIP());   // IMRPIMIMOS LA IP DE LA ESP32

  server.begin(); // INICIAMOS EL SERVIDOR PARA QUE EMPIECE A ESCUCHAR SIGNALS EN EL PUERTO 5000
  Serial.println("Servidor TCP iniciado"); // IMPRIMIMOS LO MENCIONADO ANTERIOR
}

void loop() {

  WiFiClient client = server.available(); // REVISA SI HAY UN DISPOSITIVO CONECTADO (CLIENT)

  if (client) { // SI CLIENT ESTA VACIO, SIGUE BUSCANDO, SI NO, IMPRIMIMOS QUE SE CONECTO EL USUARIO Y LA ESP32 IMPRIME HACIA EL DISP. QUE TODO OK

    Serial.println("PC conectado");
    client.println("ESP32_OK");

    while (client.connected()) { // INCIAMOS BUCLE, MIENTRAS EL DISP. ESTE CONECTADO, LEEMOS LA SIGNAL Y LA IMPRIMIMOS HACIA MATLAB

      int s1 = analogRead(SENSOR1);
      int s2 = analogRead(SENSOR2);
      int s3 = analogRead(SENSOR3);
      int s4 = analogRead(SENSOR4);
      client.print(s1);
      client.print(",");
      client.print(s2);
      client.print(",");
      client.print(s3);
      client.print(",");
      client.println(s4);
    
      delay(100);  // DELAY PARA NO LLENARNOS DE DATOS
    }

    client.stop(); // SI SE DESCONECTA EL DISPOSITIVO (CLIENT) ESTA VACIO Y SE DETIENE EL BUCLE, IMPRIMIENDO LA DESCONEXION
    Serial.println("PC desconectado");
  }
}