/*
Weather Monitor sketch for Arduino microcontrollers.
Written by Gareth Halfacree for Computeractive.
Requires the DHT library: http://playground.arduino.cc/Main/DHTLib
Requires the BMP085 library: https://github.com/adafruit/Adafruit-BMP085-Library
*/

#include "Wire.h"
#include "dht.h"
#include "Adafruit_BMP085.h"

Adafruit_BMP085 BMP;
dht DHT;
#define DHT22_PIN A3

void setup()
{
  Serial.begin(9600);
  BMP.begin();
  pinMode(DHT22_PIN, INPUT);
  digitalWrite(DHT22_PIN, HIGH);  
  Serial.println("Weather Monitor Data");
  Serial.println();
  Serial.println("Temperature,Relative Humidity,Pressure");
}

void loop()
{
  Serial.print(((DHT.temperature)+(BMP.readTemperature()))/2, 1);
  Serial.print(",");
  Serial.print(DHT.humidity, 1);
  Serial.print(",");
  Serial.println(BMP.readPressure());
  delay(5000);
}
