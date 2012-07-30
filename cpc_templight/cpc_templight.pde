int ledAnalogOne[] = {3, 5, 6};
int temperaturePin = 0;
int heat = 0;
int cold = 0;

const byte RED[] = {255, 0, 0}; 
const byte ORANGE[] = {83, 4, 0}; 
const byte YELLOW[] = {255, 255, 0}; 
const byte GREEN[] = {0, 255, 0}; 
const byte BLUE[] = {0, 0, 255}; 
const byte INDIGO[] = {4, 0, 19}; 
const byte VIOLET[] = {23, 0, 22}; 
const byte CYAN[] = {0, 255, 255}; 
const byte MAGENTA[] = {255, 0, 255}; 
const byte WHITE[] = {255, 255, 255}; 
const byte BLACK[] = {0, 0, 0}; 
const byte PINK[] = {158, 4, 79};

void setup(){
  Serial.begin(9600);
  for(int i = 0; i < 3; i++){
   pinMode(ledAnalogOne[i], OUTPUT);   //Set the three LED pins as outputs
  }
  setColor(ledAnalogOne, BLACK);       //Turn off led 1
}


void loop(){
  float temperature = getVoltage(temperaturePin);
  temperature = (temperature - .5) * 100;
  heat = map(temperature, 10, 40, 0, 255);
  cold = map(temperature, 40, 10, 0, 255);
  //Serial.println(temperature);
  //Serial.println(heat);
  //Serial.println(cold);
  byte tempColor[] = {heat, 0, cold};
  setColor(ledAnalogOne, tempColor);
  delay(1000);
 // fadeToColor(ledAnalogOne, GREEN, RED, 10);
 // fadeToColor(ledAnalogOne, RED, GREEN, 10);
}

/* Sets the color of the LED to any RGB Value
   led - (int array of three values defining the LEDs pins (led[0] = redPin, led[1] = greenPin, led[2] = bluePin))
   color - (byte array of three values defing an RGB color to display (color[0] = new Red value, color[1] = new Green value, color[2] = new Red value
*/
void setColor(int* led, byte* color){
 for(int i = 0; i < 3; i++){             //iterate through each of the three pins (red green blue)
   analogWrite(led[i], 255 - color[i]);  //set the analog output value of each pin to the input value (ie led[0] (red pin) to 255- color[0] (red input color)
                                         //we use 255 - the value because our RGB LED is common anode, this means a color is full on when we output analogWrite(pin, 0)
                                         //and off when we output analogWrite(pin, 255). 
 }
}

/* A version of setColor that takes a predefined color (neccesary to allow const int pre-defined colors */
void setColor(int* led, const byte* color){
 byte tempByte[] = {color[0], color[1], color[2]};
 setColor(led, tempByte);
}

/* Fades the LED from a start color to an end color at fadeSpeed
   led - (int array of three values defining the LEDs pins (led[0] = redPin, led[1] = greenPin, led[2] = bluePin))
   startCcolor - (byte array of three values defing the start RGB color (startColor[0] = start Red value, startColor[1] = start Green value, startColor[2] = start Red value
   endCcolor - (byte array of three values defing the finished RGB color (endColor[0] = end Red value, endColor[1] = end Green value, endColor[2] = end Red value
   fadeSpeed - this is the delay in milliseconds between steps, defines the speed of the fade
*/ 
void fadeToColor(int* led, byte* startColor, byte* endColor, int fadeSpeed){
  int changeRed = endColor[0] - startColor[0];                            //the difference in the two colors for the red channel
  int changeGreen = endColor[1] - startColor[1];                          //the difference in the two colors for the green channel 
  int changeBlue = endColor[2] - startColor[2];                           //the difference in the two colors for the blue channel
  int steps = max(abs(changeRed),max(abs(changeGreen), abs(changeBlue))); //make the number of change steps the maximum channel change
  
  for(int i = 0 ; i < steps; i++){                                        //iterate for the channel with the maximum change
   byte newRed = startColor[0] + (i * changeRed / steps);                 //the newRed intensity dependant on the start intensity and the change determined above
   byte newGreen = startColor[1] + (i * changeGreen / steps);             //the newGreen intensity
   byte newBlue = startColor[2] + (i * changeBlue / steps);               //the newBlue intensity
   byte newColor[] = {newRed, newGreen, newBlue};                         //Define an RGB color array for the new color
   setColor(led, newColor);                                               //Set the LED to the calculated value
   delay(fadeSpeed);                                                      //Delay fadeSpeed milliseconds before going on to the next color
  }
  setColor(led, endColor);                                                //The LED should be at the endColor but set to endColor to avoid rounding errors
}

/* A version of fadeToColor that takes predefined colors (neccesary to allow const int pre-defined colors */
void fadeToColor(int* led, const byte* startColor, const byte* endColor, int fadeSpeed){
  byte tempByte1[] = {startColor[0], startColor[1], startColor[2]};
   byte tempByte2[] = {endColor[0], endColor[1], endColor[2]};
   fadeToColor(led, tempByte1, tempByte2, fadeSpeed);
}

/*
 * getVoltage() - returns the voltage on the analog input defined by
 * pin
 */
float getVoltage(int pin){
 return (analogRead(pin) * .004882814); //converting from a 0 to 1024 digital range
                                        // to 0 to 5 volts (each 1 reading equals ~ 5 millivolts
}

