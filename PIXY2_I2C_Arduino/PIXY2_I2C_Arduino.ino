#include <Pixy2I2C.h>
Pixy2I2C pixy;  // This is the main Pixy object 
#define CENTER_X 158  //เซตตรงกลางหน้าจอ
#define RANGE_X 50    //ปรับแต่งได้
#define SPEED 10     //ความเร็ว
//--------------------
int MR1 = 6;
int MR2 = 7;
int ML1 = 8;
int ML2 = 9;
void TURNLEFT(int z);
void TURNRIGHT(int z);
void FORWARD(int z);
void BACKWARD(int z);
void STOP(int z);

void setup()
{
   pinMode(MR1, OUTPUT);
   pinMode(MR2, OUTPUT);
   pinMode(ML1, OUTPUT);
   pinMode(ML2, OUTPUT);
  //OK();
  //glcdClear();
  //glcd(0,0, "Running...");
  
  Serial.begin(115200);
  Serial.print("Starting...\n");
  pixy.init();
}

void loop()
{ 
  int i; 
  // grab blocks! 
  pixy.ccc.getBlocks();  //เรียกจำนวนบล็อก
  
  // If there are detect blocks, print them!
  if (pixy.ccc.numBlocks){
    Serial.print("Detected ");
    Serial.println(pixy.ccc.numBlocks);
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block ");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
      //----------------------------------
      int sig = pixy.ccc.blocks[i].m_signature;
      int x = pixy.ccc.blocks[i].m_x;
      int y = pixy.ccc.blocks[i].m_y;
      long w = pixy.ccc.blocks[i].m_width;
      long h = pixy.ccc.blocks[i].m_height;
      long s = w*h;  //เอาใว้ลูกบอลใกล้ ไกล
     
      //ตรวจสอบลูกบอลอยู่ซ้าย หรือขวา
      if(sig == 1){ //ตรวจสอบว่าลูกบอลเป็นตัวใหน
        if(s>100){ //ควบคุมใกล้ ไกล
          FORWARD(SPEED); //เดินเข้าหา
          if(x <= CENTER_X - RANGE_X){ //ตรวจสอบลูกบอลอยู่ซ้าย
             TURNLEFT(SPEED);
          }else if(x >= CENTER_X + RANGE_X){//ตรวจสอบลูกบอลอยู่ขวา
             TURNRIGHT(SPEED);
          }
        }     
      }else{
        STOP(SPEED);  // ถ้าไม่ใช่ให้หยุดนิ่ง
      }   
    }
  }  
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
    digitalWrite(MR1, HIGH);
    digitalWrite(MR2, LOW);
    digitalWrite(ML1, LOW);
    digitalWrite(ML2, HIGH);
    delay(z);
}

void TURNLEFT(int z){
    digitalWrite(MR1, LOW);
    digitalWrite(MR2, HIGH);
    digitalWrite(ML1, HIGH);
    digitalWrite(ML2, LOW);
    delay(z);
}
