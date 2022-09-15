#include <WiFi.h>
 
const char* ssid     = "SK_ 2.4G";
const char* password = "42117622";
 
WiFiServer server(80);

IPAddress staticIP(192,168,0,100);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
 
void setup()
{
  Serial.begin(115200);
 
  pinMode(23, OUTPUT);      // set the LED pin mode
  pinMode(22, OUTPUT);      // set the LED pin mode
  pinMode(21, OUTPUT);      // set the LED pin mode
  pinMode(19, OUTPUT);      // set the LED pin mode
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
 
int value = 0;
 
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
 
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
 
            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/23H\">here</a> to turn the LED on pin 23 on.<br>");
            client.print("Click <a href=\"/23L\">here</a> to turn the LED on pin 23 off.<br>");
            client.print("<br>");
 
            client.print("Click <a href=\"/22H\">here</a> to turn the LED on pin 22 on.<br>");
            client.print("Click <a href=\"/22L\">here</a> to turn the LED on pin 22 off.<br>");
            client.print("<br>");
 
            client.print("Click <a href=\"/21H\">here</a> to turn the LED on pin 21 on.<br>");
            client.print("Click <a href=\"/21L\">here</a> to turn the LED on pin 21 off.<br>");
            client.print("<br>");
 
            client.print("Click <a href=\"/19H\">here</a> to turn the LED on pin 19 on.<br>");
            client.print("Click <a href=\"/19L\">here</a> to turn the LED on pin 19 off.<br>");
            client.print("<br>");
 
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
 
        // Check to see if the client request was "GET /xH" or "GET /xL":
        if (currentLine.endsWith("GET /23H")) {
          digitalWrite(23, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /23L")) {
          digitalWrite(23, LOW);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /22H")) {
          digitalWrite(22, HIGH);               // GET /H turns the LED on
        }
 
        if (currentLine.endsWith("GET /22L")) {
          digitalWrite(22, LOW);                // GET /L turns the LED off
        }
 
        if (currentLine.endsWith("GET /21H")) {
          digitalWrite(21, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /21L")) {
          digitalWrite(21, LOW);                // GET /L turns the LED off
        }
 
        if (currentLine.endsWith("GET /19H")) {
          digitalWrite(19, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /19L")) {
          digitalWrite(19, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
