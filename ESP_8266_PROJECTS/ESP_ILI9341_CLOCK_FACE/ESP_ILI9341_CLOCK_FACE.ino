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
   // Draw clock face______________________________________________________________________
  tft.fillCircle(120, 120, 118, ILI9341_GREEN);
  tft.fillCircle(120, 120, 110, ILI9341_BLACK);

  // Draw 12 lines
  for(int i = 0; i<360; i+= 30) {
int    sx = cos((i-90)*0.0174532925);
int    sy = sin((i-90)*0.0174532925);
int    x0 = sx*114+120;
   int y0 = sy*114+120;
   int x1 = sx*100+120;
   int y1 = sy*100+120;

    tft.drawLine(x0, y0, x1, y1, ILI9341_GREEN);
  }

  // Draw 60 dots
  for(int i = 0; i<360; i+= 6) {
int    sx = cos((i-90)*0.0174532925);
int    sy = sin((i-90)*0.0174532925);
int    x0 = sx*102+120;
   int y0 = sy*102+120;
    // Draw minute markers
    tft.drawPixel(x0, y0, ILI9341_WHITE);
    
    // Draw main quadrant dots
    if(i==0 || i==180) tft.fillCircle(x0, y0, 2, ILI9341_WHITE);
    if(i==90 || i==270) tft.fillCircle(x0, y0, 2, ILI9341_WHITE);
  }

  tft.fillCircle(120, 121, 3, ILI9341_WHITE);
}
//-----------------------------------------------------------

  void loop(void) {
 // for(uint8_t rotation=0; rotation<4; rotation++) {
   
  //}
  
  }

