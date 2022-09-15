#include <WiFi.h>                    // if ESP32
//#include <ESP8266WiFi.h>           // if ESP8266
const char* ssid = "SDTCBuilding1_2_2.4G";        // You need to put your own WiFi name
const char* password = "es75xtcR";     //  You need to put your own WiFi password

void setup(){
  Serial.begin(115200);
  Serial.println();
  WiFi.begin(ssid, password);
  Serial.print("connecting ");
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi is connected ");
  Serial.print(WiFi.localIP());
 }
 
 void loop(){
  delay(1000);
 }
