# TR2019CAN_RPM

The software assumes you have the MCP_CAN library and the FastLED library (the versions I've used are included in this
repository so that if whatever hosting site they are on go down, the original libraries will still be available).

*The code is commented (You're welcome, future Terps Racing member/future me)*

## rpm_receive.ino
This is the main Arduino ino file. It is responsible for reading the CAN messages from the PE3 and converting them to 
usable RPM numbers.

## sevenSegment.h
Takes a number and displays it on a seven-segment display (currently only 0-6 and 8 since other digits are not needed). 
This code assumes a 74LS47 BCD controller connected to pins 3, 4, 5,and 6.

## TachControl.h
Displays the engine RPM on a 20-led RGB LED strip.
