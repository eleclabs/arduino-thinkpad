#include <WiFi.h>

const char* ssid = "ESP32-Wifi";
const char* password = "12345678";

WiFiServer server(80);

String header;
String outputState1 = "off";
String outputState2 = "off";

const int output1 = 22;
const int output2 = 23;

void setup() {
  Serial.begin(115200);
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  digitalWrite(output1, LOW);
  digitalWrite(output2, LOW);

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
            if (header.indexOf("GET /output1/on") >= 0) {
              Serial.println("GPIO output1 on");
              outputState1 = "on";
              digitalWrite(output1, HIGH);
            } else if (header.indexOf("GET /output1/off") >= 0) {
              Serial.println("GPIO output1 off");
              outputState1 = "off";
              digitalWrite(output1, LOW);
            } else if (header.indexOf("GET /output2/on") >= 0) {
              Serial.println("GPIO output2 on");
              outputState2 = "on";
              digitalWrite(output2, HIGH);
            } else if (header.indexOf("GET /output2/off") >= 0) {
              Serial.println("GPIO output2 off");
              outputState2 = "off";
              digitalWrite(output2, LOW);
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button {background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; }");
            client.println(".button2 {background-color: #555555; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer; }");
            client.println("</style></head>");
            client.println("<body><h1>ESP32 Web Server</h1>");

            client.println("<p>GPIO output1 - State " + outputState1 + "</p>");
            if (outputState1 == "off") {
              client.println("<a class=\"button\" href=\"../output1/on \"> LED1 ON </a>");
            } else {
              client.println("<a class=\"button2\" href=\"../output1/off \"> LED1 OFF </a>");
            }

            client.println("<p>GPIO output2 - State " + outputState2 + "</p>");
            if (outputState2 == "off") {
              client.println("<a class=\"button\" href=\"../output2/on \"> LED2 ON </a>");
            } else {
              client.println("<a class=\"button2\" href=\"../output2/off \"> LED2 OFF </a>");
            }

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
}
