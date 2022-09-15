#include <WiFi.h>
const char* ssid     = "SK_ 2.4G";
const char* password = "42117622";
WiFiServer server(80);
int LED1 = 23;
int LED2 = 22;
int LED3 = 21;
int LED4 = 19;

IPAddress staticIP(192,168,0,20);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);
 
void setup(){
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);      // set the LED pin mode
  pinMode(LED2, OUTPUT);      // set the LED pin mode
  pinMode(LED3, OUTPUT);      // set the LED pin mode
  pinMode(LED4, OUTPUT);      // set the LED pin mode
  delay(10);

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  WiFi.config(staticIP, gateway, subnet);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("WiFi connected IP address: ");
  Serial.print(WiFi.localIP());
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
            client.print("Click <a href=\"/LED1-H\">here</a> to turn on LED1 <br>");
            client.print("Click <a href=\"/LED1-L\">here</a> to turn off LED1 <br>");
            client.print("<br>");
 
            client.print("Click <a href=\"/LED2-H\">here</a> to turn on LED2 <br>");
            client.print("Click <a href=\"/LED2-L\">here</a> to turn off LED2 <br>");
            client.print("<br>");
 
            client.print("Click <a href=\"/LED3-H\">here</a> to turn on LED3 <br>");
            client.print("Click <a href=\"/LED3-L\">here</a> to turn off LED4 <br>");
            client.print("<br>");
 
            client.print("Click <a href=\"/LED4-H\">here</a> to turn on LED4<br>");
            client.print("Click <a href=\"/LED4-L\">here</a> to turn off LED4 <br>");
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
        if (currentLine.endsWith("GET /LED1-H")) {
          digitalWrite(LED1, HIGH);               // GET /H turns the LED1 on
        }
        if (currentLine.endsWith("GET /LED1-L")) {
          digitalWrite(LED1, LOW);                // GET /L turns the LED1 off
        }
        if (currentLine.endsWith("GET /LED2-H")) {
          digitalWrite(LED2, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /LED2-L")) {
          digitalWrite(LED2, LOW);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /LED3-H")) {
          digitalWrite(LED3, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /LED3-L")) {
          digitalWrite(LED3, LOW);                // GET /L turns the LED off
        }
        if (currentLine.endsWith("GET /LED4-H")) {
          digitalWrite(LED4, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /LED4-L")) {
          digitalWrite(LED4, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
