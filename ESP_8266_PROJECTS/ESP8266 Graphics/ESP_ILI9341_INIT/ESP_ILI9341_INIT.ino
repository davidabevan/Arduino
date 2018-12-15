#include <Arduino.h>
#include <Adafruit_ILI9341.h>

//Wiring Diagram
//****************************************************
//                                   LCD_PIN
//TFT LCD Pin VCC                 *1
//TFT LCD Pin GND                 *2
//TFT LCD Pin CS  to GPIO_5       *3
//TFT LCD Pin RST to RST          *4
//TFT LCD Pin DC to GPIO_2        *5
//TFT LCD Pin MOSI to GPIO_13     *6
//TFT LCD Pin CLK to GPIO_14      *7
//TFT LCD Pin LED to +3.3 V.      *8
//TFT LCD Pin MISO ( not use )    *9
//****************************************************
// For the Adafruit shield, these are the default.
#define TFT_DC 2
#define TFT_CS 5

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

#define SERIAL_OUT Serial
void setup() {
  SERIAL_OUT.begin(9600);
  SERIAL_OUT.println("ILI9341 Test!");
  tft.begin  ();
   tft.setRotation(3);
   tft.fillScreen(ILI9341_BLACK);
   tft.setCursor(0, 0);
  tft.setTextColor(ILI9341_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
}
  void loop(void) {
 // for(uint8_t rotation=0; rotation<4; rotation++) {
   
  
  
  }

