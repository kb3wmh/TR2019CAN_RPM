CRGB leds[NUM_LEDS];

#include <FastLED.h>

#define NUM_LEDS 20 // 20 LEDs currently a part of the light strip
#define DATA_PIN 7 // Output pin on Arduino connected to LED display

void setupTach() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  // Initialize leds to 0 (off)
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
  }
}
