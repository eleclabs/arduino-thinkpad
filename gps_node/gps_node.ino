
#include "TinyGPS++.h"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial

char auth[] = "xTXuGacAdsHkfMzptMPI4go-5YsiYBi8";
char ssid[] = "GpsWiFi";
char pass[] = "01234567890";
BlynkTimer timer;
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
void setup()
{
Serial.begin(9600);//This opens up communications to the Serial monitor in the Arduino IDE
Serial.println("GPS Start");//Just show to the monitor that the sketch has started
Blynk.begin(auth, ssid, pass);
timer.setInterval(1000L, sendGPS);

}
String lat_ ;
String lon_ ;
int speed_ = 0 ;
int Index1 = 0;

void sendGPS()
{
  Blynk.virtualWrite(V1, Index1, lat_, lon_, "value");
  Blynk.virtualWrite(V2, speed_);
}

void loop()
{
  Blynk.run();   /* Initiates Blynk */
  timer.run();    /* run BlynkTimer */
  
while(Serial.available())//While there are characters to come from the GPS
{
gps.encode(Serial.read());//This feeds the serial NMEA data into the library one char at a time
}
if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
{
//Get the latest info from the gps object which it derived from the data sent by the GPS unit
lat_ = String(gps.location.lat(),6);
lon_ = String(gps.location.lng(),6);
speed_ =  gps.speed.mph() ;

Serial.println("Latitude:");
Serial.println(lat_);
Serial.println("Longitude:");
Serial.println(gps.location.lng(), 6);
Serial.println("Speed MPH:");
Serial.println(gps.speed.mph());
Serial.println("");
}
}
