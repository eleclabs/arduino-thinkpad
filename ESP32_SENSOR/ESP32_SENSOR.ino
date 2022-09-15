int ledPin= 13;
int inputPin= 2;

void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
}

void loop(){
  int value= digitalRead(inputPin);

  if (value == HIGH)
  {
    digitalWrite(ledPin, HIGH);
    delay(1000) ;
  }

  else
  {
    digitalWrite(ledPin, LOW);

delay(1000) ;
  }
}

 
