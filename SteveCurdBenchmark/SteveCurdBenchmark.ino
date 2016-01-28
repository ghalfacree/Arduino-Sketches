//
// Pi_2
//
// Steve Curd
// December 2012
//
// This program approximates pi utilizing the Newton's approximation.  It quickly
// converges on the first 5-6 digits of precision, but converges verrrry slowly
// after that.  For example, it takes over a million iterations to get to 7-8
// significant digits.
//
// For demonstration purposes, drives a JY-LKM1638 display module to show the
// approximated value after each 1,000 iterations, and toggles the pin13 LED for a
// visual "sign of life".
//
// I wrote this to evaluate the performance difference between the 8-bit Arduino Mega,
// and the 32-bit Arduino Due.
// 
// Benchmark results for 100,000 iterations (pi accurate to 5 significant digits):
//   Mega: 6249 ms
//   Due: 821 ms (Due is about 7.5x faster)
//
// 1638 display module connections:
// VCC -> 3.3v
// GND -> GND
// DIO -> Pin 8
// CLK -> Pin 9
// STB0 -> Pin 7
//
//

#define ITERATIONS 100000L    // number of iterations
#define FLASH 1000            // blink LED every 1000 iterations

#include <TM1638.h>           // include the display library

// TM1638 module(DIO, CLK, STB0)
TM1638 module(8, 9, 7);

void setup() {
 pinMode(13, OUTPUT);        // set the LED up to blink every 1000 iterations
 Serial.begin(9600);
}

void loop() {
 
 unsigned long start, time;
 unsigned long niter=ITERATIONS;
 int LEDcounter = 0;
 boolean alternate = false;
 unsigned long i, count=0;
 float x = 1.0;
 float temp, pi=1.0;


 Serial.print("Beginning ");
 Serial.print(niter);
 Serial.println(" iterations...");
 Serial.println();
 
 start = millis();  
 for ( i = 2; i < niter; i++) {
   x *= -1.0;
   pi += x / (2.0f*(float)i-1.0f);
   if (LEDcounter++ > FLASH) {
     LEDcounter = 0;
     if (alternate) {
       digitalWrite(13, HIGH);
       alternate = false;
     } else {
       digitalWrite(13, LOW);
       alternate = true;
     }
     temp = 40000000.0 * pi;
     module.setDisplayToDecNumber( temp, 0x80);
   }
 }
 time = millis() - start;
 
 pi = pi * 4.0;

 Serial.print("# of trials = ");
 Serial.println(niter);
 Serial.print("Estimate of pi = ");
 Serial.println(pi, 10);
 
 Serial.print("Time: "); Serial.print(time); Serial.println(" ms");
 
 delay(10000);
}
