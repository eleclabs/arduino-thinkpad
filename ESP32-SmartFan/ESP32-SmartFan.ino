#include <WiFi.h>
const char* ssid = "SK_ 2.4G";
const char* password = "42117622";

WiFiServer server(80);

IPAddress staticIP(192,168,0,100);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

String header;
String outputState1 = "off";
String outputState2 = "off";
String outputState3 = "off";
String outputState4 = "off";

#define RY1 23  //outputState1
#define RY2 22  //outputState1
#define RY3 21  //outputState3
#define RY4 19  //outputState4

void setup() {
  Serial.begin(115200);
  pinMode(RY1, OUTPUT);
  pinMode(RY2, OUTPUT);
  pinMode(RY3, OUTPUT);
  pinMode(RY4, OUTPUT);
  //off all
  digitalWrite(RY1, LOW); 
  digitalWrite(RY2, LOW);
  digitalWrite(RY3, LOW);
  digitalWrite(RY4, LOW);
  delay(10);
  // Set Wi-Fi network with SSID and password
  Serial.print("Connect to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("WiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
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
            if (header.indexOf("GET /speed1/on") >= 0) {
              Serial.println("GPIO Speed1 on");
              outputState1 = "on";
              outputState2 = "off";
              outputState3 = "off";
              outputState4 = "off";
              digitalWrite(RY1, HIGH); //ON active 1
              digitalWrite(RY2, LOW); //OFF
              digitalWrite(RY3, LOW); //OFF
              digitalWrite(RY4, LOW); //OFF
            }else if (header.indexOf("GET /speed2/on") >= 0) {
              Serial.println("GPIO Speed2 on");
              outputState1 = "off";
              outputState2 = "on";
              outputState3 = "off";
              outputState4 = "off";
              digitalWrite(RY1, LOW); //OFF
              digitalWrite(RY2, HIGH); //ON active 1
              digitalWrite(RY3, LOW); //OFF
              digitalWrite(RY4, LOW); //OFF
            }else if (header.indexOf("GET /speed3/on") >= 0) {
              Serial.println("GPIO Speed3 on");
              outputState1 = "off";
              outputState2 = "off";
              outputState3 = "on";
              outputState4 = "off";
              digitalWrite(RY1, LOW); //OFF
              digitalWrite(RY2, LOW); //OFF
              digitalWrite(RY3, HIGH); //ON active 0
              digitalWrite(RY4, LOW); //OFF
            }else if (header.indexOf("GET /speed4/off") >= 0) {
              Serial.println("GPIO OFF ALL");
              outputState1 = "off";
              outputState2 = "off";
              outputState3 = "off";
              outputState4 = "off";
              digitalWrite(RY1, LOW); //OFF
              digitalWrite(RY2, LOW); //OFF
              digitalWrite(RY3, LOW); //OFF
              digitalWrite(RY4, LOW); //OFF
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
