// cpc-templight: a sketch for controlling an RGB LED via temperature.
// Contains code from Oomlout's RGB LED Analogue and Temperature Sensor examples.
// Written by Gareth Halfacree <gareth@halfacree.co.uk> for Custom PC Magazine Issue 110.

// Customisation Options
int upperTemp = 40 // Maximum (red) temperature in Celsius
int lowerTemp = 10 // Minimum (blue) temperature in Celsius

// Constants
int ledAnalogOne[] = {3, 5, 6};
int temperaturePin = 0;
int heat = 0;
int cold = 0;

void setup(){
  Serial.begin(9600);
  for(int i = 0; i < 3; i++){
   pinMode(ledAnalogOne[i], OUTPUT);
  }
}

void loop(){
  float temperature = getVoltage(temperaturePin);
  temperature = (temperature - .5) * 100;
  heat = map(temperature, lowerTemp, upperTemp, 0, 255);
  cold = map(temperature, lowerTemp, upperTemp, 255, 0);
  byte tempColour[] = {heat, 0, cold};
  setColour(ledAnalogOne, tempColour);
  delay(1000);
}

void setColour(int* led, byte* color){
 for(int i = 0; i < 3; i++){
   analogWrite(led[i], 255 - color[i]); 
 }
}

float getVoltage(int pin){
 return (analogRead(pin) * .004882814);
}

