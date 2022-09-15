const int sensor1 = 12;
const int sensor2 = 13;
const int MR1 = 23;
const int MR2 = 22;
const int ML1 = 21;
const int ML2 = 19;
 
void setup() {
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
}

void loop() {
 int sn1 = digitalRead(sensor1);
 int sn2 = digitalRead(sensor2);
  if(sn1 == HIGH){
    turnright();
  }else if(sn2 == HIGH){
    turnleft();
  }else if(sn1 == HIGH && sn2 == HIGH){
    stopped();
    delay(3000);
    reverse();
  }else if(sn1 == LOW && sn2 == LOW){
    forward();
  }else{
    forward();
  }

}

void forward(){
  digitalWrite(MR1, HIGH);
  digitalWrite(MR2, LOW);
  digitalWrite(ML1, HIGH);
  digitalWrite(ML2, LOW);
  delay(1000);
}
void reverse(){
  digitalWrite(MR1, LOW);
  digitalWrite(MR2, HIGH);
  digitalWrite(ML1, LOW);
  digitalWrite(ML2, HIGH);
  delay(1000);
}
void turnleft(){
  digitalWrite(MR1, LOW);
  digitalWrite(MR2, HIGH);
  digitalWrite(ML1, HIGH);
  digitalWrite(ML2, LOW);
  delay(1000);
}
void turnright(){
  digitalWrite(MR1, HIGH);
  digitalWrite(MR2, LOW);
  digitalWrite(ML1, LOW);
  digitalWrite(ML2, HIGH);
  delay(1000);
}
void stopped(){
  digitalWrite(MR1, LOW);
  digitalWrite(MR2, LOW);
  digitalWrite(ML1, LOW);
  digitalWrite(ML2, LOW);
  delay(1000);
}
