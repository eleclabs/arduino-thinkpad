const int adc1 = 13;
const int adc2 = 12;
int value1 = 0;
int value2 = 0;
const int LED1 = 23;
const int LED2 = 22;


void setup() {
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  value1 = analogRead(adc1);
  value2 = analogRead(adc2);
  
  Serial.println(value1);
  Serial.println(value2);
  
  digitalWrite(LED1, HIGH);
  delay(value1);
  digitalWrite(LED1, LOW);
  delay(value1);
  
  digitalWrite(LED2, HIGH);
  delay(value2);
  digitalWrite(LED2, LOW);
  delay(value2);
  
}
