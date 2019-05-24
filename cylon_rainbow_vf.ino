// Modfied https://github.com/FastLED/FastLED/blob/master/examples/Cylon/Cylon.ino
// to be a rainbow with a "Thanos" tail


#include <FastLED.h>


// Neopixels
#define LED_TYPE WS2812

// How many leds in your strip?
#define NUM_LEDS 60 

//ItsyBitsy M4 pin 5
#define DATA_PIN 5


// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() { 
  //Serial.begin(57600);
  //Serial.println("resetting");
  LEDS.addLeds<LED_TYPE,DATA_PIN,RGB>(leds,NUM_LEDS);
  //LEDS.setBrightness(10);
}

void fadeall() { 
  for(int i = 0; i < NUM_LEDS; i++) { 
    leds[i].nscale8(random8(200, 257));
    } 
}

void loop() { 
  static uint8_t hue = 0;
  //Serial.print("x");
  // First slide the led in one direction
  for(int i = 0; i < NUM_LEDS; i++) {
    // Set the i'th led to the next color in the rainbow 
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show(); 
    // now that we've shown the leds, fade them all by a random number
    fadeall();
    // Wait a little bit before we loop around and do it again
    FastLED.delay(25);
  }
  //Serial.print("x");

  // Now go in the other direction.  
  for(int i = (NUM_LEDS)-1; i >= 0; i--) {
    // Set the i'th led to the next color in the rainbow
    leds[i] = CHSV(hue++, 255, 255);
    // Show the leds
    FastLED.show();
    // now that we've shown the leds, fade them all by a random number
    fadeall();
    // Wait a little bit before we loop around and do it again
    FastLED.delay(25);
  }
}
