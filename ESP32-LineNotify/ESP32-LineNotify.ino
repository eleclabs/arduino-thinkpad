#include <WiFi.h>
#include <WiFiClientSecure.h>

//########## CONFIGURATION : MODIFY HERE ##########
char ssid[] = "A12"; // เครือข่าย Wi-Fi ที่ต้องการเชื่อมต่อ
char pass[] = "42117622"; // รหัสผ่านเครือข่าย

//รหัสเชื่อมต่อ Line token
#define TokenLine "zTYYn6JVn5ANpMxOnFHl9S0gZEe2ejvweGactlfkXV0"

// ข้อความ ที่จะแสดงใน Line
String txt1 = "การศึกษา คือการลงทุน, การทำงาน คือการถอนทุน!! ";

byte sensorPin = 23;    //กำหนดขาที่เชื่อมต่อกับเซ็นเซอร์
const int LED = 2;      //LED แสดงสถาน่ะการทำงาน

void setup() {
    pinMode(sensorPin, INPUT);  //กำหนดให้ขาดิจิตอล sensorPin รับข้อมูลจากเซ็นเซอร์
    pinMode(LED,OUTPUT);
    
    //ตั้งค่าคอนโซล
    Serial.begin(115200);
    
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
    byte state = digitalRead(sensorPin);
    
    if (state == 1) {
      Serial.println("Somebody is in this area!");
      NotifyLine(txt1); //ส่งค่าไปที่ Line Notify
      digitalWrite(LED, HIGH);    //LED ติด เมื่อส่งค่า
    }else if (state == 0) {
      Serial.println("No one!");
      digitalWrite(LED, LOW);     //LED ดับ เมื่อไม่ได้ส่งค่า
    }
    delay(5000);
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
