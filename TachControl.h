/**** TR2019 LED Strip Tachometer Display ****/

// Honda CBR600rr redline: 12800 RPM

#include <FastLED.h>
#include "LEDSetup.h"

#define REDLINE 12800

void dispRpm(int rpm) {
  // Display RPM as a percentage of the LED strip
  for (int i = 0; i < (rpm*NUM_LEDS/REDLINE); i++) {  
    if (i < 7) {
      // Green
      leds[i].g = 255;
    }
    
    else if (i < 12) {
      // Yellow
      leds[i].r = 255;
      leds[i].g = 255;
    }
    
    else {
      // Blue
      leds[i].b = 255;
    }  
  }

  // Turn off any LEDs above the current RPM.
  for (int i = (rpm*NUM_LEDS/REDLINE); i < NUM_LEDS; i++) {
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
  }
  
  FastLED.show();
}
