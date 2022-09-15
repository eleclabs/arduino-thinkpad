int LED[] = {23,22,21};

void setup() {
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);  
}

void loop() {
  for(int i=0 ; i<=2 ; i++ ){
    digitalWrite(LED[i],HIGH);
    delay(500);
    digitalWrite(LED[i],LOW);
    delay(500);
  }
}
