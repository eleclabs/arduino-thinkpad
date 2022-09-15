int LED1 = 23;
int SENSOR1 = 22;

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(SENSOR1, INPUT);

}

void loop() {
  digitalWrite(LED1, HIGH);
  delay(4000);
  digitalWrite(LED1, LOW);
  delay(500);

}
