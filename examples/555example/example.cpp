#include <Arduino.h>
#include <RA595.h>

/*
Demo of the RA595 lib from Romans Audio
Show off some of the simple things that you can do with a shift register
using the lib.
The hardware is set up with an LED and a 220 off each output.  The rest of
the 595 is set up as you would expect.
*/

// Setup your object
// RA595(int latchPin, int clockPin, int dataPin);
RA595 demoReg(10,11,12);
// Make a counter
unsigned long counter = 0;

void setup() {
    // Set the 0 bit high
    demoReg.allOff();
    demoReg.setBit(0,1);
    demoReg.write();
    // Set A6 as the pin to read from for a random seed
    demoReg.setRandomReadPin(A6);
}

void loop() {
    for(int i = 0; i < 100; i++) {
        demoReg.wrapRight(1);
        demoReg.write();
        delay(100);
    }
    // wrapRight()
    for(int i = 0; i < 100; i++) {
        demoReg.wrapLeft(1);
        demoReg.write();
        delay(100);
    }
    for(int i = 0; i < 10; i++) {
        for(int x = 0; x < 7; x++) {
            demoReg.wrapRight(1);
            demoReg.write();
            delay(100);
        }
        for(int x = 0; x < 7; x++) {
            demoReg.wrapLeft(1);
            demoReg.write();
            delay(100);
        }
    }
    // allOn()
    demoReg.allOn();
    demoReg.write();
    delay(700);
    // allOff()
    demoReg.allOff();
    demoReg.write();
    // setRandomBit()
    for(size_t i = 0; i < 100; i++) {
        demoReg.setRandomBit();
        demoReg.write();
        delay(100);
    }
    demoReg.allOff();
    // setBit()
    demoReg.setBit(0,1);
    demoReg.setBit(2,1);
    demoReg.setBit(4,1);
    demoReg.setBit(6,1);
    demoReg.write();
    for(int i = 0; i < 100; i++) {
        demoReg.wrapRight(1);
        demoReg.write();
        delay(100);
    }
    for(int i = 0; i < 100; i++) {
        demoReg.wrapLeft(1);
        demoReg.write();
        delay(100);
    }
    // Reset for the loop to start over
    demoReg.allOff();
    demoReg.setBit(0,1);
    demoReg.write();
}
