#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 14

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);

}

void loop() {
  // Some example procedures showing how to display to the pixels:
  colorWipe(matrix.Color(255, 0, 0), 20); // Red
  colorWipe(matrix.Color(0, 255, 0), 20); // Green
  colorWipe(matrix.Color(0, 0, 255), 20); // Blue
  // Send a theater pixel chase in...
  theaterChase(matrix.Color(127, 127, 127), 50); // White
  theaterChase(matrix.Color(127,   0,   0), 50); // Red
  theaterChase(matrix.Color(  0,   0, 127), 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<294; i++) {
      matrix.drawPixel(0, i, c);
      matrix.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<294; i++) {
      matrix.drawPixel(0, i, Wheel((i+j) & 255));
    }
    matrix.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< 294; i++) {
      matrix.drawPixel(0, i, Wheel(((i * 256 / 294) + j) & 255));
    }
    matrix.show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (int i=0; i < 294; i=i+3) {
        matrix.drawPixel(0, i+q, c);    //turn every third pixel on
      }
      matrix.show();
     
      delay(wait);
     
      for (int i=0; i < 294; i=i+3) {
        matrix.drawPixel(0, i+q, 0);        //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
        for (int i=0; i < 294; i=i+3) {
          matrix.drawPixel(0, i+q, Wheel( (i+j) % 255));    //turn every third pixel on
        }
        matrix.show();
       
        delay(wait);
       
        for (int i=0; i < 294; i=i+3) {
          matrix.drawPixel(0, i+q, 0);        //turn every third pixel off
        }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return matrix.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return matrix.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
   WheelPos -= 170;
   return matrix.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
