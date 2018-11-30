/****************************************************************************

Original source: https://github.com/coryjfowler/MCP_CAN_lib/blob/master/examples/CAN_receive/CAN_receive.ino

Modified by Charlie Dawson to get engine RPM and wheel speed from PE3 ECU

**TR2019 Version**
 
*************************************************************************/

#include <mcp_can.h>
#include <SPI.h>
#include "TachControl.h"
#include "sevenSegment.h"

long unsigned int rxId;

#define RPM_ID 0x0CFFF048           // PE3 Engine RPM CAN Message ID
#define WHEEL_SPEED_ID 0x0CFFFF48   // PE3 Wheel RPM CAN Message ID

unsigned char len = 0;
unsigned char rxBuf[8];             // CAN message (8 bytes)
char msgString[128];                // Array to store serial string

#define CAN0_INT 2                  // Set INT to pin 2
MCP_CAN CAN0(10);                   // Set CS to pin 10

int engineRpm = 0;
int wheelRpm = 0;
int currentGear = 0;

const double RATIO_ERROR = 0;       // May needed to be used to account for small errors in gear calculations


struct GEAR_RATIOS {
  const double GEAR_1 = 23.2222;
  const double GEAR_2 = 16.8889;
  const double GEAR_3 = 14.0741;
  const double GEAR_4 = 12.1975;
  const double GEAR_5 = 11.0145;
  const double GEAR_6 = 10.2037;
};

GEAR_RATIOS gears;


void setup()
{
  Serial.begin(115200);

  setupDisplay(); // Initialize LED pins, found in "sevenSegment.h"
  setupTach(); // Initialize tachometer but leave all LEDs off
  
  // Initialize MCP2515 running at 8MHz with a baudrate of 250kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("MCP2515 Initialized Successfully!");
  else
    Serial.println("Error Initializing MCP2515...");
  
  CAN0.setMode(MCP_NORMAL); // Set operation mode to normal so the MCP2515 sends acks to received data.

  pinMode(CAN0_INT, INPUT); // Configuring pin for /INT input
  
  Serial.println("MCP2515-PE3 Arduino Interface...");
  delay(1000);
}

void loop()
{
  if(!digitalRead(CAN0_INT))                         // If CAN0_INT pin is low, read receive buffer
  {
    CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
    
    if ((rxId & 0x1FFFFFFF) == RPM_ID) {
      engineRpm = getRpm(rxBuf);
      Serial.print("RPM is: "); Serial.println(engineRpm);
    }

    if ((rxId & 0x1FFFFFFF) == WHEEL_SPEED_ID) {
      wheelRpm = getRpm(rxBuf);
      Serial.print("Wheel speed is: "); Serial.println(wheelRpm);
    }

    currentGear = getGear(engineRpm, wheelRpm);
    setDisplay(currentGear); // sevenSegment.h
    dispRpm(engineRpm);      // TachControl.h
    
    Serial.print("Current gear is: "); Serial.println(currentGear);
    
    
    Serial.println();
  }
}

// Engine RPM is sent via bytes 1 and 2 of message 0x0CFF048
// Wheel  RPM is sent via bytes 1 and 2 of message 0x0CFFF48
//
// See http://pe-ltd.com/assets/an400_can_protocol_b.pdf for details

int getRpm(byte message[]){
  byte lowByte = message[0];
  byte highByte = message[1];

  unsigned int rpm = 256 * highByte + lowByte;

  return rpm;
}

// Uses engine RPM, wheel RPM, and known gear ratios to calculate
// the current gear.
//
// Returns the current gear as an integer

int getGear(int engineRpm, int wheelRpm){
  if (engineRpm == 0){
    return -1; // Engine not running
  }

  if (wheelRpm == 0) {
    return 0; // Neutral, prevent divide by 0
  }
  
  double ratio = (double) engineRpm / (double) wheelRpm;

  if (abs(ratio - gears.GEAR_1) <= RATIO_ERROR){
    return 1;
  }

  else if (abs(ratio - gears.GEAR_2) <= RATIO_ERROR){
    return 2;
  }

  else if (abs(ratio - gears.GEAR_3) <= RATIO_ERROR){
    return 3;
  }

  else if (abs(ratio - gears.GEAR_4) <= RATIO_ERROR){
    return 4;
  }

  else if (abs(ratio - gears.GEAR_5) <= RATIO_ERROR){
    return 5;
  }

  else if (abs(ratio - gears.GEAR_6) <= RATIO_ERROR){
    return 6;
  }

  return 0; // Will happen if engine on and car is moving but in neutral
}
