/*  ===========================================================================
#  This is the library for Hover. 
#  
#  Hover is a development kit that lets you control your hardware projects in a whole new way.  
#  Wave goodbye to physical buttons. Hover detects hand movements in the air for touch-less interaction.  
#  It also features five touch-sensitive regions for even more options.
#  Hover uses I2C and 2 digital pins. It is compatible with Arduino, Raspberry Pi and more.
#
#  Hover can be purchased here: http://www.justhover.com
#
#  Written by Emran Mahbub and Jonathan Li for Gearseven Studios.  
#  BSD license, all text above must be included in any redistribution
#  ===========================================================================
#
#  INSTALLATION
#  The 3 library files (Hover.cpp, Hover.h and keywords.txt) in the Hover folder should be placed in your Arduino Library folder.
#  Run the HoverDemo.ino file from your Arduino IDE.
#
#  SUPPORT
#  For questions and comments, email us at support@gearseven.com
#  v2.1
#  ===========================================================================*/

#include <Hover.h>
#include <Wire.h>

#ifdef __AVR__
 #define WIRE Wire
#endif

Hover::Hover(uint8_t addr) {
  _i2caddr = addr;
}

void Hover::begin(int ts, int rst) {
	WIRE.begin();
	pinMode(ts, INPUT);    //Used by TS line on MGC3130
	pinMode(rst, OUTPUT);    //Used by TS line on MGC3130
	digitalWrite(rst, LOW);
	pinMode(rst, INPUT);    
	delay(3000);
	Serial.println("Hover is ready");
}

void Hover::setRelease(int ts) {
    digitalWrite(ts, HIGH);
    pinMode(ts, INPUT);
}

boolean Hover::getStatus(int ts) {
	if (digitalRead(ts) == 0) {
		pinMode(ts, OUTPUT);
		digitalWrite(ts, LOW);
		return 0;
	}	
	return 1;
}

byte Hover::getEvent(void) {
	byte data;
	byte event;
	int c = 0;
    WIRE.requestFrom((uint8_t)_i2caddr, (uint8_t)18);    // request 20 bytes from slave device at 0x42
    while(WIRE.available())    // slave may send less than requested
    {     
		data = WIRE.read(); // receive a byte as character
		if (c == 10 && data > 1) {
			event = (B00000001 << (data-1)) | B00100000;
			return event;
		}
		if (c == 14 && data > B11111) {
			event = ((data & B11100000) >> 5) | B01000000 ;
			return event;
		}
		if (c == 15 && data > 0) {
			event = (((data & B0011) << 3) | B01000000);
			return event;
		}
        c++;
    }
}

String Hover::getEventString(byte eventByte) {

	//Serial.println("inside string fcn");
	//return "Test";
	//Serial.println(eventByte);
    if (eventByte == B00100010) {
        //Serial.println("Right swipe");
		return "Right Swipe";
    } else if (eventByte == B00100100) {
        //Serial.println("Left swipe"); 
		return "Left Swipe";

    } else if (eventByte == B00101000) {
        //Serial.println("Up swipe");  
		return "Up Swipe";
		
    } else if (eventByte == B00110000) {
        //Serial.println("Down swipe"); 
		return "Down Swipe";
		
    } else if (eventByte == B01000001) {
        //Serial.println("Tap south");
		return "Tap South";
		
    } else if (eventByte == B01000010) {
        //Serial.println("Tap West");
		return "Tap West";
		
    } else if (eventByte == B01010000) {
        //Serial.println("Tap Center");
		return "Tap Center";
		
    } else if (eventByte == B01001000) {
        //Serial.println("Tap East"); 
		return "Tap East";
		
    } else if (eventByte == B01000100) {
        //Serial.println("Tap NORTH");     
		return "Tap North";
		
    } 
	return "";
}
