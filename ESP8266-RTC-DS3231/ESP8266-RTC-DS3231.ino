// Date, Time and Alarm functions using a DS3231 RTC connected via I2C and Wire lib

#include <Wire.h>
#include <SPI.h>  // not used here, but needed to prevent a RTClib compile error
#include <RTClib.h>
int RY1 = D1;
int RY2 = D2;

RTC_DS3231 RTC;

void setup () {
  pinMode(RY1, OUTPUT);
  pinMode(RY2, OUTPUT);
  
  Serial.begin(9600);
  Wire.begin();
  RTC.begin(10,9);

  RTC.adjust(DateTime(__DATE__, __TIME__));
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  DateTime now = RTC.now();
  RTC.setAlarm1Simple(21, 58);
  RTC.turnOnAlarm(1);
  if (RTC.checkAlarmEnabled(1)) {
    Serial.println("Alarm Enabled");
  }
}

void loop () {
  DateTime now = RTC.now();

  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

  if (RTC.checkIfAlarm(1)) {
    Serial.println("Alarm Triggered");
  }
  
  if (now.hour() == 22 && now.minute() == 19 ) { //ถ้าชั่วโมงเท่ากับ 22 และนาทีเท่ากับ 19 จะสั่งให้เปิดไฟ 
    digitalWrite(RY1, HIGH); // สั่งให้ Relay1 ติด
    Serial.println("RY1 ON");
  }else{
    Serial.println("RY1 OFF");
    digitalWrite(RY1, LOW); // สั่งให้ Relay1 ดับ
  }

  if (now.second() == 10 ) { //ถ้าวินาทีเท่ากับ 10 จะสั่งให้เปิดไฟ 
    digitalWrite(RY2, HIGH); // สั่งให้ Relay1 ติด
    Serial.println("RY1 ON");
  }else{
    Serial.println("RY1 OFF");
    digitalWrite(RY2, LOW); // สั่งให้ Relay1 ดับ
  }

  
  Serial.println();
  delay(1000);
}
