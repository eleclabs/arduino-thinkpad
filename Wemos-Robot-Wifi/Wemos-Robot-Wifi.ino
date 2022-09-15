#include <WiFi.h>
const char* ssid = "SmartRobot (DD1)";
const char* password = "12345678";

WiFiServer server(80);

String header;
String mr1State = "off";
String mr2State = "off";
String ml1State = "off";
String ml2State = "off";

const int mr1 = 12;
const int mr2 = 13;
const int ml1 = 25;
const int ml2 = 26;

void back(void);
void front(void);
void right(void);
void left(void);
void stoped(void);

void setup() {
  Serial.begin(115200);
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  stoped();

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
            if (header.indexOf("GET /front/on") >= 0) {
              front();
            } else if (header.indexOf("GET /front/off") >= 0) {
              stoped();
            } else if (header.indexOf("GET /back/on") >= 0) {
              back();
            } else if (header.indexOf("GET /back/off") >= 0) {
              stoped();
            } else if (header.indexOf("GET /left/on") >= 0) {
              left();
            } else if (header.indexOf("GET /left/off") >= 0) {
              stoped();
            } else if (header.indexOf("GET /right/on") >= 0) {
              right();
            } else if (header.indexOf("GET /right/off") >= 0) {
              stoped();
            } else {
              stoped();
            }
            /*
                        client.println("<!DOCTYPE html><html>");
                        client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
                        client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
                        client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
                        client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
                        client.println(".button2 {background-color: #555555;}</style></head>");

                        client.println("<body><h1>ESP32 Smart Robot</h1>");
                        // client.println("<p>GPIO 26 - State " + output26State + "</p>");
                        // client.println("<p>GPIO 27 - State " + output27State + "</p>");
                        client.println();
            */
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

//---ฟังก์ชั่นต่างๆ
void back(void) {
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
}
void front(void) {
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
}
void right(void) {
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, HIGH);
  digitalWrite(ml1, HIGH);
  digitalWrite(ml2, LOW);
}
void left(void) {
  digitalWrite(mr1, HIGH);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, HIGH);
}
void stoped(void) {
  digitalWrite(mr1, LOW);
  digitalWrite(mr2, LOW);
  digitalWrite(ml1, LOW);
  digitalWrite(ml2, LOW);
}
