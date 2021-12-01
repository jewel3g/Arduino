#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
const int S1 = 14;
const int SMOKE = 12;
const int FLAME = 16;
int Switch = 0;
int smoke = 0;
int flame = 0;

static const int RXPin = 2, TXPin = 0;   // GPIO 4=D2(conneect Tx of GPS) and GPIO 5=D1(Connect Rx of GPS
static const uint32_t GPSBaud = 9600; //if Baud rate 9600 didn't work in your case then use 4800
TinyGPSPlus gps; // The TinyGPS++ object
WidgetMap myMap(V0);  // V0 for virtual pin of Map Widget
SoftwareSerial ss(RXPin, TXPin);  // The serial connection to the GPS device
BlynkTimer timer;
float spd;       //Variable  to store the speed
float sats;      //Variable to store no. of satellites response
String bearing;  //Variable to store orientation or direction of GPS
char auth[] = "OgcfkTT8MiG9wAYwyGm3ZP8t7FIpzOUT";              //Your Project authentication key
char ssid[] = "kawsar4698";                                       // Name of your network (HotSpot or Router name)
char pass[] = "kawsar4698";                                      // Corresponding Password
//unsigned int move_index;         // moving index, to be used later
unsigned int move_index = 1;       // fixed location for now
void setup()
{
  Serial.begin(115200);

pinMode(S1,INPUT);
pinMode (SMOKE,INPUT);
pinMode(FLAME,INPUT);
  
  Serial.println();
  ss.begin(GPSBaud);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(5000L, checkGPS); // every 5s check if GPS is connected, only really needs to be done once
  lcd.begin();
  lcd.backlight();
}

void checkGPS(){
  if (gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
      Blynk.virtualWrite(V4, "GPS ERROR");  // Value Display widget  on V4 if GPS not detected
  }
}

void loop()
{
lcd.setCursor(0, 0); 
  lcd.print("Have A Nice Day");
  delay(1000);;
  lcd.clear();
   Switch = digitalRead(S1);
    smoke = digitalRead(SMOKE);
   flame = digitalRead(FLAME);
   
Serial.print(Switch);
Serial.print("   Switch  ");
Serial.print(smoke);

Serial.print("     Smoke     ");
Serial.print(flame);
Serial.print("  Flame  ");
Serial.println("");

if (Switch == 0)
  {
    
     Blynk.notify("Warning!!! Accdient Occour in your car!!!");

lcd.setCursor(0, 1);     
  lcd.print(" Please Exit ");
  delay(2000);
    lcd.clear();
    }


    
if (smoke == 0)
  {
    
     Blynk.notify("Warning !!!! Smoke in your car!!");
    lcd.setCursor(0, 1); 
  lcd.print(" Please Exit ");
  delay(2000);
  lcd.clear();
    }


    
if (flame == 0)
  {
    
     Blynk.notify("Warning!!!  fire in your car!!");
    lcd.setCursor(0, 1); 
  lcd.print(" Please Exit ");
  delay(2000);
  lcd.clear();
    }
    while (ss.available() > 0) 
    {
      // sketch displays information every time a new sentence is correctly encoded.
      if (gps.encode(ss.read()))
        displayInfo();
  }
  Blynk.run();
  timer.run();
}

void displayInfo()
{ 
  if (gps.location.isValid() ) 
  {    
    float latitude = (gps.location.lat());     //Storing the Lat. and Lon. 
    float longitude = (gps.location.lng()); 
    
    Serial.print("LAT:  ");
    Serial.println(latitude, 6);  // float to x decimal places
    Serial.print("LONG: ");
    Serial.println(longitude, 6);
    Blynk.virtualWrite(V1, String(latitude, 6));   
    Blynk.virtualWrite(V2, String(longitude, 6));  
    myMap.location(move_index, latitude, longitude, "GPS_Location");
    spd = gps.speed.kmph();               //get speed
       Blynk.virtualWrite(V3, spd);
       
       sats = gps.satellites.value();    //get number of satellites
     Blynk.virtualWrite(V4, sats);

       bearing = TinyGPSPlus::cardinal(gps.course.value()); // get the direction
       Blynk.virtualWrite(V5, bearing);                   
  }
  
 Serial.println();
}
