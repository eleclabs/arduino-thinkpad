const int LED[] = {23,22,21,19};
const int SW1  = 12;
const int SW2  = 13;

void setup() {
   Serial.begin(9600);
  pinMode(LED[0], OUTPUT);
  pinMode(LED[1], OUTPUT);
  pinMode(LED[2], OUTPUT);
  pinMode(LED[3], OUTPUT);
  pinMode(SW1, INPUT_PULLUP);
  pinMode(SW2, INPUT_PULLUP);
}

void loop() {
  int state1 = digitalRead(SW1);
  int state2 = digitalRead(SW2);
  
  if(state1 == LOW){
     Serial.println("Forword");
     for(int i=0; i <=3; i++){
         digitalWrite(LED[i], HIGH);
         delay(200);
         digitalWrite(LED[i], LOW);
         delay(200);
      }
  }else{
     Serial.println("SW OFF");
     digitalWrite(LED[0], LOW); 
     digitalWrite(LED[1], LOW); 
     digitalWrite(LED[2], LOW); 
     digitalWrite(LED[3], LOW); 
  }
  
  if(state2 == LOW){
     Serial.println("Backword");  
     for(int i=3; i >=0; i--){
         digitalWrite(LED[i], HIGH);
         delay(200);
         digitalWrite(LED[i], LOW);
         delay(200);
      }
  }else{
     Serial.println("OFF");
     digitalWrite(LED[0], LOW); 
     digitalWrite(LED[1], LOW); 
     digitalWrite(LED[2], LOW); 
     digitalWrite(LED[3], LOW); 
  }
  
  delay(10);
}
