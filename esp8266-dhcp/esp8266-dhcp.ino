#include <ESP8266WiFi.h> //เป็นการเรียกใช้ Library โมดูล ESP8266

const char* ssid = "nodemcu_wifi"; //สร้างตัวแปรไว้เก็บชื่อ ssid ของ AP ของเรา
const char* pass = "123456"; //สร้างตัวแปรไว้เก็บชื่อ password ของ AP ของเรา

void setup () {
  pinMode(LED_BUILTIN, OUTPUT); 
  
  Serial.begin(115200); //ตั้งค่าใช้งาน serial ที่ baudrate 115200
  delay(10);

  // Connect to WiFi network
  Serial.println();
  WiFi.begin(ssid, pass); //ทำการเชื่อมต่อไปยัง AP

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) { //รอจนกว่าจะเชื่อมต่อสำเร็จ 
    delay(500);
    Serial.print("."); //แสดง ... ไปเรื่อยๆ จนกว่าจะเชื่อมต่อได้
  } //ถ้าเชื่อมต่อสำเร็จก็จะหลุด loop while ไป

  Serial.println(""); 
  Serial.print("Wi-Fi connected to "); //แสดงว่าเชื่อมต่อ Wi-Fi ได้แล้ว
  Serial.println(ssid);
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP()); //แสดง IP ของบอร์ดที่ได้รับแจกจาก AP
}

void loop () { //ยังไม่ต้องมีการวนอะไรใดๆ เลยปล่อย void loop ว่างไว้เฉยๆ
  digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because
                                    // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(2000);                      // Wait for two seconds (to demonstrate the active low LED)
}
