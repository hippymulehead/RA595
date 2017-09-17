#include <Arduino.h>
#include <RA595.h>

RA595 demoReg(10,11,12);
unsigned long counter = 0;

void setup() {
    demoReg.allOff();
    demoReg.setBit(0,1);
    demoReg.write();
    demoReg.setRandomReadPin(A6);
}

void loop() {
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
    demoReg.allOn();
    demoReg.write();
    delay(700);
    demoReg.allOff();
    demoReg.write();
    for(size_t i = 0; i < 100; i++) {
        demoReg.setRandomBit();
        demoReg.write();
        delay(100);
    }
    demoReg.allOff();
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
    demoReg.allOff();
    demoReg.setBit(0,1);
    demoReg.write();
}