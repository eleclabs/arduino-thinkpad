const int ry1 = 23;
const int ry2 = 22;
const int sensor1 = 13;

void setup() {
   pinMode(ry1, OUTPUT);
   pinMode(ry2, OUTPUT);
   pinMode(sensor1, INPUT);
}

void loop() {
   if(digitalRead(sensor1) == HIGH){
      digitalWrite(ry1, HIGH);
   }else{
      digitalWrite(ry1, LOW);
   }
}
