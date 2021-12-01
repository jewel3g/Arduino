#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "0tC_lE4BQPUSeuaVglcbfDsEY6KNOu-m";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Jewel";
char pass[] = "10101520";


// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3F, 20, 4);
const int sensor_pin = A0;  /* Connect Soil moisture analog sensor pin to A0 of NodeMCU */

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  lcd.begin();
Blynk.begin(auth, ssid, pass);

  // Turn on the blacklight and print a message.
  lcd.backlight();
//  lcd.print("Hello, world!");
  dht.begin();
}

void loop() {
Blynk.run();
 
   float moisture_percentage;

  moisture_percentage = ( 100.00 - ( (analogRead(sensor_pin)/1023.00) * 100.00 ) );

  Serial.print("Soil Moisture(in Percentage) = ");
  Serial.print(moisture_percentage);
  Serial.println("%");
float p; 
p =moisture_percentage + 0.10;
  lcd.setCursor(0,1);
lcd.print("Moisture:");
 lcd.setCursor(9,1);
lcd.print(p);
lcd.setCursor(14,1);
lcd.print("%");
lcd.setCursor(16,1);
lcd.print("[P]");
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

  lcd.setCursor(0,0);
lcd.print("Temperature:");
  lcd.setCursor(12,0);
lcd.print(t);
lcd.setCursor(17,0);
lcd.print("C");

  lcd.setCursor(0,2);
lcd.print("Humidity:");
lcd.setCursor(9,2);
lcd.print(h);
lcd.setCursor(14,2);
lcd.print("%");
lcd.setCursor(0,3);
lcd.print("CO level is good ");
delay(10);

}
