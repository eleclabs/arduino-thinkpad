
#include <Wire.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include "Arduino.h"
#include "esp32-hal-cpu.h"
#include <Adafruit_MLX90614.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HTTPClient.h>
String Linetoken = "Your New Line Token";                                                    //Your New Line Token


int threshold = 4;                                                                          //MLX90614 Calibration for Body mode (Surface + 4 C=Body)
float temp, Objtemp1, Objtemp2;
bool setCpuFrequencyMhz(uint32_t cpu_freq_mhz);
uint16_t result;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32                                                                    //Set OLED pixel=128 * 32  
#define pin2 26                                                                             // Switch to measure Surface Mode
#define pin3 27                                                                             // Switch to measure Body Mode

WiFiClientSecure client;                                                                     //WIFIClient library name use symbol to replace
char host[] = "notify-api.line.me";                                                          //LINE Notify API web address


// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WIFI SSID";  //Home WIFI SSID
char password[] = "WIFI Password";  //Home WIFI Password

String url = "https://api.thingspeak.com/update?api_key=KE393NY4C7E4Y3UH&field1=25";        //Set Thingspeak chanel

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)                //Set OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);                   //Set OLED

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup()
{

  setCpuFrequencyMhz(240);                                                                   //Set CPU clock to 240MHz fo example
  Wire.begin(21, 22, 100000);                                                                //I2C pin: SCL pin=22, SDA pin=21, I2C frequency=50K hz (Default is 100K hz)
  Serial.begin(115200);

  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin3, INPUT_PULLUP);

  // Initial WIFI
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)                                                                         //Wait for connection ok
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");                                                                            //WIFI cooection ok
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());                                                                              //Disaply ESP32 WIFI IP

  // Detect OLED installtion ok or not and Address 0x3C for 128x32
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  init_display();
  Serial.println("MLX90614 infra-red temperature sensor test");                                                //Initalation IR sensor-MLX90614
  mlx.begin();
}



void loop()
{
Mode: while (digitalRead(pin2) == LOW)
  {
    Serial.println("IO26 is pressed");
    Serial.println(digitalRead(pin2));
    display.clearDisplay();
    delay(1000);
    get_surface();
    delay(500);
    unit_display();
    web_surface();
    Line_surface();

    if (digitalRead(pin2) == LOW) continue;
    if (digitalRead(pin2) == HIGH) break;
  }
  goto BODY;

BODY: while (digitalRead(pin3) == LOW)
  {
    Serial.println("IO27 is pressed");
    Serial.println(digitalRead(pin3));
    display.clearDisplay();
    delay(1000);
    get_body();
    delay(500);
    unit_display();
    web_body();
    Line_body();
    if (digitalRead(pin3) == LOW) continue;
    if (digitalRead(pin3) == HIGH) break;
  }
  goto Mode;

}

void init_display()
{
  display.clearDisplay();
  display.setRotation(2);                                                                   //OLED顯示轉向，可自行決定方向
  display.setTextSize(2);                                                                   // Set Text size
  display.setTextColor(1);                                                                  // Set OLD Color (Default is 1)
  display.setCursor(0, 0);                                                                 // Start at top-left corner
  display.print("YZU_Brian");
  display.display();
  delay(1000);
}

void unit_display()
{ //Display "oC"
  display.setTextSize(2);
  display.setCursor(99, 0);
  display.print("o");
  display.setTextSize(2);
  display.setCursor(109, 12);
  display.print("C");
  display.display();
  delay(500);
}

void get_surface()
{
  Wire.beginTransmission(0x5A);                                                                          //Start to send MLX90614 I2C address-0x5A
  Wire.write(0x07);                                                                                      // Write I2C data to MLX90614 address-0x07 (Ogject Temperature)
  Wire.endTransmission(false);                                                                           // I2C stop transmission
  Wire.requestFrom(0x5A, 3);                                                                             //Request the I2C data with 3 Bytes from the address of MLX90614
  result = Wire.read();                                                                                  //Receive DATA
  result |= Wire.read() << 8;                                                                            //Receive DATA
  uint8_t pec = Wire.read();
  temp =  result * 0.02 - 273.15;                                                                        //Measure Surface Temperature
  Objtemp1 = temp;
  Serial.println(Objtemp1, 1);
  Serial.println(" *C");
  display.setCursor(0, 4);
  display.print(Objtemp1, 1);
}

void get_body()
{
  Wire.beginTransmission(0x5A);                                                                          //Start to send MLX90614 I2C address-0x5A
  Wire.write(0x07);                                                                                      // Write I2C data to MLX90614 address-0x07 (Ogject Temperature)
  Wire.endTransmission(false);                                                                           // I2C stop transmission
  Wire.requestFrom(0x5A, 3);                                                                             //Request the I2C data with 3 Bytes from the address of MLX90614
  result = Wire.read();                                                                                  //Receive DATA
  result |= Wire.read() << 8;                                                                            //Receive DATA
  uint8_t pec = Wire.read();
  temp =  result * 0.02 - 273.15;                                                                        //Measure Surface Temperature
  Objtemp2 = temp + threshold;
  Serial.println(Objtemp2, 1);
  Serial.println(" *C");
  display.setCursor(0, 4);
  display.print(Objtemp2, 1);
}

void web_surface()
{
  //Forward its value to Thingspeak
  Serial.println("Connect Web");
  HTTPClient http;
  String url1 = url + "&field1=" + (int)Objtemp1;                                             // Show the value of Temperature and Humidity by parameter with Http get on Web
  http.begin(url1);                                                                           //Get the content of heep client
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
  {
    String payload = http.getString();                                                   //Read content of the Web on payload
    Serial.print("Web content=");                                                        //Display the content of Web
    Serial.println(payload);
  }
  else
  {
    Serial.println("Web connect fail");
  }
  http.end();
  delay(5000);
}

void web_body()
{
  //Forward its value to Thingspeak
  Serial.println("Connect Web");
  HTTPClient http;
  String url2 = url + "&field1=" + (int)Objtemp2;                                       // Show the value of Temperature and Humidity by parameter with Http get on Web
  http.begin(url2);                                                                      //Get the content of heep client
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK)
  {
    String payload = http.getString();                                                   //Read content of the Web on payload
    Serial.print("Web content=");                                                        //Display the content of Web
    Serial.println(payload);
  }
  else
  {
    Serial.println("Web connect fail");
  }
  http.end();
  delay(5000);
}

void Line_surface()
{
  //ESP32 will send its warming if the temperaure is over than 30C
  if (Objtemp1 >= 20 )
  {
    //組成Line訊息內容
    String message = "The Temperaute will risk";                                                           //The message content of Line
    message += "\nTemperature=" + String((int)Objtemp1) + " *C";           //The message content of Line

    Serial.println(message);
    if (client.connect(host, 443))
    {
      int LEN = message.length();
      String url1 = "/api/notify";                                                       //Pass POST header
      client.println("POST " + url1 + " HTTP/1.1");                                      //Pass POST header
      client.print("Host: "); client.println(host);                                      //Pass POST header

      client.print("Authorization: Bearer "); client.println(Linetoken);                //access token
      client.println("Content-Type: application/x-www-form-urlencoded");                //access token
      client.print("Content-Length: "); client.println( String((LEN + 8)) );            //access token
      client.println();                                                                 //access token
      client.print("message="); client.println(message);                                //access token
      client.println();

      delay(1000);                                                                        //Delay 1 sec
      String response = client.readString();

      Serial.println(response);                                                         //Display send complete
      client.stop();                                                                    //Stop client connection
    }
    else
    {
      Serial.println("connected fail");                                                 //Disaply "Connected fail " if the temperature value cannot send to Line
    }
  }
  delay(3000);
}

void Line_body()
{
  //ESP32 will send its warming if the temperaure is over than 30C
  if (Objtemp2 >= 30 )
  {
    //組成Line訊息內容
    //    String message = "目前待測物溫度有偏高趨勢, 請派人前往處理";                               //The message content of Line
    String message = "The Temperaute will risk";                               //The message content of Line
    message += "\nTemperature=" + String((int)Objtemp2) + " *C";           //The message content of Line

    Serial.println(message);
    if (client.connect(host, 443))
    {
      int LEN = message.length();
      String url2 = "/api/notify";                                                       //Pass POST header
      client.println("POST " + url2 + " HTTP/1.1");                                      //Pass POST header
      client.print("Host: "); client.println(host);                                      //Pass POST header

      client.print("Authorization: Bearer "); client.println(Linetoken);                //access token
      client.println("Content-Type: application/x-www-form-urlencoded");                //access token
      client.print("Content-Length: "); client.println( String((LEN + 8)) );            //access token
      client.println();                                                                 //access token
      client.print("message="); client.println(message);                                //access token
      client.println();

      delay(1000);                                                                        //Delay 1 sec
      String response = client.readString();

      Serial.println(response);                                                         //Display send complete
      client.stop();                                                                    //Stop client connection
    }
    else
    {
      Serial.println("connected fail");                                                 //Disaply "Connected fail " if the temperature value cannot send to Line
    }
  }
  delay(3000);
}
