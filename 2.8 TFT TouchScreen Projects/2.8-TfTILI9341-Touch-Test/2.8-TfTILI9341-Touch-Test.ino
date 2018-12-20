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

#define CS_PIN  0
#define TFT_DC  4
#define TFT_CS   5
// MOSI=11, MISO=12, SCK=13

XPT2046_Touchscreen ts(CS_PIN);
#define TIRQ_PIN  2
//XPT2046_Touchscreen ts(CS_PIN);  // Param 2 - NULL - No interrupts
//XPT2046_Touchscreen ts(CS_PIN, 255);  // Param 2 - 255 - No interrupts
//XPT2046_Touchscreen ts(CS_PIN, TIRQ_PIN);  // Param 2 - Touch IRQ Pin - interrupt enabled polling

//ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
void setup() {
  Serial.begin(38400);
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);
  ts.begin();
  while (!Serial && (millis() <= 1000));
}

boolean wastouched = true;

void loop() {
  boolean istouched = ts.touched();
  if (istouched) {
    TS_Point p = ts.getPoint();
    if (!wastouched) {
      tft.fillScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_YELLOW);
   //   tft.setFont(Arial_60);
      tft.setCursor(60, 80);
      tft.print("Touch");
    }
    tft.fillRect(100, 150, 140, 60, ILI9341_BLACK);
    tft.setTextColor(ILI9341_GREEN);
//    tft.setFont(Arial_24);
    tft.setCursor(100, 150);
    tft.print("X = ");
    tft.print(p.x);
    tft.setCursor(100, 180);
    tft.print("Y = ");
    tft.print(p.y);
    Serial.print(", x = ");
    Serial.print(p.x);
    Serial.print(", y = ");
    Serial.println(p.y);
  } else {
    if (wastouched) {
      tft.fillScreen(ILI9341_BLACK);
      tft.setTextColor(ILI9341_RED);
//      tft.setFont(Arial_48);
      tft.setCursor(120, 50);
      tft.print("No");
      tft.setCursor(80, 120);
      tft.print("Touch");
    }
    Serial.println("no touch");
  }
  wastouched = istouched;
  delay(100);
}
