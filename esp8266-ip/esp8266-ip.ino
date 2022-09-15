#include<Arduino.h>
#include<ESP8266WiFi.h>
const char* ssid="Nokia 8.1";     // You need to put your own WiFi name
const char* password="12345678"; //  You need to put your own WiFi password
void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("connecting");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print("Waiting to connect WiFi\n");
  }
  
  Serial.print("WiFi is connected \n");
  Serial.print(WiFi.localIP());
 }
 
 void loop(){
  delay(1000);
 }
 
 
