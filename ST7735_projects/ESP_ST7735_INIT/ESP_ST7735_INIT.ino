#include <Arduino.h>
//#include <Adafruit_ILI9341.h>
#  include <Adafruit_ST7735.h>
//Wiring Diagram ST7735 BREAKOUT BOARD TFT_LCD KMR 1.8 SPI
//****************************************************
//                                   LCD_PIN  Notes NODEMCU
//TFT LCD 01 to Pin GND                 *01   GND
//TFT LCD 02 to Pin VCC                 *02   VCC
//TFT LCD 06 to Pin RST to RST          *06
//TFT LCD 07 to Pin DC to GPIO_2        *07    A0     D4
//TFT LCD 08 to Pin MOSI to GPIO_13     *08    SDA    D7
//TFT LCD 09 to Pin CLK to GPIO_14      *09           D5
//TFT LCD 10 to Pin CS  to GPIO_5       *10           D1
//TFT LCD Pin MISO ( not use )    *12         NOT USED
//TFT LCD 15 to Pin LED to +3.3 V.      *15   LED VCC
//TFT LCD 16 TO GND                     *16     GND
//**********SD_READER_PINS******************************
//SD CS                           *14
//SD MISO                         *12
//SD MOSI                         *13
//SD SCK                          *11
//****************************************************
// For the Adafruit shield, these are the default.
#define TFT_DC 2
#define TFT_CS 5

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC);

#define SERIAL_OUT Serial
void setup() {
  SERIAL_OUT.begin(9600);
  SERIAL_OUT.println("ILI9341 Test!");
 // tft.begin  ();
 tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
   tft.setRotation(3);
   tft.fillScreen(ST7735_BLACK);
   tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE);  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_YELLOW); tft.setTextSize(2);
  tft.println(1234.56);
}
  void loop(void) {
 // for(uint8_t rotation=0; rotation<4; rotation++) {
   
  //}
  
  }

