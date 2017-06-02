#include <Adafruit_NeoPixel.h>
#include "hsv2rgb.h"

#define PIN            1
#define NUMPIXELS      100

////////////////////////////////////////////////////////////
#define RED    0xFF3855   // 0
#define ORANGE 0xFA5B3D   // 1
#define YELLOW 0xFFF700   // 2
#define GREEN  0xA7F432   // 3
#define BLUE   0x0048BA   // 4
#define PURPLE 0x5946B2   // 5
#define WHITE  0xFFFFFF   // 6

const uint32_t COLORS[7] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, WHITE};

////////////////////////////////////////////////////////////


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500; // delay for half a second

void setup() {
  pixels.begin();
}

void loop() {

  // this works
  uint32_t i = 0;
  setSubstrip(&pixels, 0, 9, COLORS[i]);
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).
  pixels.clear();

  i++;
  setSubstrip(&pixels, 0, 9, COLORS[i]);
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).
  pixels.clear();

  i++;
  setSubstrip(&pixels, 0, 9, COLORS[i]);
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).
  pixels.clear();

  /*
  // this does not work
  for(uint32_t i = 0; i<3; i++) {
    setSubstrip(&pixels, 0, 9, COLORS[i]);
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval); // Delay for a period of time (in milliseconds).
    pixels.clear();
  }
  */


  /*
  decrementDelay();
  int x = random(1, 4);
  if (x == 1)
    snake(random(1, 10));
  else if (x == 2)
    line();
  else if (x == 3)
    fade();
   */
}

void fade() {
  uint32_t cColor = randColor();
  setSubstrip(&pixels, 0, NUMPIXELS-1, cColor);
  swc();
  swc();
}

void line() {
  for(int i=0; i<NUMPIXELS / 10; i++){
    uint32_t cColor = randColor();
    setSubstrip(&pixels, i*10, i*10 + 9, cColor);
    swc();
  }
  for(int i=(NUMPIXELS / 10) - 2; i>0; i--){
    uint32_t cColor = randColor();
    setSubstrip(&pixels, i*10, i*10 + 9, cColor);
    swc();
  }
}

void snake(int n) {
  for(int i=0; i<NUMPIXELS / n; i++){
    uint32_t cColor = randColor();
    setSubstrip(&pixels, i * n, i * n + n - 1, cColor);
    swc();
  }
  for(int i=(NUMPIXELS / n) - 2; i>0; i--){
    uint32_t cColor = randColor();
    setSubstrip(&pixels, i * n, i * n + n-1, cColor);
    swc();
  }
}


uint32_t randColor() {
  hsv chsv = {random(0, 360), random(50, 100) / 100.0, random(50, 100) / 100.0};
  rgb crgb = hsv2rgb(chsv);
  return pixels.Color(crgb.r * 255, crgb.g * 255, crgb.b * 255);
}

void swc() {
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).
  pixels.clear();
}

void decrementDelay() {
  if (delayval > 200)
    delayval -= 40;
  
  if (delayval > 100)
    delayval -= 10;
  delayval -= 10;
  
  if(delayval == 0)
    delayval = 300;
}


void setSubstrip(Adafruit_NeoPixel *pixels, int8_t start,  int end, uint32_t cColor) {
  for(int i = start; i <= end; i++) {
    pixels->setPixelColor(i, cColor);
  }
}



