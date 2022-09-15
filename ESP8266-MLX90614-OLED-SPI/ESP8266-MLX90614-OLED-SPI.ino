#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdint.h>
#include <Adafruit_MLX90614.h>
 
#define OLED_RESET 4
 
Adafruit_SSD1306 display(OLED_RESET);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
 
#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
 
void setup()   
{                
  Serial.begin(57600);
  Serial.println("Adafruit MLX90614 test");  
  mlx.begin();  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
}
 
 
void loop() 
{
    // Clear the buffer.
  display.clearDisplay();
 
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.print("Ambient: ");
  display.print(mlx.readAmbientTempC()); 
  display.print(" c");
  display.setCursor(0,10);
  display.print("Object: ");
  display.print(mlx.readObjectTempC()); 
  display.print(" c");
  display.display();
  delay(2000);
 
}
