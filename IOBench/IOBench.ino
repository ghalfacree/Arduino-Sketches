/*  IOBench - a simple benchmark for Arduinos and compatibles.
 *  Written by Gareth Halfacree <freelance@halfacree.co.uk>
 *  
 *  Principle: perform digitalRead and digitalWrite operations
 *  to measure the relative performance of Arduino MCUs and
 *  compatible devices.
 *  
 *  The read benchmark begins by measuring the time, in
 *  microseconds, it takes to complete a large loop.
 *  The loop is then repeated with a digitalRead operation,
 *  and the elapsed time in microseconds minus the time taken
 *  by the incrementing of the variable is printed to the
 *  serial port. The benchmark does not require anything to be
 *  connected to Pin 8.
 *  
 *  The write benchmark is split into two sections: soft and hard.
 *  The soft write benchmark requires no extra hardware, and
 *  works the same way as the read benchmark; the hard write
 *  benchmark loops forever and requires a frequency counter or
 *  oscilloscope connected to Pin 7 to measure the performance.
 *  The hard benchmark performs two digitalWrites, one high
 *  and one low, to toggle the pin; this will give a different
 *  result than the single-write soft benchmark. When comparing
 *  boards, always compare soft-to-soft and hard-to-hard; never
 *  compare soft-to-hard or vice-versa.
 *  
 *  NOTE: IOBench is not about getting the best performance out
 *  of a given microcontroller; there are much more efficient
 *  ways to read and write than digitalRead and digitalWrite.
 *  It simply offers a way to quickly compare the relative
 *  performance of different microcontrollers when using the two
 *  most common methods of controlling pins.
 */

char versionNumber[ ] = "v1.1.3";
unsigned long numberOfIterations = 1000000; // Increase if the benchmarks complete too quickly
int writePin = 7; // Pin to use for write benchmarks
int readPin = 8; // Pin to use for read benchmarks
unsigned long timeBegan;
unsigned long loopTimeElapsed;
double timeElapsed;
int readResult;
unsigned long i = 0;

void setup() {
  pinMode(writePin, OUTPUT);
  pinMode(readPin, INPUT);
  delay(5000); // Gives us time to active the serial monitor
  Serial.begin(9600);
  Serial.println(F(""));
  Serial.print(F("IOBench for Arduino, "));
  Serial.println(versionNumber);
  Serial.println(F(""));
}

void loop() {
  Serial.println(F("Calibrating loop overhead..."));
  i = 0;
  timeBegan = micros();
  while(i < numberOfIterations) {
    i++;
  }
  loopTimeElapsed = (micros()-timeBegan); // Time taken to do nothing but increment a variable
  Serial.print(F("Loop overhead measured at "));
  Serial.print(loopTimeElapsed);
  Serial.println(F(" microseconds."));
  Serial.println(F(""));
  Serial.print(F("Beginning read benchmark on Pin "));
  Serial.print(readPin);
  Serial.println(F("..."));
  i = 0;
  timeBegan = micros();
  while(i < numberOfIterations) {
    readResult=digitalRead(readPin);
    i++;
  }
  timeElapsed = (micros()-timeBegan-loopTimeElapsed); // Time taken to read a pin
  Serial.print(F("Read performance: "));
  Serial.print((numberOfIterations/timeElapsed)*1000);
  Serial.println(F(" kHz."));
  Serial.println(F(""));
  Serial.print(F("Beginning soft write benchmark on Pin "));
  Serial.print(writePin);
  Serial.println(F("..."));
  i = 0;
  timeBegan = micros();
  while(i < numberOfIterations) {
    digitalWrite(writePin, HIGH);
    i++;
  }
  timeElapsed = (micros()-timeBegan-loopTimeElapsed); // Time taken to write a pin
  Serial.print(F("Write performance: "));
  Serial.print((numberOfIterations/timeElapsed)*1000);
  Serial.println(F(" kHz."));
  Serial.println(F(""));
  Serial.print(F("Beginning hard (toggle) write benchmark on Pin "));
  Serial.print(writePin);
  Serial.println(F("..."));
  Serial.println(F("Activate frequency counter now."));
  Serial.println(F("Reset Arduino to restart benchmarks."));
  while(1) { // Infinite loop; use a frequency counter to get a measurement of write performance
    digitalWrite(writePin, HIGH);
    digitalWrite(writePin, LOW); 
  }
}
