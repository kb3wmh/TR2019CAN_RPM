/**** TR2019 LED Strip Tachometer Display ****/

// Honda CBR600rr redline: 12800 RPM

#include <FastLED.h>
#include "math.h"

#define CHIPSET APA102
#define DATA_PIN 3 // Output pin on Arduino connected to LED display
#define CLOCK_PIN 4
#define NUM_LEDS 15 // 20 LEDs currently a part of the light strip


#define REDLINE 12800.0
#define BRIGHTNESS_WAVE 0.25
#define BRIGHTNESS 1.0

#define COLOR_SPEED 5

int rWave;
int gWave;
int bWave;

int rAddWave;
int gAddWave;
int bAddWave;

unsigned long time;

CRGB leds[NUM_LEDS];

void setupTach() {
  //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.addLeds<CHIPSET, DATA_PIN, CLOCK_PIN>(leds, NUM_LEDS);

  // Initialize leds to 0 (off)
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r = 0;
    leds[i].g = 0;
    leds[i].b = 0;
  }

  rWave = 254;
  gWave = 0;
  bWave = 0;

  rAddWave = COLOR_SPEED;
  gAddWave = 0;
  bAddWave = 0;
}

// Cycle through colors when car is off ( both to show that tach is working and for cool factor :) )
void rainbowWave() {
  for (int i = NUM_LEDS - 1; i >=1; i--) {
    leds[i].r = leds[i-1].r;
    leds[i].b = leds[i-1].b;
    leds[i].g = leds[i-1].g;
  }

  leds[0].r = rWave * BRIGHTNESS_WAVE;
  leds[0].g = gWave * BRIGHTNESS_WAVE;
  leds[0].b = bWave * BRIGHTNESS_WAVE;

  rWave += rAddWave;
  gWave += gAddWave;
  bWave += bAddWave;

  if (rWave >= 255) {
    rAddWave = (-1) * COLOR_SPEED;
    gAddWave = COLOR_SPEED;
    bAddWave = 0;
  }

  else if (gWave >= 255) {
    rAddWave = 0;
    gAddWave = (-1) * COLOR_SPEED;
    bAddWave = COLOR_SPEED;
  }

  else if (bWave >= 255) {
    rAddWave = COLOR_SPEED;
    gAddWave = 0;
    bAddWave = (-1) * COLOR_SPEED;
  }

  if ((leds[0].r + leds[0].g + leds[0].b) < (255 * BRIGHTNESS_WAVE * 0.5)) {
    rWave = 255 * BRIGHTNESS_WAVE;
  }

  FastLED.show();
  
}

void dispRpm(int rpm) {
  // Display RPM as a percentage of the LED strip
  if (millis() - time > 5) {
    if (rpm != 0) {
      Serial.println(rpm * NUM_LEDS/REDLINE);
      for (int i = 0; i < ((rpm/REDLINE)*NUM_LEDS); i++) {  
        if (i < 7) {
          // Green
          leds[i].g = 255 * BRIGHTNESS;
        }
        
        else if (i < 12) {
          // Yellow
          leds[i].r = 255 * BRIGHTNESS;
          leds[i].g = 255 * BRIGHTNESS;
        }
        
        else {
          // Blue
          leds[i].b = 255 * BRIGHTNESS;
        }  
      }
    
      // Turn off any LEDs above the current RPM.
      for (int i = ((rpm/REDLINE)*NUM_LEDS); i < NUM_LEDS; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
      }
      
      FastLED.show();
    }
  
    else { // if rpm is 0 RAINBOW WAVE TIME
      rainbowWave();
    }
  
    time = millis();
  }
}
