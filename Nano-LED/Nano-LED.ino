int LED0 = 0;
int LED1 = 1;
int LED2 = 2;
int LED3 = 3;

void setup() {
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
}

void loop() {
  digitalWrite(LED0, HIGH); 
  digitalWrite(LED1, LOW); 
  digitalWrite(LED2, LOW); 
  digitalWrite(LED3, LOW); 
  delay(500);
  digitalWrite(LED0, LOW); 
  digitalWrite(LED1, HIGH); 
  digitalWrite(LED2, LOW); 
  digitalWrite(LED3, LOW); 
  delay(500);
  digitalWrite(LED0, LOW); 
  digitalWrite(LED1, LOW); 
  digitalWrite(LED2, HIGH); 
  digitalWrite(LED3, LOW); 
  delay(500);
  digitalWrite(LED0, LOW); 
  digitalWrite(LED1, LOW); 
  digitalWrite(LED2, LOW); 
  digitalWrite(LED3, HIGH); 
  delay(500);
}
