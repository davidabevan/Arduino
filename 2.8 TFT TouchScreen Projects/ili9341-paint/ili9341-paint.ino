// Paint application - Demonstate both TFT and Touch Screen

/***************************************************
  This is our GFX example for the Adafruit ILI9341 Breakout and Shield
  ----> http://www.adafruit.com/products/1651

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

// Esp             TFT          i?o
// 5V              Vcc
// D1              Cs           GPIO5 SCL
// RST             RST
// D2              Dc           GPIO4 SDA
// D7              SDL/MOSI     GPIO13
// D5              SCK          GPIO14
// 3.3V            LED                  //*
 
 //Wiring Diagram
//****************************************************
//                             LCD_PIN    Wemos
//TFT LCD Pin VCC                 *1       5V
//TFT LCD Pin GND                 *2       GND
//TFT LCD Pin CS  to GPIO_5       *3       D1
//TFT LCD Pin RST to RST          *4       RST
//TFT LCD Pin DC to GPIO_4        *5       D2
//TFT LCD Pin MOSI to GPIO_13     *6       D7
//TFT LCD Pin CLK to GPIO_14      *7       D5
//TFT LCD Pin LED to +3.3 V.      *8       3.3V
//TFT LCD Pin MISO ( not use )    *9       D6
//^^^^^^TOUCH^^^^^^^^^^^^^^^^^^^^^^^^
// TFT LCD PIN T-CLK GPIO14      *10       D5
// TFT LCD PIN T-CS GPIO0        *11       D3
// TFT LCD PIN T-DIN GPIO13      *12       D7
// TFT LCD PIN T-DO GPIO12       *13       D6
// TFT LCD PIN T-IRQ GPIO2       *14       D4
//****************************************************
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

#define CS_PIN  0
// MOSI=11, MISO=12, SCK=13

//XPT2046_Touchscreen ts(CS_PIN);
#define TIRQ_PIN  2
//XPT2046_Touchscreen ts(CS_PIN);  // Param 2 - NULL - No interrupts
//XPT2046_Touchscreen ts(CS_PIN, 255);  // Param 2 - 255 - No interrupts
XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling
// For the Adafruit shield, these are the default.
#define TFT_DC 4
#define TFT_CS 5

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
// If using the breakout, change pins as desired
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#include <stdint.h>
//#include <SeeedTouchScreen.h>
//#include <TFTv2.h>
#include <SPI.h>

int ColorPaletteHigh = 30;
int color = ILI9341_WHITE;  //Paint brush color
unsigned int colors[8] = {ILI9341_BLACK, ILI9341_RED, ILI9341_GREEN, ILI9341_BLUE, ILI9341_CYAN, ILI9341_YELLOW, ILI9341_WHITE};

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// The 2.8" TFT Touch shield has 300 ohms across the X plate

//TouchScreen ts = TouchScreen(XP, YP, XM, YM); //init TouchScreen port pins

void setup() {
  //Tft.TFTinit();  //init TFT library
  tft.begin();
  Serial.begin(115200);
  //Draw the pallet
  for (int i = 0; i < 8; i++) {
   // tft.fillRectangle(i * 30, 0, 30, ColorPaletteHigh, colors[i]);
  }
}

void loop() {
  // a point object holds x y and z coordinates.
  Point p = ts.getPoint();

  //map the ADC value read to into pixel co-ordinates

  p.x = map(p.x, TS_MINX, TS_MAXX, 0, 240);
  p.y = map(p.y, TS_MINY, TS_MAXY, 0, 320);

  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!

  if (p.z > __PRESURE) {
    // Detect  paint brush color change
    if (p.y < ColorPaletteHigh + 2) {
      color = colors[p.x / 30];
    } else {
      tft.fillCircle(p.x, p.y, 2, color);
    }
  }
}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
