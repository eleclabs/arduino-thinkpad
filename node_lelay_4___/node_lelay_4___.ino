#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

//Config ขา Output
#define Relay1 D1 //คือต่อรีเลย์ขา D1 กำหนดเป็นชื่อ Relay1
#define Relay2 D2 //คือต่อรีเลย์ขา D2 กำหนดเป็นชื่อ Relay2
#define Relay3 D3 //คือต่อรีเลย์ขา D3 กำหนดเป็นชื่อ Relay3
#define Relay4 D4 //คือต่อรีเลย์ขา D4 กำหนดเป็นชื่อ Relay4
#define Relay9 D9 //คือต่อรีเลย์ขา D8 กำหนดเป็นชื่อ Relay9

char auth[] = "VxypTHclZKUQatUqZEdfLdH9ck7nVhTQ";
char ssid[] = "test";
char pass[] = "0123456789";

WidgetLED Relay1Blynk(V10);
WidgetLED Relay2Blynk(V11);
WidgetLED Relay3Blynk(V12);
WidgetLED Relay4Blynk(V13);
WidgetLED Relay9Blynk(V18);
  
void setup()
{
  // Debug console
  Serial.begin(9600);
  
  //กำหนดขา OUTPUT
  pinMode(Relay1,OUTPUT); 
  pinMode(Relay2,OUTPUT); 
  pinMode(Relay3,OUTPUT); 
  pinMode(Relay4,OUTPUT);
  pinMode(Relay9,OUTPUT);    
    Blynk.begin(auth,ssid,pass);
    
}

void loop()
{
  Blynk.run();
}
BLYNK_WRITE(V1){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(Relay1, HIGH); 
        Relay1Blynk.on();
    } else {
        digitalWrite(Relay1, LOW); 
         Relay1Blynk.off();
    }
}
BLYNK_WRITE(V2){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(Relay2, HIGH); 
         Relay2Blynk.on();
    } else {
        digitalWrite(Relay2, LOW); 
         Relay2Blynk.off();
    }
}
BLYNK_WRITE(V3){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(Relay3, HIGH); 
        Relay3Blynk.on();
    } else {
        digitalWrite(Relay3, LOW); 
         Relay3Blynk.off();
    }
}
BLYNK_WRITE(V4){ 
  Serial.println(param.asInt());
    if (param.asInt()){ 
        digitalWrite(Relay4, HIGH); 
        Relay4Blynk.on();
    } else {
        digitalWrite(Relay4, LOW); 
         Relay4Blynk.off();
    }
}
BLYNK_WRITE(V9){ 
  Serial.println(param.asInt()); 
    if (param.asInt()){ 
        digitalWrite(Relay9, HIGH);
        digitalWrite(Relay1, HIGH);
        digitalWrite(Relay2, HIGH);
        digitalWrite(Relay3, HIGH);
        digitalWrite(Relay4, HIGH); 
         Relay9Blynk.on();
    } else {
        digitalWrite(Relay9, LOW);
        digitalWrite(Relay1, LOW);
        digitalWrite(Relay2, LOW);
        digitalWrite(Relay3, LOW);
        digitalWrite(Relay4, LOW); 
         Relay9Blynk.off();
    }
}
