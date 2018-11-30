/****Compatible with 74LS47 Display Contoller****/

// Digital pins connected to the 74LS47 display controller
#define pinA 3
#define pinB 4
#define pinC 5
#define pinD 6

struct displayNumber {
  int pinAState;
  int pinBState;
  int pinCState;
  int pinDState;
};

displayNumber one;
displayNumber two;
displayNumber three;
displayNumber four;
displayNumber five;
displayNumber six;
displayNumber zero;
displayNumber eight;

void setupDisplay() {
  // Setup each of the structs for the given numbers
  one.pinAState = HIGH;
  one.pinBState = LOW;
  one.pinCState = LOW;
  one.pinDState = LOW;

  two.pinAState = LOW;
  two.pinBState = HIGH;
  two.pinCState = LOW;
  two.pinDState = LOW;

  three.pinAState = HIGH;
  three.pinBState = HIGH;
  three.pinCState = LOW;
  three.pinDState = LOW;

  four.pinAState = LOW;
  four.pinBState = LOW;
  four.pinCState = HIGH;
  four.pinCState = LOW;

  five.pinAState = HIGH;
  five.pinBState = LOW;
  five.pinCState = HIGH;
  five.pinDState = LOW;

  six.pinAState = LOW;
  six.pinBState = HIGH;
  six.pinCState = HIGH;
  six.pinDState = LOW;

  zero.pinAState = LOW;
  zero.pinBState = LOW;
  zero.pinCState = LOW;
  zero.pinDState = LOW;

  eight.pinAState = LOW;
  eight.pinBState = LOW;
  eight.pinCState = LOW;
  eight.pinDState = HIGH;

  // Set the output pins for the tach
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
}

void setDisplay(int gear) {
  displayNumber displayGear;
  switch (gear) {
  case -1:
    displayGear = eight;
    break;
  case 0:
    displayGear = zero;
    break;
  case 1:
    displayGear = one;
    break;
  case 2:
    displayGear = two;
    break;
  case 3:
    displayGear = three;
    break;
  case 4:
    displayGear = four;
    break;
  case 5:
    displayGear = five;
    break;
  case 6:
    displayGear = six;
    break;
  }

  digitalWrite(pinA, displayGear.pinAState);
  digitalWrite(pinB, displayGear.pinBState);
  digitalWrite(pinC, displayGear.pinCState);
  digitalWrite(pinD, displayGear.pinDState);
}
