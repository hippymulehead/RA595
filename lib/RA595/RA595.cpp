#include <Arduino.h>
#include <RA595.h>

RA595::RA595(int latchPin, int clockPin, int dataPin) {
    _latchPin = latchPin;
    _clockPin = clockPin;
    _dataPin = dataPin;
    pinMode(_latchPin, OUTPUT);
    pinMode(_clockPin, OUTPUT);
    pinMode(_dataPin, OUTPUT);
    _reg = 0;
}

void RA595::allOff() {
    _reg = 0;
}

void RA595::allOn() {
    _reg = 255;
}

void RA595::setByte(byte byteToSet) {
    _reg = byteToSet;
}

void RA595::setByteNow(byte byteToWrite) {
    _reg = byteToWrite;
    write();
}

void RA595::write() {
    if (_rotateAmt != 0) {
        _treg = rotator(_rotateAmt);
    } else {
        _treg = _reg;
    }
    digitalWrite(_latchPin, LOW);
    shiftOut(_dataPin, _clockPin, LSBFIRST, _treg);
    digitalWrite(_latchPin, HIGH);
}

void RA595::setBit(int bitNumber, int value) {
    bitWrite(_reg, bitNumber, value);
}

void RA595::setBitNow(int bitNumberToWrite, int value) {
    bitWrite(_reg, bitNumberToWrite, value);
    write();
}

void RA595::setRandomReadPin(int pin) {
    _rndPin = pin;
    pinMode(_rndPin, INPUT);
}

void RA595::setRotateAmt(unsigned int rotateAmt) {
    _rotateAmt = rotateAmt;
}

void RA595::setRandomBit() {
    _reg = 0;
    bitWrite(_reg, random(0, 8), 1);
}

byte RA595::getRegValue() {
    return _reg;
}

void RA595::shiftLeft(unsigned int amt) {
    _reg = _reg << amt;
}

void RA595::shiftRight(unsigned int amt) {
    _reg = _reg >> amt;
}

void RA595::wrapLeft(unsigned int amt) {
    for (size_t i = 0; i < amt; i++) {
        int t = bitRead(_reg, 0);
        _reg = _reg >> 1;
        bitWrite(_reg, 7, t);
    }
}

void RA595::wrapRight(unsigned int amt) {
    for (size_t i = 0; i < amt; i++) {
        int t = bitRead(_reg, 7);
        _reg = _reg << 1;
        bitWrite(_reg, 0, t);
    }
}

void RA595::ssd(int digitToDisplay) {
    _reg = _ssdArray[digitToDisplay];
}
