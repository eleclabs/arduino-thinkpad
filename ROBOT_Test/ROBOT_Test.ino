#define SPEED 3000     //ความเร็ว

int MR1 = 7;
int MR2 = 6;
int ML1 = 5;
int ML2 = 4;

void TURNLEFT(int z);
void TURNRIGHT(int z);
void FORWARD(int z);
void BACKWARD(int z);
void STOP(int z);

void setup() {
   pinMode(MR1, OUTPUT);
   pinMode(MR2, OUTPUT);
   pinMode(ML1, OUTPUT);
   pinMode(ML2, OUTPUT);
   Serial.begin(115200);
   Serial.print("Starting...\n");

}

void loop() {
  FORWARD(SPEED);
  //BACKWARD(SPEED);
  //TURNLEFT(SPEED);
  //TURNRIGHT(SPEED);
  //STOP(SPEED);
}

void STOP(int z){
    digitalWrite(MR1, LOW);
    digitalWrite(MR2, LOW);
    digitalWrite(ML1, LOW);
    digitalWrite(ML2, LOW);
    delay(z);
}

void FORWARD(int z){
    digitalWrite(MR1, HIGH);
    digitalWrite(MR2, LOW);
    digitalWrite(ML1, HIGH);
    digitalWrite(ML2, LOW);
    delay(z);
}

void BACKWARD(int z){
    digitalWrite(MR1, LOW);
    digitalWrite(MR2, HIGH);
    digitalWrite(ML1, LOW);
    digitalWrite(ML2, HIGH);
    delay(z);
}

void TURNRIGHT(int z){
    digitalWrite(MR1, LOW);
    digitalWrite(MR2, HIGH);
    digitalWrite(ML1, HIGH);
    digitalWrite(ML2, LOW);
    delay(z);
}

void TURNLEFT(int z){
    digitalWrite(MR1, HIGH);
    digitalWrite(MR2, LOW);
    digitalWrite(ML1, LOW);
    digitalWrite(ML2, HIGH);  
    delay(z);
}
