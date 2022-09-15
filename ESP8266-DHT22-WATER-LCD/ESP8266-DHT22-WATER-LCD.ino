#include <Wire.h>
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
/*
#include <SPI.h>  // not used here, but needed to prevent a RTClib compile error
#include <RTClib.h>
RTC_DS3231 RTC;
*/
#define RY1 D5
#define RY2 D6
#define RY3 D7
#define RY4 D8

#define LDR D4

#define DHTPIN D0
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22 (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);
//LiquidCrystal_I2C lcd(0x3F, 16, 2); // ถ้าจอไม่ขึ้นให้ลองใช้ตำแหน่ง 0x3F นี้

void setup() {
  pinMode(RY1, OUTPUT);
  pinMode(RY2, OUTPUT);
  pinMode(LDR, INPUT_PULLUP);
  
  Serial.begin(115200);
  delay(100);
/*
  Wire.begin();
  RTC.begin();
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
  */
  dht.begin();
  lcd.begin();  
 // lcd.backlight();   //เปิดไฟ backlight
}

void loop() {
/*
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
  
  if (now.hour() == 15 && now.minute() == 55 ) { //ถ้าชั่วโมงเท่ากับ 22 และนาทีเท่ากับ 19 จะสั่งให้เปิดไฟ 
    digitalWrite(RY3, LOW); // สั่งให้ Relay3 ติด
    Serial.println("RY3 ON");
  }else{
    digitalWrite(RY3, HIGH); // สั่งให้ Relay3 ดับ
    Serial.println("RY3 OFF");
  }

  if (now.second() >= 0 ) { //ถ้าวินาทีเท่ากับ 60 จะสั่งให้เปิดไฟ 
    digitalWrite(RY4, HIGH); // สั่งให้ Relay4 ติด
    Serial.println("RY4 ON");
    delay(10000);
  }else{
    digitalWrite(RY4, LOW); // สั่งให้ Relay4 ดับ
    Serial.println("RY4 OFF");
  }
  
  Serial.println();
  
  
  int btnLDR=digitalRead(LDR);

  */
  
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

  if(t >= 28 ){
    digitalWrite(RY1, HIGH);
    Serial.print("Relay ON  \n");
  }else{
    digitalWrite(RY1, LOW); 
    Serial.print("Relay OFF  \n");
  }
/*
  if(btnLDR == HIGH){
    digitalWrite(RY2, HIGH);
    Serial.print("Light ON  \n");
  }else{
    digitalWrite(RY2, LOW); 
    Serial.print("Light OFF  \n");
  }
*/
   delay(2000);
}
