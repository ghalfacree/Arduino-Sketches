/*
   Custom Macro Keyboard
   Requires Arduino Leonardo or compatible
   Written by Gareth Halfacree, http://freelance.halfacree.co.uk
   Based on work by Tom Igoe, http://arduino.cc/en/Tutorial/KeyboardButton
   Parts list:
       4x momentary push-buttons: http://www.oomlout.co.uk/pushbuttons-x5-p-196.html
       Jumper wires: http://www.oomlout.co.uk/breadboard-jumper-wires-70-pieces-p-181.html
       Breadboard (optional): http://www.oomlout.co.uk/breadboard-400-point-p-180.html
   Written for PC Pro Magazine, January 2013
*/

// Definitions
const int button1Pin = 2; // Change pin numbers here, if required
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 5;

// Initial button states
int previousButton1State = HIGH;
int previousButton2State = HIGH;
int previousButton3State = HIGH;
int previousButton4State = HIGH;

// Set up the sketch - this only runs once per power-on
void setup() {
  pinMode(button1Pin, INPUT_PULLUP); // All button pins are inputs
  pinMode(button2Pin, INPUT_PULLUP); // 'PULLUP' tells the Arduino to use its internal pull-up resistors
  pinMode(button3Pin, INPUT_PULLUP); // This means there's no need to wire in external resistors
  pinMode(button4Pin, INPUT_PULLUP);
  Keyboard.begin(); // Sets the Arduino up in keyboard (USB HID) emulation mode
}

// Program loop - this runs continuously so long as the Arduino is kept powered on
void loop() {
  int button1State = digitalRead(button1Pin); // Check the status of the first button
  if ((button1State != previousButton1State) && (button1State == LOW)) {
    // This code runs once each time the button is pressed
    // In this example, the keys Left-GUI ('Windows key' or 'Super') and D are held for 250 milliseconds,
    // displaying the desktop on a Windows machine
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('d');
    delay(250);
    Keyboard.releaseAll();
  }
  previousButton1State = button1State;
  
  int button2State = digitalRead(button2Pin); // Check the status of the second button
  if ((button2State != previousButton2State) && (button2State == LOW)) {
    // This code runs once each time the button is pressed
    // In this example, a two-line message is typed out
    Keyboard.println("Visit the PC Pro website:");
    Keyboard.println("http://www.pcpro.co.uk");
  }
  previousButton2State = button2State;
  
  int button3State = digitalRead(button3Pin); // Check the status of the third button
  if ((button3State != previousButton3State) && (button3State == LOW)) {
    // This code runs once each time the button is pressed
    // In this example, a complex password is typed without the enter key being pressed
    Keyboard.print("5F5B9*0Pl#nsgBLYKn8O9XwB&*xo$0g6");
  }
  previousButton3State = button3State;
  
  int button4State = digitalRead(button4Pin); // Check the status of the fourth button
  if ((button4State != previousButton4State) && (button4State == LOW)) {
    // This code runs once each time the button is pressed
    // In this example, the player's coordinates in the game World of Warcraft are displayed
    // Based on the 'Useful Macro' page at: http://www.wowwiki.com/Useful_macros
    Keyboard.println("/run px,py=GetPlayerMapPosition(\"player\"); DEFAULT_CHAT_FRAME:AddMessage(format(\"You are at location: %s (%0.1f, %0.1f)\",GetZoneText(),px*100,py*100));");
  }
  previousButton4State = button4State;
}
