/*
Weather Monitor sketch for Arduino microcontrollers.
Written by Gareth Halfacree for Computeractive.
Requires the DHT library: http://playground.arduino.cc/Main/DHTLib
Requires the BMP085 library: https://github.com/adafruit/Adafruit-BMP085-Library
*/

#include "dht.h"
#include "Wire.h"
#include "Adafruit_BMP085.h"

Adafruit_BMP085 bmp;

dht DHT;
#define DHT22_PIN A3

void setup()
{
  Serial.begin(9600);
  bmp.begin();
  pinMode(DHT22_PIN, INPUT);
  digitalWrite(DHT22_PIN, HIGH);  
  Serial.println("Weather Monitor Data");
  Serial.println();
  Serial.println("Temperature,Relative Humidity,Pressure");
}

void loop()
{

  int chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
                break;
    case DHTLIB_ERROR_CHECKSUM:
                Serial.print("Checksum error,\t");
                break;
    case DHTLIB_ERROR_TIMEOUT:
                Serial.print("Time out error,\t");
                break;
    default:
                Serial.print("Unknown error,\t");
                break;
  }
  
  Serial.print(((DHT.temperature)+(bmp.readTemperature()))/2, 1);
  Serial.print(",");
  Serial.print(DHT.humidity, 1);
  Serial.print(",");
  Serial.println(bmp.readPressure());
  delay(5000);
}
