#define RA595_h
#ifdef RA595_h
#include <Arduino.h>
#include <RAGPIO.h>

/*
(C) 2018 Mike Romans of Romans Audio
Object to manage a 595 shift register in a very Opp kinda way.
This uses the 595 as a display/gate device mainly.  I wrote this for
my Eurorack Arduino projects.  Outside of that, there may be some limitations.
You can set up two objects with only 4 pins by reusing the clock and latch pins.
RA595 reg1(10,11,12);
RA595 reg2(10,11,9);
Clock and latch don't need to be diffrent, just the data pin.

Features:
    all on, all off
    set register by byte
    set the register bit at a time
    writes are seperate from Sets
        (When the register is written it updates the whole byte at once
        This keeps the output in sync for timing perposes)
    a random function
    since the obect stores the value of the register you can get that value at any time.
    shiftLeft, shiftRight
    wrapLeft, wrapRight (a rotating shift)
    7 Segment Display driver in a single call.
*/

class RA595 {
    public:
        // Sets up the object and does all the grunt work
        RA595(int latchPin, int clockPin, int dataPin);
        // Turn off all pins
        void allOff();
        // Turn on all pins
        void allOn();
        // Send an entire byte
        void setByte(uint8_t byteToSet);
        // Send an entire byte and write it now.
        void setByteNow(uint8_t byteToWrite);
        // Set a single bit to a value
        void setBit(int bitNumber, int value);
        // Set a single bit to a value, includes a write
        void setBitNow(int bitNumberToWrite, int value);
        // Set what analog pin to pull random seeds from I use A6
        void setRandomReadPin(int pin);
        // Randomnly sets a single pin high
        void setRandomBit();
        // Sets the rotation value of the output.  0-8
        void setRotateAmt(unsigned int rotateAmt);
        // Returns a byte that contains the value of the reg without rotation
        uint8_t getRegValue();
        // Bitwise left shift
        void shiftLeft(unsigned int amt);
        // Bitwise right shift
        void shiftRight(unsigned int amt);
        // This rotates all bits left and what falls off the shift is added back on the other end;
        void wrapLeft(unsigned int amt);
        // This rotates all bits right and what falls off the shift is added back on the other end;
        void wrapRight(unsigned int amt);
        // Simple 7 Segment Display Driver.  0-15 displays Hex 0-F
        void ssd(int digitToDisplay);
        // Nothing above is written until you call this
        void write();

    protected:
        DigitalOut m_latchOut;
        DigitalOut m_clockOut;
        DigitalOut m_dataOut;
        uint8_t m_reg;
        int m_rndPin;
        unsigned int m_rotateAmt = 0;
        uint8_t m_treg = 0;
        int m_ssdArray[16] = {252, 96, 218, 242, 102, 182, 190, 224, 254, 246, 238, 62, 156, 122, 158, 142};

        byte rotator(unsigned int amt) {
            uint8_t m_t = m_reg;
            for (size_t x = 0; x < amt; x++) {
                int m_x = bitRead(m_t, 7);
                m_t = m_t << 1;
                bitWrite(m_t, 0, m_x);
            }
            return m_t;
        }
};
#endif
