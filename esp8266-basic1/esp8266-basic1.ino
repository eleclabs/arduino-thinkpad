#include <ESP8266WiFi.h>

const char *ssid = "NodeMCU";
const char *password = "12345678"; //the password should be 8 char or more

//setting the addresses
IPAddress ip(192,168,8,1);
IPAddress gateway(192, 168, 8, 1);
IPAddress subnet(255, 255, 255, 0);

void setup() {
  WiFi.mode(WIFI_AP); //switching to AP mode
  WiFi.softAP(ssid, password); //initializing the AP with ssid and password. This will create a WPA2-PSK secured AP

  WiFi.config(ip,gateway,subnet);
  WiFi.begin();
}

void loop() {
  
}
