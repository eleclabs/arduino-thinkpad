#define D0 16
int btnState = HIGH;

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin();  
  
  pinMode(D0,INPUT);
}

void loop() {
 btnState = digitalRead(D0);
  if(btnState == LOW){
  Serial.print("Ambient = "); 
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); 
  Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient = "); 
  Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); 
  Serial.print(mlx.readObjectTempF()); Serial.println("*F");
  Serial.println();
  delay(3000);
  }else{
    Serial.println("Please scan again!!"); 
  }
}
