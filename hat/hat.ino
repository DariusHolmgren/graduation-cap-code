#include <Adafruit_NeoPixel.h>
#include "hsv2rgb.h"

#define PIN            1
#define NUMPIXELS      5

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; // delay for half a second

void setup() {
  pixels.begin();
}

void loop() {
  hsv chsv = {random(0, 360), random(50, 100) / 100.0, random(50, 100) / 100.0};
  rgb crgb = hsv2rgb(chsv);
  uint32_t cColor = pixels.Color(crgb.r * 255, crgb.g * 255, crgb.b * 255);
  
  delayval -= 20;
  if(delayval == 40)
    delayval = 300;
  
  for(int i=0;i<NUMPIXELS;i++){
    pixels.setPixelColor(i, cColor);
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  for(int i=NUMPIXELS-2;i>0;i--){
    pixels.setPixelColor(i, cColor);
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
}
