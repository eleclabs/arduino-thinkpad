#define SW1 2
#define SW2 3
#define LED1 4
#define LED2 5
#define LED3 6
#define LED4 7
#define M1 11
#define M2 12

void setup() {
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
}

void loop() {
  if(digitalRead(SW1) == 0){
    digitalWrite(M1, HIGH);
  }
 
}
