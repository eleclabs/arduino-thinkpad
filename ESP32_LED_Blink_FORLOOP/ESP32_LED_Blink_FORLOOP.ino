const int LED[] = {23,22,21,19};

void setup() { 
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
}

void loop() {
  for(int i=0; i <=3; i++){
    digitalWrite(LED[i], HIGH);
    delay(200);
    digitalWrite(LED[i], LOW);
    delay(200);
  }
}
