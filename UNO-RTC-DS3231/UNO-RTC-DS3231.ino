// Date, Time and Alarm functions using a DS3231 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <SPI.h>  // not used here, but needed to prevent a RTClib compile error
#include <RTClib.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2,3); //(Tx,Rx)
int RY1 = 8;
int RY2 = 9;
int RY3 = 10;
int RY4 = 11;

#define LDR 13

RTC_DS3231 RTC;

void setup () {
  pinMode(RY1, OUTPUT);
  pinMode(RY2, OUTPUT);
  pinMode(RY3, OUTPUT);
  pinMode(RY4, OUTPUT);
  pinMode(LDR, INPUT_PULLUP);

  mySerial.begin(9600);
  Serial.begin(9600);
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
}

void loop () {
  if(mySerial.available() > 0){
    char ch = mySerial.read();
    
    /*
    if(ch == 'A'){
      digitalWrite(RY1, LOW);  //ติด active 0
    }else { 
      digitalWrite(RY1, HIGH); //ดับ
    }
    if(ch == 'B'){
      digitalWrite(RY2, LOW);  //ติด active 0
    }else{ 
      digitalWrite(RY2, HIGH); //ดับ
    }
    if(ch == 'C'){
      digitalWrite(RY3, LOW);  //ติด active 0
    }else{ 
      digitalWrite(RY3, HIGH); //ดับ
    }
    if(ch == 'D'){
      digitalWrite(RY4, LOW);  //ติด active 0
    }else{ 
      digitalWrite(RY4, HIGH); //ดับ
    }   
    if(ch == 'E'){
      digitalWrite(RY1, LOW);  //ติด active 0
      digitalWrite(RY2, LOW);  //ติด active 0
      digitalWrite(RY3, LOW);  //ติด active 0
      digitalWrite(RY4, LOW);  //ติด active 0
    }
    if(ch == 'F'){
      digitalWrite(RY1, HIGH); //ดับ
      digitalWrite(RY2, HIGH); //ดับ
      digitalWrite(RY3, HIGH); //ดับ
      digitalWrite(RY4, HIGH); //ดับ
    }
    */
    if(ch == '0'){
      digitalWrite(RY4, LOW);  //ติด active 0
    }else if(ch == '1') { 
      digitalWrite(RY4, HIGH); //ดับ
    }

  }
  
  //ควบคุมไฟแสงสว่างด้วย LDR
  int statusLDR=digitalRead(LDR);
  if(statusLDR == HIGH){  
    digitalWrite(RY2,LOW);      //สั่งให้ ติด acrive 0
    Serial.print("Light ON  \n");
  }else{
    digitalWrite(RY2,HIGH); 
    Serial.print("Light OFF  \n");
  }
  
  //ตั้งเวลาจับเวลา
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
  
  if (now.hour() == 8 && now.minute() == 30 ) { //ถ้าชั่วโมงเท่ากับ 8 และนาทีเท่ากับ 30 จะสั่งให้เปิดไฟ 
    digitalWrite(RY1, LOW); // สั่งให้ ติด active 0
    Serial.println("RY1 ON");
  }else{
    digitalWrite(RY1, HIGH); // สั่งให้ ดับ
    Serial.println("RY1 OFF");
  }

  if (now.second() == 10 ) { //ถ้าวินาทีเท่ากับ 10 จะสั่งให้เปิดไฟ 
    digitalWrite(RY1, LOW); // สั่งให้ ติด active 0
    Serial.println("RY1 ON");
    delay(10000);
  }else{
    Serial.println("RY1 OFF");
    digitalWrite(RY1, HIGH); // สั่งให้ ดับ
  }

  if (now.second() == 30 ) { //ถ้าวินาทีเท่ากับ 30 จะสั่งให้เปิดไฟ 
    digitalWrite(RY1, LOW); // สั่งให้ ติด active 0
    Serial.println("RY1 ON");
    delay(10000);
  }else{
    digitalWrite(RY1, HIGH); // สั่งให้ดับ
    Serial.println("RY1 OFF");
  }

  if (now.second() == 50) { //ถ้าวินาทีเท่ากับ 50 จะสั่งให้เปิดไฟ 
    digitalWrite(RY1, LOW); // สั่งให้ ติด active 0
    Serial.println("RY2 ON");
    delay(10000);
  }else{
    digitalWrite(RY1, HIGH); // สั่งให้ ดับ
    Serial.println("RY1 OFF");
  }

  Serial.println();
  delay(1000);
}
