#include "Adafruit_NeoPixel.h"
#include "hsv2rgb.h"

#define PIN            11
#define NUMPIXELS      100

////////////////////////////////////////////////////////////
#define RED     0xFF0000   // 0
#define ORANGE  0xCC3300   // 1
#define YELLOW  0xE77200   // 2
#define GREEN   0x00FF00   // 3
#define BLUE    0x0000FF   // 4
#define PURPLE  0x6600cc   // 5
#define WHITE   0xFFFFFF   // 6
#define PINK    0xED0A3F   // 7
#define CYAN    0x00FFFF   // 8
#define MAGENTA 0xCC00CC   // 9



const uint32_t COLORS[10] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, WHITE, PINK, CYAN, MAGENTA};
uint32_t var = 0;
////////////////////////////////////////////////////////////


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 300; // delay

void setup() {
  pixels.begin();
}

void loop() {
  //uint32_t cColor = randColor();

  for(int i = 0; i < 10; i++) {
    box(COLORS[i]);
    decrementDelay();
  }
  
  /*
  var++;
  switch(var % 4) {
    case 1: fade(10); break;
    case 2: box(); break;
    case 3: snake(random(1, 3) * 5); break;
    default: decrementDelay();
  }
  */
}

void vline(uint8_t line) {
  uint32_t cColor = randColor();
  bool even = true;
  
  for (int j = line; j < NUMPIXELS - line;) {
    if ((j % 10 == line) || (j % 10 == (9 - line))) {
      pixels.setPixelColor(j, cColor);
      if (even) {
        j+= (19 - (line*2) );
      }
      else {
        j+= 1 + line*2;
      }
      even = !even;
    }
    else
      j++;
  }
  swc();
    delay(500);
}

void box(uint32_t cColor) {
  for (int i = 0; i < 5; i++) {
    setSubstrip( 0 + i + (10 * i),  9 - i  + (10 * i), cColor); // top
    setSubstrip(90 + i - (10 * i), 99 - i  - (10 * i), cColor); // bottom
    
    for (int j = i * 10; j < NUMPIXELS - (i * 10); j++) {
      if (j % 10 == i || j % 10 == (9 - i)) {
        pixels.setPixelColor(j, cColor);
      }
    }
    swc();
  } 
}

void cross(uint32_t cColor) {
  for (int i = 0; i < sqrt(NUMPIXELS); i++) {
    for (int j = 0; j < NUMPIXELS - 1; j++)
      if ((j % 11) == 1)
        setSubstrip(j, j, cColor);
    swc();
  } 
}

void fade(uint32_t cColor, uint8_t x) {
  uint8_t b = 10;
  setSubstrip(0, NUMPIXELS, cColor);
  
  for (; b < 200; b++) {
    pixels.setBrightness(b);
    sw(x);
  }
  for (; b > 10; b--) {
    pixels.setBrightness(b);
    sw(x);
  }
  pixels.setBrightness(255);
  pixels.clear(); // This sends the updated pixel color to the hardware.
}

void snake(int n) {
  for(int i=0; i<NUMPIXELS / n; i++){
    uint32_t cColor = randColor();
    setSubstrip(i * n, i * n + n - 1, cColor);
    swc();
  }
  for(int i=(NUMPIXELS / n) - 2; i>0; i--){
    uint32_t cColor = randColor();
    setSubstrip(i * n, i * n + n-1, cColor);
    swc();
  }
}

uint32_t randColor() {
  hsv chsv = {random(0, 360), random(60, 100) / 100.0, random(60, 100) / 100.0}; 
  rgb crgb = hsv2rgb(chsv);
  return pixels.Color(crgb.r * 255, crgb.g * 255, crgb.b * 255);
}

void swc() {
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).
  pixels.clear(); // This sends the updated pixel color to the hardware.
}

void sw(uint8_t i) {
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval / i); // Delay for a period of time (in milliseconds).
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


void setSubstrip(int8_t start,  int end, uint32_t cColor) {
  for(int i = start; i <= end; i++) {
    pixels.setPixelColor(i, cColor);
  }
}

void mytch_hat(uint32_t cColor){ 
  while(delayval >= 11) {
    box(cColor);
    decrementDelay();
  }

  fade(cColor, 10);
  delayval = 300;

}

