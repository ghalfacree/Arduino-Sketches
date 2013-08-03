/*
Weather Monitor sketch for Arduino microcontrollers.
Written by Gareth Halfacree for Computeractive.
Requires the DHT library: http://playground.arduino.cc/Main/DHTLib
Requires the BMP085 library: https://github.com/adafruit/Adafruit-BMP085-Library
*/

#include "Wire.h"
#include "dht.h"
#include "Adafruit_BMP085.h"
#include "TM1638.h"

Adafruit_BMP085 BMP;
dht DHT;
#define DHT22_PIN A3
unsigned int temp=0;

void setup()
{
  Serial.begin(9600);
  BMP.begin();
  pinMode(DHT22_PIN, INPUT);
  digitalWrite(DHT22_PIN, HIGH);  
  Serial.println("Weather Monitor Data");
  Serial.println();
  Serial.println("Temperature,Pressure");
}

void loop()
{
  TM1638 module(8, 9, 10);
  Serial.print(BMP.readTemperature());
  temp=(BMP.readTemperature());
  module.setDisplayToDecNumber(temp, 0, false);
  Serial.print(",");
  Serial.println(BMP.readPressure());
  delay(5000);
}
