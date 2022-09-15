const int buttonPin = A0;
int buttonState = 0;
#include <Servo.h>
Servo myservo;
void setup() {
  myservo.attach(A1);
  pinMode(buttonPin, INPUT);
}
void loop(){
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
      myservo.write(0);
      delay(0);
  } else {
    myservo.write(105);
  }
}
