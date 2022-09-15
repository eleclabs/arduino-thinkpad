#include "Wire.h"
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
/*
  #include <ESP8266WiFi.h>
  const char* ssid = "SmartFarm V0.1";
  const char* password = "12345678";
  WiFiServer server(80);

  String header;
  String outputState1 = "off";
  String outputState2 = "off";
*/
//int val;
//int adc = A0;
#define S1  D3
#define RY1 D5
#define RY2 D6
//#define RY3 D7  //outputState1
//#define RY4 D8  //outputState2

#define DHTPIN D0
#define DHTTYPE DHT11 // DHT 11
//#define DHTTYPE DHT22 // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21 // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);
//LiquidCrystal_I2C lcd(0x3F, 16, 2); // ถ้าจอไม่ขึ้นให้ลองใช้ตำแหน่ง 0x3F นี้


void setup() {
  Serial.begin(115200);
  dht.begin();
  lcd.begin();
  //lcd.backlight();   //เปิดไฟ backlight
  delay(100);

  pinMode(S1, INPUT_PULLUP);
  pinMode(RY1, OUTPUT);
  pinMode(RY2, OUTPUT);
  //pinMode(RY3, OUTPUT);
  //pinMode(RY4, OUTPUT);
  //off all
  digitalWrite(RY1, HIGH);
  digitalWrite(RY2, HIGH);
  //digitalWrite(RY3, HIGH);
  //digitalWrite(RY4, HIGH);
  /*
    // Set Wi-Fi network with SSID and password
    WiFi.mode(WIFI_AP); // ใช้งาน WiFi ในโหมด AP
    WiFi.softAP(ssid);  //or WiFi.softAP(ssid, password)
    Serial.print("Connect to ");
    Serial.println(ssid);
    IPAddress apip = WiFi.softAPIP();
    Serial.print("IP Address: ");
    Serial.println(apip);
    server.begin();
  */
}
void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  lcd.setCursor(0, 0);
  lcd.print("Hum:     ");
  lcd.setCursor(4, 0);
  lcd.print(h);
  lcd.setCursor(9, 0);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("Tem:     ");
  lcd.setCursor(4, 1);
  lcd.print(t);
  lcd.setCursor(9, 1);
  lcd.print("C");

  Serial.print("อุณหภูมิ  ");
  Serial.print(t); // แสดงค่าอุณหภูมิ
  Serial.println(" *C");
  Serial.print("ความชื้นสัมพัทธ์  ");
  Serial.print(h); // แสดงค่าความชื้น
  Serial.println(" %");
  Serial.println("\n.........");

  if (t >= 29 ) {
    digitalWrite(RY1, LOW);
    Serial.print("RY1 ON  \n");
  } else {
    digitalWrite(RY1, HIGH);
    Serial.print("RY1 OFF  \n");
  }
  /*
  if (h >= 50 ) {
    digitalWrite(RY4, LOW);
    Serial.print("RY4 ON  \n");
  } else {
    digitalWrite(RY4, HIGH);
    Serial.print("RY4 OFF  \n");
  }
*/
  int s1 = digitalRead(S1);
  if (s1 == HIGH) {
    digitalWrite(RY2, LOW);
    Serial.print("RY2 ON  \n");
  } else {
    digitalWrite(RY2, HIGH);
    Serial.print("RY2 OFF  \n");
  }
/*
  val = analogRead(adc);         // อ่านค่า Analog ขาA0 เก็บไว้ในตัวแปร Val
  val = map(val, 0, 1023, 0, 180);  // แปลงค่า ระหว่าง 0-1023 เป็น 0-180
  Serial.print("val = ");           // พิมพ์ข้อมความส่งเข้าคอมพิวเตอร์ "val = "
  Serial.println(val);              // พิมพ์ค่าของตัวแปร val
  
  if (val >= 100) {
    digitalWrite(RY3, LOW);
    Serial.print("RY3 ON  \n");
  } else {
    digitalWrite(RY3, HIGH);
    Serial.print("RY3 OFF  \n");
  }
*/
  //----Wifi----
  /*
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
            if (header.indexOf("GET /RY3/on") >= 0) {
              Serial.println("GPIO RY3 on");
              outputState1 = "on";
              digitalWrite(RY3, LOW); //active 0
            } else if (header.indexOf("GET /RY3/off") >= 0) {
              Serial.println("GPIO RY3 off");
              outputState1 = "off";
              digitalWrite(RY3, HIGH);
            } else if (header.indexOf("GET /RY4/on") >= 0) {
              Serial.println("GPIO RY4 on");
              outputState2 = "on";
              digitalWrite(RY4, LOW); //active 0
            } else if (header.indexOf("GET /RY4/off") >= 0) {
              Serial.println("GPIO RY4 off");
              outputState2 = "off";
              digitalWrite(RY4, HIGH);
            }

            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            client.println("<body><h1>Smart Farm V0.1</h1>");
            client.println("<p>GPIO RY3 - State " + outputState1 + "</p>");
            client.println("<p>GPIO RY4 - State " + outputState2 + "</p>");
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
  */
  delay(1000);
}
