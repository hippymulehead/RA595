#include <Arduino.h>
#include <RA595.h>

RA595::RA595(int latchPin, int clockPin, int dataPin) {
    m_shiftReg.setup(latchPin, clockPin, dataPin, LSBFIRST);
    m_reg = 0;
}

void RA595::allOff() {
    m_reg = 0;
}

void RA595::allOn() {
    m_reg = 255;
}

void RA595::setByte(byte byteToSet) {
    m_reg = byteToSet;
}

void RA595::setByteNow(byte byteToWrite) {
    m_reg = byteToWrite;
    write();
}

void RA595::write() {
    if (m_rotateAmt != 0) {
        m_treg = rotator(m_rotateAmt);
    } else {
        m_treg = m_reg;
    }
    m_shiftReg = m_treg;
    // m_latchOut = LOW;
    // uint8_t i;
	// for (i = 0; i < 8; i++)  {
    //     m_dataOut = !!(m_treg & (1 << i));
    //     m_clockOut = HIGH;
    //     m_clockOut = LOW;
	// }
    // m_latchOut = HIGH;
}

void RA595::setBit(int bitNumber, int value) {
    bitWrite(m_reg, bitNumber, value);
}

void RA595::setBitNow(int bitNumberToWrite, int value) {
    bitWrite(m_reg, bitNumberToWrite, value);
    write();
}

void RA595::setRandomReadPin(int pin) {
    m_rndPin = pin;
    pinMode(m_rndPin, INPUT);
}

void RA595::setRotateAmt(unsigned int rotateAmt) {
    m_rotateAmt = rotateAmt;
}

void RA595::setRandomBit() {
    m_reg = 0;
    bitWrite(m_reg, random(0, 8), 1);
}

byte RA595::getRegValue() {
    return m_reg;
}

void RA595::shiftLeft(unsigned int amt) {
    m_reg = m_reg << amt;
}

void RA595::shiftRight(unsigned int amt) {
    m_reg = m_reg >> amt;
}

void RA595::wrapLeft(unsigned int amt) {
    for (size_t i = 0; i < amt; i++) {
        int t = bitRead(m_reg, 0);
        m_reg = m_reg >> 1;
        bitWrite(m_reg, 7, t);
    }
}

void RA595::wrapRight(unsigned int amt) {
    for (size_t i = 0; i < amt; i++) {
        int t = bitRead(m_reg, 7);
        m_reg = m_reg << 1;
        bitWrite(m_reg, 0, t);
    }
}

void RA595::ssd(int digitToDisplay) {
    m_reg = m_ssdArray[digitToDisplay];
}
