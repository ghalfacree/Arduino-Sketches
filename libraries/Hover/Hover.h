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


#ifndef _Hover_H
#define _Hover_H

#include "Arduino.h"


class Hover {
 public:
  Hover(uint8_t addr = 0x42);
  void begin(int ts, int mclr);
  void setRelease(int ts);
  boolean getStatus(int ts);
  byte getEvent(void);
  String getEventString(byte eventByte);

 private:
  uint8_t _i2caddr;
};




#endif