const int mr1 = 12;
const int mr2 = 13;
const int ml1 = 25;
const int ml2 = 26;
const int sl = 34; 
const int sr = 39; 
const int sf = 4;  

void setup() {
  pinMode(mr1, OUTPUT);
  pinMode(mr2, OUTPUT);
  pinMode(ml1, OUTPUT);
  pinMode(ml2, OUTPUT);
  pinMode(sl, INPUT);
  pinMode(sr, INPUT);
  pinMode(sf, INPUT);
}

void back(void);
void front(void);
void right(void);
void left(void);
void stoped(void);

void loop() {
  const int slState= digitalRead(sl);
  const int srState= digitalRead(sr);
  const int sfState= digitalRead(sf);
  
  if(slState==LOW && srState==HIGH ){ //Turn Right
    if(sfState == LOW){
      back();
    }else{
      right();
    }
  }
  else if(slState==HIGH && srState==LOW ){ //Turn Left
    if(sfState == LOW){
      back();
    }else{
      left();
    }
  }else if(slState==LOW && srState==LOW ){  //ถอยหลัง
     if(sfState == LOW){
      back();
    }else{
      back();
    }
  }else if(slState==HIGH && srState==HIGH ){  //เดินหน้า
     if(sfState == LOW){
      back();
    }else{
      front();
    }
  }else{  //หยุด
    stoped();
  }
  
}

//---ฟังก์ชั่นต่างๆ
void back(void){
   digitalWrite(mr1, LOW); 
   digitalWrite(mr2, HIGH); 
   digitalWrite(ml1, LOW); 
   digitalWrite(ml2, HIGH); 
   delay(10);
}
void front(void){
   digitalWrite(mr1, HIGH); 
   digitalWrite(mr2, LOW); 
   digitalWrite(ml1, HIGH); 
   digitalWrite(ml2, LOW); 
   delay(10);
}
void right(void){
    digitalWrite(mr1, LOW); 
    digitalWrite(mr2, HIGH); 
    digitalWrite(ml1, HIGH); 
    digitalWrite(ml2, LOW); 
    delay(10);
}
void left(void){
    digitalWrite(mr1, HIGH); 
    digitalWrite(mr2, LOW); 
    digitalWrite(ml1, LOW); 
    digitalWrite(ml2, HIGH); 
    delay(10);
}
void stoped(void){
   digitalWrite(mr1, LOW); 
   digitalWrite(mr2, LOW); 
   digitalWrite(ml1, LOW); 
   digitalWrite(ml2, LOW); 
   delay(10);
}
