#define SW1 2  
#define SW2 3
int LED[] = { 4,5,6,7 };
#define MR1 9
#define MR2 10
#define ML1 11
#define ML2 12
int btn1 = 1;
int btn2 = 1;

void setup() {
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
}

void loop() {
  btn1= digitalRead(SW1);
  btn2= digitalRead(SW2);

  if(btn1 == 0){
    digitalWrite(MR1, HIGH);
    delay(10);
    digitalWrite(MR2, LOW);
     delay(10);
    digitalWrite(ML1, HIGH);
     delay(10);
    digitalWrite(ML2, LOW);
     delay(10);
  }else{
    digitalWrite(MR1, LOW);
    digitalWrite(MR2, LOW);
    digitalWrite(ML1, LOW);
    digitalWrite(ML2, LOW);
  }
   if(btn2 == 0){
    digitalWrite(MR1, LOW);
     delay(10);
    digitalWrite(MR2, HIGH);
     delay(10);
    digitalWrite(ML1, LOW);
     delay(10);
    digitalWrite(ML2, HIGH);
     delay(10);
  }else{
    digitalWrite(MR1, LOW);
    digitalWrite(MR2, LOW);
    digitalWrite(ML1, LOW);
    digitalWrite(ML2, LOW);
  }

  for(int x=0; x<=3; x++){
    digitalWrite(LED[x], HIGH);
    delay(500);
    digitalWrite(LED[x], LOW);
  }
   for(int x=3; x>=0; x--){
    digitalWrite(LED[x], HIGH);
    delay(500);
    digitalWrite(LED[x], LOW);
  }

}
