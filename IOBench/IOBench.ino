/*  IOBench - a simple benchmark for Arduinos and compatibles.
 *  Written by Gareth Halfacree <freelance@halfacree.co.uk>
 *  
 *  Principle: perform digitalRead and digitalWrite operations
 *  to measure the relative performance of Arduino MCUs and
 *  compatible devices.
 *  
 *  The read benchmark begins by measuring the time, in
 *  microseconds, it takes to complete a 100,000-strong loop.
 *  The loop is then repeated with a digitalRead operation,
 *  and the elapsed time in microseconds minus the time taken
 *  by the incrementing of the variable is printed to the
 *  serial port. The benchmark does not require anything to be
 *  connected to Pin 8.
 *  
 *  The write benchmark simply loops forever, turning a pin
 *  on and off continuously. To measure the performance, connect
 *  a frequency counter or oscilloscope to Pin 8.
 *  
 *  NOTE: IOBench is not about getting the best performance out
 *  of a given microcontroller; there are much more efficient
 *  ways to read and write than digitalRead and digitalWrite.
 *  It simply offers a way to quickly compare the relative
 *  performance of different microcontrollers when using the two
 *  most common methods of controlling pins.
 */

unsigned long timeBegan;
unsigned long loopTimeElapsed;
unsigned long readTimeElapsed;
int readResult;
unsigned long i = 0;

void setup() {
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
  Serial.begin(9600);
  Serial.println(F(""));
  Serial.println(F("IOBench for Arduino, v1.0.0"));
  Serial.println(F(""));
}

void loop() {
  Serial.println(F("Calibrating read benchmark on Pin 8..."));
  i=0;
  timeBegan = micros();
  while(i < 100000) {
    i++;
  }
  loopTimeElapsed = (micros()-timeBegan); // Time taken to do nothing but increment a variable
  Serial.println(F("Beginning read benchmark on Pin 8..."));
  i=0;
  timeBegan = micros();
  while(i < 100000) {
    readResult=digitalRead(8);
    i++;
  }
  readTimeElapsed=(micros()-timeBegan-loopTimeElapsed); // Time taken to read a pin then increment a variable
  Serial.print(F("Time elapsed for 100,000 read operations: "));
  Serial.print(readTimeElapsed);
  Serial.println(F(" microseconds."));
  Serial.println(F(""));
  Serial.println(F("Beginning write benchmark on Pin 7..."));
  Serial.println(F("Activate frequency counter now."));
  Serial.println(F("Reset Arduino to restart benchmarks."));
  while(1) { // Infinite loop; use a frequency counter to get a measurement of write performance
    digitalWrite(7, HIGH);
    digitalWrite(7, LOW); 
  }
}
