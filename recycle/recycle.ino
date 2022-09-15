#include <Servo.h> // ไลบรารี่ Servo ควรติดตั้ง
Servo myservo;
int State = 0;
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
  myservo.attach(9);
  myservo.write(160); // Setup Servo เปิดฝาเอาขยะออก 
  delay(10000); //หน่วงเวลา 10 วินาที
  myservo.write(0); // Setup กลับตำแหน่ง 0 องศา
}
void loop() {
  int Sr = digitalRead(2); // รับค่า Sensor จากขา 2
  Serial.println(State);
  if (State == 0) {
    if (Sr == 1) { // เมื่อ Sr เซ็นเซอร์มีค่า = 1 
      myservo.write(0); // Servo อยู่ที่ตำแหน่ง 0
      delay(100); 
    }
    else if (Sr == 0) { // เมื่อ Sr เซ็นเซอร์มีค่า = 0 
      myservo.write(160); // Servo หมุนไปที่ 160 องศา
      State = 1; // State มีค่าเท่ากับ 1 
    }
  }
  if (State == 1) { // เมื่อ State = 1
    delay(3000); // หน่วงเวลา 3 นาที
    State = 0; // State มีค่า = 0 
  }
} // กลับไปวนลูป
