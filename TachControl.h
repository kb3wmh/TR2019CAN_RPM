/**** TR2019 LED Strip Tachometer Display ****/

// Honda CBR600rr redline: 12800 RPM

#include <FastLED.h>

#define NUM_LEDS 20 // 20 LEDs currently a part of the light strip
#define DATA_PIN 7 // Output pin on Arduino connected to LED display
#define REDLINE 12800

CRGB leds[NUM_LEDS];

void setupTach() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // Initialize leds to 0 (off)
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
  }
}

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
