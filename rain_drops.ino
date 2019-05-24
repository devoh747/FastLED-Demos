/* ======================================================================================
          Project: Arduino LED Light Box - Raindrop sketch
          Author: Scott C  (https://gist.github.com/ArduinoBasics/0d7f61cf711180d9e7f4b112bbece698)
          Created: 18th August 2015
            
          Modified by devoh747 5/24/2019 for FastLED 3.2.6 ( http://fastled.io/) running on Arduino 1.8.9
          Using an ItsyBitsy M4 (Pin 5 is 5v logic) with a strip of 60 WS2812 leds           
           
========================================================================================= */

#include "FastLED.h"            // This sketch uses the FastLED library                                    
 
#define DATA 5                  // Data connected to Digital Pin 5 on ItsyBitsy M4 (https://www.adafruit.com/product/3800)                                                              
#define LED_TYPE WS2812         // This LED strip uses the WS2812 chipset.                                   
#define NUM_LEDS 60             // There are 60 LEDs on this strand

//Global Variables
byte brightness[NUM_LEDS];      // The brightness of each LED is controlled individually through this array
byte hue[NUM_LEDS];             // The hue of each LED is controlled individually through this array
struct CRGB leds[NUM_LEDS];     // This is the array of LEDs    
byte startVal[NUM_LEDS];        // The startVal array helps to randomise the LED pattern
byte minHue =0;                 // Keeps the hue within a certain range - this is the lower limit
byte maxHue =30;                // Keeps the hue within a certain range - this is upper limit
byte maxBrightness = 150;       // Limits the brightness of the LEDs
 
    
/*===================================================================
  setup(): The following code is only run once
====================================================================*/

void setup() {
  //If you have a different LED strip, you may need to modify the next line
  //For this LED strand, you need to define only the data connection
  LEDS.addLeds<LED_TYPE, DATA, RGB>(leds, NUM_LEDS); 
  
  //Clear the LED strip
  FastLED.clear();
  
  //This helps to create a truly random pattern each time
  random16_add_entropy(random8());

  //Initialise the startVal and hue arrays
  for(int i = 0; i<NUM_LEDS; i++){
    startVal[i] = random8();
    hue[i] = random(minHue, maxHue);
  }
}


/*===================================================================
  loop(): The following code runs indefinitely
====================================================================*/

void loop() {
  
  //Cycle through each LED
  for(int i = 0; i<NUM_LEDS; i++){
    
    //The brightness of each LED is based on the startValue, 
    //and has a sinusoidal pattern
    startVal[i]++;
    brightness[i] = sin8(startVal[i]);
    
    //Set the hue and brightness of each LED
    leds[i] = CHSV(hue[i], 255, map(brightness[i],0,255,0,maxBrightness));
    
    //This helps to further randomise the pattern
    if(random(1000)<100){
      startVal[i] = startVal[i]+2;
    }
    
    //The hue will only change when the LED is "off"
    if(brightness[i] <3){
      //Randomise the hue for the next on off cycle
      hue[i] = random(minHue, maxHue); 
      
      //Each time an LED turns off, the hue "range" is incremented.
      //This allows the LEDs to transition through each colour of the rainbow
      minHue++;
      maxHue++;
    }
  }
  
  FastLED.show();           // Show the next frame of the LED pattern
  FastLED.delay(10);        // Slow down the animation slightly
} 
