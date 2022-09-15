#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
//----------------------------------------
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
//----------------------------------------

//########## CONFIGURATION : MODIFY HERE ##########
char ssid[] = "OPPO A5 2020";      // เครือข่าย Wi-Fi ที่ต้องการเชื่อมต่อ
char pass[] = "oppoa52020"; // รหัสผ่านเครือข่าย

//รหัสเชื่อมต่อ Line token
#define TokenLine "bJWRQzviA1mlL9Q1M4kwgzFBVudwTT8XjPyfUCmH7xj"

// ข้อความ ที่จะแสดงใน Line
String txt1 = "เครื่องวัดอุณหภูมิแจ้งเตือนไลน์ ";

byte sensorPin = 23;    //กำหนดขาที่เชื่อมต่อกับเซ็นเซอร์
const int LED = 2;      //LED แสดงสถาน่ะการทำงาน

void setup() {
  //ตั้งค่าคอนโซล
  Serial.begin(115200);
  Serial.println("Adafruit MLX90614 test");
  mlx.begin();
  //-----------------------
  pinMode(sensorPin, INPUT);  //กำหนดให้ขาดิจิตอล sensorPin รับข้อมูลจากเซ็นเซอร์
  pinMode(LED, OUTPUT);

  //เริ่มการเชื่อมต่อกับวายฟายแม่ข่าย
  WiFi.begin(ssid, pass);

  //แสดง "WiFi Connecting" ในคอนโซล
  Serial.print("WiFi Connecting");

  //ตรวจเช็คสถานะการเขื่อมต่อวายฟาย
  //ถ้าไม่สำเร็จให้แสดง "." ในคอนโซลจนกว่าจะเขื่อมต่อได้
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  //แสดงสถานะการวายฟายเชื่อมต่อแล้ว
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //------------MLX90614------------
  Serial.print("Ambient = ");
  Serial.print(mlx.readAmbientTempC());
  Serial.print("*C\tObject = ");
  Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = ");
  Serial.print(mlx.readAmbientTempF());
  Serial.print("*F\tObject = ");
  Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  Serial.println();
  String txt2 = "\nอุณหภูมิแวดล้อม = ";
  txt2 += mlx.readAmbientTempC();
  txt2 += "*C";
  txt2 += "\nอุณหภูมิร่างกาย = ";
  txt2 += mlx.readObjectTempC()-10;  //ลบ เพื่อให้ได้อุณหภูมิที่ใกล้เคียงของจริง
  txt2 += "*C\n";
  //--------------------------------
  byte state = digitalRead(sensorPin);

  if (state == 0) {
    Serial.println("Somebody is in this area!");
    NotifyLine(txt2); //ส่งค่าไปที่ Line Notify
    digitalWrite(LED, HIGH);    //LED ติด เมื่อส่งค่า
  } else if (state == 0) {
    Serial.println("No one!");
    digitalWrite(LED, LOW);     //LED ดับ เมื่อไม่ได้ส่งค่า
  }
  delay(3000);
}

void NotifyLine(String t) {
  WiFiClientSecure client;
  client.setInsecure();           // ถ้าเป็น ESP32 เวอร์ชั่น 1.0.4 ให้ปิดส่วนนี้ไว้
  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("Connection failed");
    return;
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(TokenLine) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP32\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + t).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + t;

  Serial.println(req);
  client.print(req);
  delay(20);
  Serial.println("-------------");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  } //while
} //loop
