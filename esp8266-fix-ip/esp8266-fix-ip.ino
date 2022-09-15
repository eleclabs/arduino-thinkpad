#include <ESP8266WiFi.h> //เป็นการเรียกใช้ Library โมดูล ESP8266

const char* ssid = "nodemcu_wifi"; //สร้างตัวแปรไว้เก็บชื่อ ssid ของ AP ของเรา
const char* pass = "password"; //สร้างตัวแปรไว้เก็บชื่อ password ของ AP ของเรา

// Static IP details...
IPAddress ip(192, 168, 1, 111);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress DNS(192, 168, 1, 1);

void setup () {
  Serial.begin(115200); //ตั้งค่าใช้งาน serial ที่ baudrate 115200
  // Static IP Setup Info Here...
  WiFi.config(ip, gateway, subnet, DNS);
  WiFi.begin(ssid, pass); //ทำการเชื่อมต่อไปยัง AP

  while (WiFi.status() != WL_CONNECTED) { //รอจนกว่าจะเชื่อมต่อสำเร็จ 
    Serial.print("."); //แสดง ... ไปเรื่อยๆ จนกว่าจะเชื่อมต่อได้
    delay(500);
  } //ถ้าเชื่อมต่อสำเร็จก็จะหลุด loop while ไป

  Serial.println(""); 
  Serial.print("Wi-Fi connected to "); //แสดงว่าเชื่อมต่อ Wi-Fi ได้แล้ว
  Serial.println(ssid);
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP()); //แสดง IP ของบอร์ดที่ได้รับแจกจาก AP
}

void loop () { //ยังไม่ต้องมีการวนอะไรใดๆ เลยปล่อย void loop ว่างไว้เฉยๆ
}
