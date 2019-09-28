// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
// Used for software SPI
#define LIS3DH_CLK A5
#define LIS3DH_MISO A4
#define LIS3DH_MOSI A3
// Used for hardware & software SPI
#define LIS3DH_CS A2

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int red = 10;
int green = 9;
int blue = 7;

void setup(void) {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif

  Serial.begin(9600);
  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  lcd.begin(16, 2);
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");
}

void loop() {
  lis.read();      // get X Y and Z data at once
  // Then print out the raw data
  Serial.print("X:  "); Serial.print(lis.x); 
  Serial.print("  \tY:  "); Serial.print(lis.y); 
  Serial.print("  \tZ:  "); Serial.print(lis.z); 

  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event; 
  lis.getEvent(&event);
  
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
  Serial.print(" \tY: "); Serial.print(event.acceleration.y); 
  Serial.print(" \tZ: "); Serial.print(event.acceleration.z); 
  Serial.println(" m/s^2 ");

  if(abs(lis.x) > abs(lis.y) && abs(lis.x) > abs(lis.z)) {

    analogWrite(red,255);
    analogWrite(blue,0);
    analogWrite(green,0);
    
   }

   if(abs(lis.y) > abs(lis.x) && abs(lis.y) > abs(lis.z)) {

    analogWrite(red,0);
    analogWrite(blue,255);
    analogWrite(green,0);
    
   }

   if(abs(lis.z) > abs(lis.x) && abs(lis.z) > abs(lis.y)) {

    analogWrite(red,0);
    analogWrite(blue,255);
    analogWrite(green,255);
    
   }

   lcd.clear();
   lcd.print("x,y,z: " + String(lis.x) + String(lis.y) + String(lis.z));

  Serial.println();
 
  delay(200); 
}
