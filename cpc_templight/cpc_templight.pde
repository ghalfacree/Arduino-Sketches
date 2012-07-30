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
  heat = map(temperature, 10, 40, 0, 255);
  cold = map(temperature, 40, 10, 0, 255);
  byte tempColor[] = {heat, 0, cold};
  setColor(ledAnalogOne, tempColor);
  delay(1000);
}

void setColor(int* led, byte* color){
 for(int i = 0; i < 3; i++){
   analogWrite(led[i], 255 - color[i]); 
 }
}

float getVoltage(int pin){
 return (analogRead(pin) * .004882814);
}

