/*********************************************************************/
/* Sleepduino: an Arduino-based nightlight and white noise generator */
/*   Gareth Halfacree|gareth.halfacree.co.uk|gareth@halfacree.co.uk  */
/*                                                                   */
/* The Sleepduino is a sketch which combines Oomlout's demonstration */
/* sketch for RBG LEDs (Circ16) with John Honnibal's psuedo-random   */
/* bit-stream generator. The result: a device which provides suitable*/
/* lighting for a baby's nursery along with reassuring white noise to*/
/* help baby drift off to sleep and stay there for the duration. At  */
/* least, that's the theory. Fingers crossed that it works.          */
/*                                                                   */
/* Original RGB LED demo sketch: http://bit.ly/yFD3c8                */
/* Original PRBS generator code: http://bit.ly/Ay0NML                */
/*                                                                   */
/* Individual LED colours can be customised using the defined colours*/
/* written below. What works best depends on your room: white is     */
/* likely too bright, but yellow or red - or a combination - should  */
/* provide a decent nightlight-like glow.                            */
/*                                                                   */
/* Licensed under a CC-Attribution-NonCommercial-ShareAlike licence. */
/*        See original sketches for other licence details.           */
/*       http://creativecommons.org/licenses/by-nc-sa/3.0/           */
/*********************************************************************/

// Configure various pins
int ledDigitalOne[] = {9, 10, 11};
int ledDigitalTwo[] = {14, 15, 16};
int ledDigitalThree[] = {4, 5, 6};
const int speakerPin = 3;
const boolean ON = LOW;                  // Yeah, this confused me too.
const boolean OFF = HIGH;                // Common anode = backwards.
const int button1Pin = 7;
const int button2Pin = 8;
const int button3Pin = 12;
unsigned long int reg;
int button1State = 0;
int button2State = 0;
int button3State = 0;
int i = 0;
int ii = 0;
int iii = 0;

//Predefined Colours
const boolean RED[] = {ON, OFF, OFF};    
const boolean GREEN[] = {OFF, ON, OFF}; 
const boolean BLUE[] = {OFF, OFF, ON}; 
const boolean YELLOW[] = {ON, ON, OFF}; 
const boolean CYAN[] = {OFF, ON, ON}; 
const boolean MAGENTA[] = {ON, OFF, ON}; 
const boolean WHITE[] = {ON, ON, ON}; 
const boolean BLACK[] = {OFF, OFF, OFF}; 

// An Array that stores the predefined colours
const boolean* COLOURS[] = {RED, GREEN, BLUE, YELLOW, CYAN, MAGENTA, WHITE, BLACK};

void setup(){
  for(int i = 0; i < 3; i++){
   pinMode(ledDigitalOne[i], OUTPUT);
   pinMode(ledDigitalTwo[i], OUTPUT);
   pinMode(ledDigitalThree[i], OUTPUT);}
  pinMode(speakerPin, OUTPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  digitalWrite(button1Pin, HIGH);
  digitalWrite(button2Pin, HIGH);
  digitalWrite(button3Pin, HIGH);
  setColour(ledDigitalOne, BLACK);    //Set the colour of bottom LED
  setColour(ledDigitalTwo, BLACK);    //Set the colour of middle LED
  setColour(ledDigitalThree, BLACK);  //Set the colour of top LED
  reg = 0x55aa55aaL; //The seed for the bitstream. It can be anything except 0.
}

void loop(){ // This is where the white-noise generator does its stuff.
   generateNoise();
   button1State = digitalRead(button1Pin);
   if (button1State == LOW) {
     if (i < 8) {
        i++;}
     else {
        i = 0;}
     setColour(ledDigitalOne, COLOURS[i]);
     while (digitalRead(button1Pin) == LOW) {generateNoise();}}
   button2State = digitalRead(button2Pin);
   if (button2State == LOW) {
     if (ii < 8) {
        ii++;}
     else {
        ii = 0;}
     setColour(ledDigitalTwo, COLOURS[ii]);
     while (digitalRead(button2Pin) == LOW) {generateNoise();}}
   button3State = digitalRead(button3Pin);
   if (button3State == LOW) {
     if (iii < 8) {
        iii++;}
     else {
        iii = 0;}
     setColour(ledDigitalThree, COLOURS[iii]);
     while (digitalRead(button3Pin) == LOW) {generateNoise();}}
}

// The below code deals with turning our friendly colour names into outputs.
void setColour(int* led, boolean* colour){
 for(int i = 0; i < 3; i++){
   digitalWrite(led[i], colour[i]);
 }
}

void setColour(int* led, const boolean* colour){
  boolean tempColour[] = {colour[0], colour[1], colour[2]};
  setColour(led, tempColour);
}

void generateNoise(){
   unsigned long int newr;
   unsigned char lobit;
   unsigned char b31, b29, b25, b24;
   b31 = (reg & (1L << 31)) >> 31;
   b29 = (reg & (1L << 29)) >> 29;
   b25 = (reg & (1L << 25)) >> 25;
   b24 = (reg & (1L << 24)) >> 24;
   lobit = b31 ^ b29 ^ b25 ^ b24;
   newr = (reg << 1) | lobit;
   reg = newr;
   digitalWrite (speakerPin, reg & 1);
   delayMicroseconds (50);} // Changing this value changes the frequency.
