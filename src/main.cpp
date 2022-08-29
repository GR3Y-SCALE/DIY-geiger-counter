#include <Arduino.h>
#define LOG_PERIOD 5000
#define CONVERSIONFACTOR 0.008120 //Specific for each GM tube
#define NUM 3

volatile unsigned long counts; //variable for GM Tube events
unsigned long previousMillis; //variable for measuring time
unsigned long currentMillis;
unsigned long dose = 0;
unsigned long countsPerMinute;

unsigned long countArray[NUM];
int arrayIndex;

void impulse() { //calls on geiger event

counts++;

}

void initArray() {
    for (int i = 0; i < NUM; i++) {
        countArray[i] = 0;
    }
}

int arrayTotal() {
    int totalCounts = 0;
    for (int i = 0; i < NUM; i++) {
        totalCounts += countArray[i];
    }
    return totalCounts;
}

unsigned long ConvertToSieverts(long cpm = 0) {
    return cpm*CONVERSIONFACTOR;
}

int scale(int val) {
    return val*4;
}

void setup() { //setup

counts = 0;

Serial.begin(9600);

pinMode(2, INPUT);

attachInterrupt(digitalPinToInterrupt(2), impulse, FALLING); //define external interrupts

Serial.println("Start counter");

initArray();

arrayIndex = 0;

}

void loop() { //main cycle

currentMillis = millis();

if (currentMillis - previousMillis > LOG_PERIOD) {

    previousMillis = currentMillis;

    if (arrayIndex != 3) {
        countArray[arrayIndex] = counts;
        arrayIndex++;
    } else {
        arrayIndex = 0;
        countArray[arrayIndex] = counts;
    } 
    countsPerMinute = scale(arrayTotal());

    Serial.print("Counts Per Minute: "); Serial.print(countsPerMinute); Serial.print(" Seiverts: "); Serial.println(ConvertToSieverts(countsPerMinute)); Serial.print("index: "); Serial.println(counts);
    counts = 0;
}



}

