/*
VLC Gesture Control via Hover Board
Requires: Hover Board, Arduino Leonardo or compatible
Writteh by Gareth Halfacree <freelance@halfacree.co.uk>
Based on code for the Hover Board from http://hoverlabs.co
*/

// Include required header files
#include <Wire.h>
#include <Hover.h>

// Set TS and Reset pin definitions
int ts = 5;
int reset = 6;

// Set the Hover board up
Hover hover = Hover();
byte event;
String output_string = "";

// Setup portion - runs once
void setup() {
  Serial.begin(9600); // Start a serial session for debugging purposes
  delay(4000);
  Serial.println("Initializing Hover...please wait.");
  hover.begin(ts, reset); // Initialise the Hover board
  Keyboard.begin(); // Enable keyboard emulation
}

// Loop portion - runs continuously
void loop(void) {
  if (hover.getStatus(ts) == 0) { // Check for gesture
    event = hover.getEvent(); } //  Retrieve gesture event via I2C
  // Check event types and trigger actions on recognised gestures
  if (event == B00100010)
    {
    Serial.println("Right-Swipe: Control + Right Arrow"); // VLC shortcut for skip forward one minute
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(100);
    Keyboard.releaseAll();
    }
  else if (event == B00100100)
    {
    Serial.println("Left-Swipe: Control + Left Arrow"); // VLC shortcut for skip backward one minute
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ARROW);
    delay(100);
    Keyboard.releaseAll();
    }
  else if (event == B00101000)
    {
    Serial.println("Up-Swipe: Control + Up Arrow");  // VLC shortcut for volume up
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_UP_ARROW);
    delay(100);
    Keyboard.releaseAll();      
    }
  else if (event == B00110000)
    {
    Serial.println("Down-Swipe: Control + Down Arrow"); // VLC shortcut for volume down
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_DOWN_ARROW);
    delay(100);
    Keyboard.releaseAll();
    }
  else if (event == B01010000)
    {
    Serial.println("Centre-Tap: Space Bar"); // VLC shortcut for pause and play
    Keyboard.write(' ');
    delay(100);
    }
  hover.setRelease(ts); // Reset Hover board ready for next interation
}
