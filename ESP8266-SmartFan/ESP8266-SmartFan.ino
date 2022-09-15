#include <ESP8266WiFi.h>

const char* ssid = "SmartFAN V0.1";
const char* password = "12345678";
WiFiServer server(80);

String header;
String outputState1 = "off";
String outputState2 = "off";
String outputState3 = "off";
String outputState4 = "off";

#define RY1 D1  //outputState1
#define RY2 D2  //outputState1
#define RY3 D3  //outputState3
#define RY4 D4  //outputState4


void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(RY1, OUTPUT);
  pinMode(RY2, OUTPUT);
  pinMode(RY3, OUTPUT);
  pinMode(RY4, OUTPUT);
  //off all
  digitalWrite(RY1, HIGH);
  digitalWrite(RY2, HIGH);
  digitalWrite(RY3, HIGH);
  digitalWrite(RY4, HIGH);

  // Set Wi-Fi network with SSID and password
  WiFi.mode(WIFI_AP); // ใช้งาน WiFi ในโหมด AP
  WiFi.softAP(ssid);  //or WiFi.softAP(ssid, password)
  Serial.print("Connect to ");
  Serial.println(ssid);
  IPAddress apip = WiFi.softAPIP();
  Serial.print("IP Address: ");
  Serial.println(apip);

  server.begin();
}
void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {

        char c = client.read();
        Serial.write(c);
        header += c;
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            if (header.indexOf("GET /RY1/on") >= 0) {
              Serial.println("GPIO RY1 on");
              outputState1 = "on";
              outputState2 = "off";
              outputState3 = "off";
              outputState4 = "off";
              digitalWrite(RY1, LOW); //ON active 0
              digitalWrite(RY2, HIGH); //OFF
              digitalWrite(RY3, HIGH); //OFF
              digitalWrite(RY4, HIGH); //OFF
            } else if (header.indexOf("GET /RY1/off") >= 0) {
              Serial.println("GPIO RY1 off");
              outputState1 = "off";
              digitalWrite(RY1, HIGH);
            } else if (header.indexOf("GET /RY2/on") >= 0) {
              Serial.println("GPIO RY2 on");
              outputState1 = "off";
              outputState2 = "on";
              outputState3 = "off";
              outputState4 = "off";
              digitalWrite(RY1, HIGH); //OFF
              digitalWrite(RY2, LOW); //ON active 0
              digitalWrite(RY3, HIGH); //OFF
              digitalWrite(RY4, HIGH); //OFF
            } else if (header.indexOf("GET /RY2/off") >= 0) {
              Serial.println("GPIO RY2 off");
              outputState2 = "off";
              digitalWrite(RY2, HIGH);
            }else if (header.indexOf("GET /RY3/on") >= 0) {
              Serial.println("GPIO RY3 on");
              outputState1 = "off";
              outputState2 = "off";
              outputState3 = "on";
              outputState4 = "off";
              digitalWrite(RY1, HIGH); //OFF
              digitalWrite(RY2, HIGH); //OFF
              digitalWrite(RY3, LOW); //ON active 0
              digitalWrite(RY4, HIGH); //OFF
            } else if (header.indexOf("GET /RY3/off") >= 0) {
              Serial.println("GPIO RY3 off");
              outputState3 = "off";
              digitalWrite(RY3, HIGH);
            }else if (header.indexOf("GET /RY4/on") >= 0) {
              Serial.println("GPIO RY4 on");
              outputState1 = "off";
              outputState2 = "off";
              outputState3 = "off";
              outputState4 = "off";
              digitalWrite(RY1, HIGH); //OFF
              digitalWrite(RY2, HIGH); //OFF
              digitalWrite(RY3, HIGH); //OFF
              digitalWrite(RY4, HIGH); //OFF
            } else if (header.indexOf("GET /RY4/off") >= 0) {
              Serial.println("GPIO RY4 off");
              outputState4 = "off";
              digitalWrite(RY4, HIGH);
            }
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            client.println("<body><h1>Smart FAN V0.1</h1>");
            client.println("<p>GPIO RY1 - State " + outputState1 + "</p>");
            client.println("<p>GPIO RY2 - State " + outputState2 + "</p>");
            client.println("<p>GPIO RY3 - State " + outputState3 + "</p>");
            client.println("<p>GPIO RY4 - State " + outputState4 + "</p>");
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

   delay(1000);
}
