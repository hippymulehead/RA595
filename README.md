# RA595

This is a simple OOP lib for Arduino and the 595 Shift Register.

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