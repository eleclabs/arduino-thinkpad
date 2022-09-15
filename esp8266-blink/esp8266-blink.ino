int ry1 = D5;
int ry2 = D6;
int ry3 = D7;
int ry4 = D8;


void setup()
{
  pinMode(ry1,OUTPUT);
  pinMode(ry2,OUTPUT);
  pinMode(ry3,OUTPUT);
  pinMode(ry4,OUTPUT);
}
void loop()
{
   digitalWrite(ry1,LOW);
   digitalWrite(ry2,HIGH);
   digitalWrite(ry3,HIGH);
   digitalWrite(ry4,HIGH);
   delay(1000);
   digitalWrite(ry1,HIGH);
   digitalWrite(ry2,LOW);
   digitalWrite(ry3,HIGH);
   digitalWrite(ry4,HIGH);
   delay(1000);
   digitalWrite(ry1,HIGH);
   digitalWrite(ry2,HIGH);
   digitalWrite(ry3,LOW);
   digitalWrite(ry4,HIGH);
   delay(1000);
   digitalWrite(ry1,HIGH);
   digitalWrite(ry2,HIGH);
   digitalWrite(ry3,HIGH);
   digitalWrite(ry4,LOW);
   delay(1000);
   
}
