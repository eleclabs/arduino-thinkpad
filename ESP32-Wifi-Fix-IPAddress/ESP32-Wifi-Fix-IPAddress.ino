#include <WiFi.h>          // if ESP32
//#include <ESP8266WiFi.h>     // if ESP8266
const char* ssid = "A12";       // You need to put your own WiFi name
const char* password = "42117622";  //  You need to put your own WiFi password

IPAddress staticIP(192,168,0,20);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

void setup(){
  Serial.begin(115200);
  Serial.println();
  
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  
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
 
 
