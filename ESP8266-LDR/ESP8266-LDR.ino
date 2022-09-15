
#define RY1 5
#define RY2 4
#define RY3 0
#define RY4 2

#define LDR 13

void setup() {
  pinMode(RY1, OUTPUT);
  pinMode(RY2, OUTPUT);
  pinMode(RY3, OUTPUT);
  pinMode(RY4, OUTPUT);
  pinMode(LDR, INPUT_PULLUP);
  
  Serial.begin(115200);
  delay(100);
  
}
void loop() {
  int btnLDR=digitalRead(LDR);
  
  if(btnLDR == LOW){  
    digitalWrite(RY1,HIGH);
    Serial.print("Light ON  \n");
  }else{
    digitalWrite(RY1,LOW); 
    Serial.print("Light OFF  \n");
  }

   delay(1000);
}
