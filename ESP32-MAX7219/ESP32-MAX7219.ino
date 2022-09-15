#include <MD_Parola.h>
#include <MD_MAX72xx.h>

// Define the number of devices we have in the chain and the hardware interface
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define DATA_PIN    27  //MOSI 
#define CLK_PIN     25  //SCK
#define CS_PIN      26  //SS
#define MAX_DEVICES 4

MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

String msg,message="Hello World!";

void setup(void)
{
  Serial.begin(115200);
  P.begin();
  P.setIntensity(0);  //Intensity 0-15
}

void loop(void)
{ 
  if(Serial.available())
  {
    message="";
    while(Serial.available()) message+=(char)Serial.read();
    Serial.println("Message="+message);
  }
     
  if(P.displayAnimate())
  {
    msg=message;
    P.displayText(msg.c_str(),PA_LEFT,100,1,PA_SCROLL_LEFT,PA_SCROLL_LEFT); 
  }
}
