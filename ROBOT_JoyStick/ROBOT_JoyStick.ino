#define SPEED 30     //ความเร็ว
int VRx = A0;
int VRy = A1;
int SW = 2;
int MR1 = 7;
int MR2 = 6;
int ML1 = 5;
int ML2 = 4;
//กำหนดค่าเริ่มต้น
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

void TURNLEFT(int z);
void TURNRIGHT(int z);
void FORWARD(int z);
void BACKWARD(int z);
void STOP(int z);

void setup() {
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);

  pinMode(MR1, OUTPUT);
  pinMode(MR2, OUTPUT);
  pinMode(ML1, OUTPUT);
  pinMode(ML2, OUTPUT);
  Serial.begin(115200);
  Serial.print("Starting...\n");

}

void loop() {
  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  Serial.print("X: ");
  Serial.print(mapX);
  Serial.print(" | Y: ");
  Serial.print(mapY);
  Serial.print(" | Button: ");
  Serial.println(SW_state);

  delay(100);
  if(mapX >= 500){
    FORWARD(SPEED);
  }else if(mapX <= 500){
    BACKWARD(SPEED);
  }

  if(mapY>=500){
    TURNLEFT(SPEED);
  }else if(mapX <= 500){
    TURNRIGHT(SPEED);
  }
  
 
  //STOP(SPEED);
}

void STOP(int z) {
  digitalWrite(MR1, LOW);
  digitalWrite(MR2, LOW);
  digitalWrite(ML1, LOW);
  digitalWrite(ML2, LOW);
  delay(z);
}

void FORWARD(int z) {
  digitalWrite(MR1, HIGH);
  digitalWrite(MR2, LOW);
  digitalWrite(ML1, HIGH);
  digitalWrite(ML2, LOW);
  delay(z);
}

void BACKWARD(int z) {
  digitalWrite(MR1, LOW);
  digitalWrite(MR2, HIGH);
  digitalWrite(ML1, LOW);
  digitalWrite(ML2, HIGH);
  delay(z);
}

void TURNRIGHT(int z) {
  digitalWrite(MR1, LOW);
  digitalWrite(MR2, HIGH);
  digitalWrite(ML1, HIGH);
  digitalWrite(ML2, LOW);
  delay(z);
}

void TURNLEFT(int z) {
  digitalWrite(MR1, HIGH);
  digitalWrite(MR2, LOW);
  digitalWrite(ML1, LOW);
  digitalWrite(ML2, HIGH);
  delay(z);
}
