int ry1 = D1;
int ry2 = D2;

void setup() {
  pinMode(ry1, OUTPUT);
  pinMode(ry2, OUTPUT);

}

void loop() {
  
  digitalWrite(ry1, HIGH);
  digitalWrite(ry2, LOW);
  delay(200);
  digitalWrite(ry1, LOW);
  digitalWrite(ry2, HIGH);
  delay(200);
  


}
