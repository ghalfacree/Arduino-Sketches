/*  Ultrasonic sensor sketch for Spark Core/Particle Photon
    Designed to differentiate between a desk in sitting and standing modes
    Based on Jason Ch's Arduino Playground Sketch 'UltrasonicSensor'
    Copyleft Gareth Halfacree <gareth@halfacree.co.uk>
*/

// Variable setup
unsigned long echo = 0;             // Echo return timing variable
unsigned long ultrasoundValue = 0;  // Distance measured by sensor
int ultraSoundSignal = A0;          // Ultrasonic sensor signal pin
int distance = 0;                   // Distance measured by sensor in centimetres
int lastdistance = 0;               // Used for filtering sudden changes (i.e. measurement errors)
bool mode=0;                        // 0 (false) for sitting, 1 (true) for standing
bool lastmode=0;                    // Used for tracking mode changes
int matchcounter=0;                 // Used to avoid triggering on spurious readings

void setup()
{
    // There's actually nothing to do here
}

unsigned long ping() // Jason Ch's function for reading the ultrasonic sensor
{
    pinMode(ultraSoundSignal, OUTPUT);      // Switch signal pin to output
    digitalWrite(ultraSoundSignal, LOW);    // Send low pulse 
    delayMicroseconds(2);                   // Wait for 2 microseconds
    digitalWrite(ultraSoundSignal, HIGH);   // Send high pulse
    delayMicroseconds(5);                   // Wait for 5 microseconds
    digitalWrite(ultraSoundSignal, LOW);    // Holdoff
    pinMode(ultraSoundSignal, INPUT);       // Switch signalpin to input
    digitalWrite(ultraSoundSignal, HIGH);   // Turn on pullup resistor
    echo = pulseIn(ultraSoundSignal, HIGH); // Listen for echo
    ultrasoundValue = echo / 58.138;        // Convert to centimetres
    return ultrasoundValue;                 // Return the result to the main program
}

void loop()
{
    Spark.variable("distance", &distance, INT); // In case we want to read it manually
    lastdistance=distance;          // Track distance changes
    distance = ping();              // Update current distance using 'ping' function
    if (distance != lastdistance) { // If the distance has changed...
        delay(1200);                // Wait a bit...
        distance = ping();          // Then check again - filters out spurious readings
    }
    if (distance == lastdistance) { // If there's no change in distance since the last read...
        matchcounter++;             // Increment the counter for number of static readings
    }
    Spark.publish("Distance",String(distance),60,PRIVATE); // Send the current distance to Particle
    if (matchcounter > 2) {         // If we've had three or more stable readings...
        matchcounter = 0;           // Reset the match counter
        lastmode=mode;              // Track mode changes
        if (distance > 170) {       // If the ceiling is far away...
            mode=0;                 // Then the desk is in sitting mode
        }
        else if (distance < 160) {  // If the ceiling is close...
            mode=1;                 // Then the desk is in standing mode
        }
        if (mode != lastmode && !mode) { // Is there a new mode, and is it false?
            Spark.publish("Mode","sitting",60,PRIVATE); // Tell Particle that
        }
        else if (mode != lastmode && mode) { // Is there a new mode, and is it true?
            Spark.publish("Mode","standing",60,PRIVATE); // Tell Particle that
        }
    }
    delay(10000);                   // Take readings at ten second intervals continuously.
}
