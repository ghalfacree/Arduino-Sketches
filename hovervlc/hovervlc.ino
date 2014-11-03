#include <Wire.h>
#include <Hover.h>

// Pin declarations for Hover
int ts = 5;
int reset = 6;

Hover hover = Hover();
byte event;
String output_string = "";

void setup() {
  Serial.begin(9600);
  delay(4000);
  Serial.println("Initializing Hover...please wait.");
  hover.begin(ts, reset);   
  Keyboard.begin();  
}
void loop(void) {
    // Check if Hover is ready to send gesture or touch events
  if (hover.getStatus(ts) == 0) {
    
    //Get the event over i2c and print it
    event = hover.getEvent();}
  if (event == B00100010) {
        Serial.println("Right-Swipe: Control + Right Arrow");
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_RIGHT_ARROW);
        delay(100);
        Keyboard.releaseAll();
    } else if (event == B00100100) {
        Serial.println("Left-Swipe: Control + Left Arrow");
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_ARROW);
        delay(100);
        Keyboard.releaseAll();
    } else if (event == B00101000) {
        Serial.println("Up-Swipe: Control + Up Arrow");
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_UP_ARROW);
        delay(100);
        Keyboard.releaseAll();      
    } else if (event == B00110000) {
        Serial.println("Down-Swipe: Control + Down Arrow");
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_DOWN_ARROW);
        delay(100);
        Keyboard.releaseAll();
    } else if (event == B01010000) {
        Serial.println("Centre-Tap: Space Bar");
        Keyboard.write(' ');
        delay(100);
    }
        hover.setRelease(ts);
}
