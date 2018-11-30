/**** TR2019 LED Strip Tachometer Display ****/

// Honda CBR600rr redline: 12800 RPM

#include <FastLED.h>

#define NUM_LEDS 20
#define DATA_PIN 7
#define REDLINE 12800

CRGB leds[NUM_LEDS];

void setupTach() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
  }
}

void dispRpm(int rpm) {
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
