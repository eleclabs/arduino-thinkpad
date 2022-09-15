int sw1=2;
int sw2=3;
int led[]={4,5,6,7};
int ML1=9;
int ML2=10;
int MR1=11;
int MR2=12;

void setup() {
  pinMode(sw1, INPUT);
  pinMode(sw2, INPUT);
  pinMode(led[0], OUTPUT);
  pinMode(led[1], OUTPUT);
  pinMode(led[2], OUTPUT);
  pinMode(led[3], OUTPUT);
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
}

void loop() {
  int btn1=HIGH;
  btn1 = digitalRead(sw1);
  if(btn1 == LOW){
    reverse();
  }else{
    forward();
  }
 
}

void forward(){
  for(int i=0; i<=3; i++){
    digitalWrite(led[i],HIGH);
    delay(100);
    digitalWrite(led[i],LOW);
    delay(100);
  }
}

void reverse(){
  for(int i=3; i>=0; i--){
    digitalWrite(led[i],HIGH);
    delay(100);
    digitalWrite(led[i],LOW);
    delay(100);
  }
}
