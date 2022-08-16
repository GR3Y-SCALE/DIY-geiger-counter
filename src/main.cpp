#include <Arduino.h>
#define LOG_PERIOD 5000

volatile unsigned long counts; //variable for GM Tube events
unsigned long previousMillis; //variable for measuring time
unsigned long currentMillis;
volatile unsigned long totalCounts;



void impulse() { //calls on geiger event

counts++;
totalCounts++;

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

Serial.print("Counts :"); Serial.print(counts); Serial.print(" Total Counts : "); Serial.println(totalCounts);

counts = 0;

}

}