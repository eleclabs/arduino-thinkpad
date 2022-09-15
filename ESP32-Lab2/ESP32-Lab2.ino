const int LED1 = 23;
const int LED2 = 22;
const int LED3 = 21;
const int LED4 = 19;
const int SW1  = 12;
const int SW2  = 13;

void setup() {
   Serial.begin(9600);
   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(LED3, OUTPUT);
   pinMode(LED4, OUTPUT);   
   pinMode(SW1, INPUT_PULLUP);
   pinMode(SW2, INPUT_PULLUP);
}

void loop() {
  int state1 = digitalRead(SW1);
  int state2 = digitalRead(SW2);

  if(state1 == LOW){
     Serial.println("SW1 & SW2 ON");
     digitalWrite(LED1, HIGH);
     digitalWrite(LED2, HIGH);
  }else{
     Serial.println("SW1 & SW2 OFF");
     digitalWrite(LED1, LOW);
     digitalWrite(LED2, LOW);
  }

  if(state2 == LOW){
     Serial.println("SW3 & SW4 ON");  
     digitalWrite(LED3, HIGH); 
     digitalWrite(LED4, HIGH);    
  }else{
     Serial.println("SW3 & SW4 OFF");
     digitalWrite(LED3, LOW); 
     digitalWrite(LED4, LOW); 
  }

  delay(100);
}
