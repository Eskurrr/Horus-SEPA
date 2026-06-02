// Definimos sensores
#define SENSOR1 34
#define SENSOR2 35
#define SENSOR3 32
#define SENSOR4 33
// variable para guardar el tiempo del ultimo envio de datos
unsigned long lastSend = 0;

void setup() {
  Serial.begin(500000); // hacemos el setup a 500000 baudios 
}

void loop() {
  if (millis() - lastSend >= 4) {  // 250 Hz
    lastSend = millis(); // actualizamos nuestra variable
    int s1 = analogRead(SENSOR1); // leemos los 4 sensores
    int s2 = analogRead(SENSOR2);
    int s3 = analogRead(SENSOR3);
    int s4 = analogRead(SENSOR4);
    // imprimimos los datos en la consola
    Serial.print(s1);   Serial.print(",");
    Serial.print(s2);   Serial.print(",");
    Serial.print(s3);   Serial.print(",");
    Serial.println(s4);
  }
}