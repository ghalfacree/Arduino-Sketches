/* 
MOCP controller
 Based on the following by Tom Igoe: 
 http://www.arduino.cc/en/Tutorial/KeyboardButton
 */

const int buttonPin = 2;          // input pin for pushbuttons
const int button2Pin = 3;
const int button3Pin = 4;
const int button4Pin = 5;
const int groundPin = 6;
int previousButtonState = HIGH;   // for checking the state of a pushButton
int previousButton2State = HIGH;
int previousButton3State = HIGH;
int previousButton4State = HIGH;

void setup() {
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(button4Pin, INPUT_PULLUP);
  pinMode(groundPin, OUTPUT);
  digitalWrite(groundPin, LOW);
  // initialize control over the keyboard:
  Keyboard.begin();
}

void loop() {
  // read the first pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the button state has changed, 
  if ((buttonState != previousButtonState) 
    // and it's currently pressed:
  && (buttonState == LOW)) {
    // send pause command to mocp
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('p');
    delay(250);
    Keyboard.releaseAll();
  }
  // save the current button state for comparison next time:
  previousButtonState = buttonState;
  
  // read the second pushbutton:
  int button2State = digitalRead(button2Pin);
  // if the button state has changed, 
  if ((button2State != previousButton2State) 
    // and it's currently pressed:
  && (button2State == LOW)) {
    // Take a screenshot
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('s');
    delay(150);
    Keyboard.releaseAll();
  }
  // save the current button state for comparison next time:
  previousButton2State = button2State;
  
  // read the third pushbutton:
  int button3State = digitalRead(button3Pin);
  // if the button state has changed, 
  if ((button3State != previousButton3State) 
    // and it's currently pressed:
  && (button3State == LOW)) {
    // Take a screenshot of the active window
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('d');
    delay(150);
    Keyboard.releaseAll();
  }
  // save the current button state for comparison next time:
  previousButton3State = button3State;
  
  // read the fourth pushbutton:
  int button4State = digitalRead(button4Pin);
  // if the button state has changed, 
  if ((button4State != previousButton4State) 
    // and it's currently pressed:
  && (button4State == LOW)) {
    // Suspend
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_BACKSPACE);
    delay(150);
    Keyboard.releaseAll();
  }
  // save the current button state for comparison next time:
  previousButton4State = button4State;
}

