#include <Arduino.h>
#define LOG_PERIOD 5000 //miliseconds

unsigned long counts; //variable for GM Tube events
unsigned long previousMillis; //variable for measuring time
unsigned long currentMillis;
unsigned long totalCounts;



void impulse() { //calls on geiger event

counts++;

}


void setup() { //setup

counts = 0;

Serial.begin(9600);

pinMode(2, INPUT);

attachInterrupt(digitalPinToInterrupt(2), impulse, FALLING); //define external interrupts

Serial.println("Start counter");
totalCounts = 0;

}

void loop() { //main cycle

currentMillis = millis();

if (currentMillis - previousMillis > LOG_PERIOD) {

previousMillis = currentMillis;

totalCounts =+ counts;
Serial.print("Counts: "); Serial.print(counts); Serial.print(" Total Count: "); Serial.println(totalCounts);

counts = 0;

}

}