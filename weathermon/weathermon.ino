/*
Weather Monitor sketch for Arduino microcontrollers.
Written by Gareth Halfacree for Computeractive.
Requires the DHT library: http://playground.arduino.cc/Main/DHTLib
Requires the BMP085 library: https://github.com/adafruit/Adafruit-BMP085-Library
*/

#include <dht.h>

dht DHT;
#define DHT22_PIN A3

void setup()
{
  Serial.begin(9600);
  pinMode(DHT22_PIN, INPUT);
  digitalWrite(DHT22_PIN, HIGH);  
  Serial.println("Weather Monitor");
  Serial.print("---------------");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void loop()
{
  // READ DATA
  Serial.print("DHT22, \t");
  int chk = DHT.read22(DHT22_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
                Serial.print("OK,\t");
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
  // DISPLAY DATA
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.println(DHT.temperature, 1);

  delay(5000);
}
//
// END OF FILE
//

