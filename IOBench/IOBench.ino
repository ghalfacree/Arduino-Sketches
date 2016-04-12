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
 *  The write benchmark is split into two sections: soft and hard.
 *  The soft write benchmark requires no extra hardware, and
 *  works the same way as the read benchmark; the hard write
 *  benchmark loops forever and requires a frequency counter or
 *  oscilloscope connected to Pin 7 to measure the performance.
 *  The hard benchmark performs two digitalWrites, one high
 *  and one low, to toggle the pin; as a result, you'll need to
 *  double the figure you read on the frequency counter to
 *  get a per-write performance reading.
 *  
 *  NOTE: IOBench is not about getting the best performance out
 *  of a given microcontroller; there are much more efficient
 *  ways to read and write than digitalRead and digitalWrite.
 *  It simply offers a way to quickly compare the relative
 *  performance of different microcontrollers when using the two
 *  most common methods of controlling pins.
 */

char versionNumber[ ]= "v1.1.0";
unsigned long numberOfIterations = 100000; // Increase if the benchmarks complete too quickly
unsigned long timeBegan;
unsigned long loopTimeElapsed;
double timeElapsed;
int readResult;
unsigned long i = 0;

void setup() {
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
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
  Serial.println(F("Beginning read benchmark on Pin 8..."));
  i = 0;
  timeBegan = micros();
  while(i < numberOfIterations) {
    readResult=digitalRead(8);
    i++;
  }
  timeElapsed = (micros()-timeBegan-loopTimeElapsed); // Time taken to read a pin then increment a variable
  Serial.print(F("Read performance: "));
  Serial.print((numberOfIterations/timeElapsed)*1000);
  Serial.println(F(" kHz."));
  Serial.println(F(""));
  Serial.println(F("Beginning soft write benchmark on Pin 7..."));
  i = 0;
  timeBegan = micros();
  while(i < numberOfIterations) {
    digitalWrite(7, HIGH);
    i++;
  }
  timeElapsed = (micros()-timeBegan-loopTimeElapsed);
  Serial.print(F("Write performance: "));
  Serial.print((numberOfIterations/timeElapsed)*1000);
  Serial.println(F(" kHz."));
  Serial.println(F(""));
  Serial.println(F("Beginning hard write benchmark on Pin 7..."));
  Serial.println(F("Activate frequency counter now."));
  Serial.println(F("NOTE: Double the reported frequency for per-digitalWrite result."));
  Serial.println(F("Reset Arduino to restart benchmarks."));
  while(1) { // Infinite loop; use a frequency counter to get a measurement of write performance
    digitalWrite(7, HIGH);
    digitalWrite(7, LOW); 
  }
}
