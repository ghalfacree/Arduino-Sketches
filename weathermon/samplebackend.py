# Simple Python back-end for weathermon.ino sketch
# Requires pySerial library: http://pyserial.sourceforge.net

import serial
ser = serial.Serial('/dev/ttyUSB0', 9600)
while 1:
    print ser.readline(),
