// Paint example specifically for the TFTLCD breakout board.
// DOES NOT CURRENTLY WORK ON ARDUINO LEONARDO
 
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
 
#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif
 
#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2 // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin
 
// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
 
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
// optional
#define LCD_RESET A4
 
// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define CYAN    0x07FF
#define WHITE   0xFFFF
 
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
 
#define PENRADIUS 3
#define MINPRESSURE 10
#define MAXPRESSURE 1000
 
int count = 0;
 
int TS_MINX = 500;
int TS_MINY = 500;
int TS_MAXX = 0;
int TS_MAXY = 0;
 
bool tft_y = false;
 
void setup(void) {
  Serial.begin(9600);
  Serial.println(F("TFT Calibration"));
 
  tft.reset();
 
  //The identifier is hardcoded as the library is unable to recognise the lcd chip
  //uint16_t identifier = 0x9341;
 
  tft.begin();
  tft.setRotation(0);
  pinMode(13, OUTPUT);
  tft.fillScreen(BLACK);
 
  //Splash
  tft.setRotation(1);
  tft.setCursor(30, (tft.height() / 2) - 20);
  tft.setTextSize(2);
  tft.println("TFT Calibration v1.0");
  tft.setCursor(30, tft.height() / 2);
  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.print("Screen size:");
  tft.print(tft.width());
  tft.print("x");
  tft.println(tft.height());
  tft.setCursor(30, (tft.height() / 2) + 20);
  tft.println("Test wil begin in 2s...");
  delay(2000);
  tft.fillScreen(BLACK);
  //TFT Calibration
  tft.setCursor(30, (tft.height() / 2) - 20);
  tft.setTextSize(2);
  tft.println("TFT Calibration");
  tft.setCursor(30, (tft.height() / 2));
  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.print("Click on screen to begin...");
  tft_y = true;
}
 
void drawCir(int prevX, int prevY, int x, int y) {
  tft.fillCircle(prevX, prevY, 15, BLACK);
  tft.fillCircle(x, y, 15, BLUE);
  tft.fillCircle(x, y, 7, CYAN);
}
 
void loop()
{
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  // if sharing pins, you'll need to fix the directions of the touchscreen pins
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
 
  if (tft_y) {
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
      debugPt(p);
      Serial.print("\tCount = "); Serial.println(count);
 
      switch (count) {
        case 0:
          tft.fillRect(30, (tft.height() / 2), 180, (tft.height() / 2) + 10, BLACK);
          tft.setCursor(30, (tft.height() / 2));
          tft.print("Press the dots on the corners of the screen.");
          drawCir(0, 0, 0, 0);
          getMinMax(p);
          count++;
          break;
        case 1:
          drawCir(0, 0, tft.width(), 0);
          getMinMax(p);
          count++;
          break;
        case 2:
          drawCir(tft.width(), 0, tft.width(), tft.height());
          getMinMax(p);
          count++;
          break;
        case 3:
          drawCir(tft.width(), tft.height(), 0, tft.height());
          getMinMax(p);
          count++;
          break;
        case 4:
          Serial.print("\nMin X = "); Serial.print(TS_MINX);
          Serial.print("Min Y = "); Serial.print(TS_MINY);
          drawCir(0, tft.height(), tft.width() + 16, tft.height() + 16);
          tft.fillRect(30, (tft.height() / 2), 300, (tft.height() / 2) + 10, BLACK);
          tft.setCursor(30, tft.height() / 2);
          tft.print("Calibration completed!");
          tft.setCursor(30, (tft.height() / 2) + 20);
          tft.print("Min X:");
          tft.print(TS_MINX);
          tft.setCursor(110, (tft.height() / 2) + 20);
          tft.print("Min Y:");
          tft.print(TS_MINY);
          tft.setCursor(30, (tft.height() / 2) + 30);
          tft.print("Max X:");
          tft.print(TS_MAXX);
          tft.setCursor(110, (tft.height() / 2) + 30);
          tft.print("Max Y:");
          tft.print(TS_MAXY);
          tft.setCursor(30, (tft.height() / 2) + 50);
          tft.print("Main Loop will comemence in 5s...");
          delay(5000);
          tft_y = false;
          break;
      }
      delay(200);
    }
  } else {
    tft.setRotation(0);
 
    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
      p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
      p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
      tft.fillCircle(p.x, p.y, PENRADIUS, BLUE);
    }
  }
}
 
void debugPt(TSPoint pt) {
  Serial.print("\nX = "); Serial.print(pt.x);
  Serial.print("\tY = "); Serial.print(pt.y);
  Serial.print("\tPressure = "); Serial.print(pt.z);
}
 
 
void getMinMax(TSPoint pt) {
  if (pt.x < TS_MINX) {
    TS_MINX = pt.x;
  }
  if (pt.y < TS_MINY) {
    TS_MINY = pt.y;
  }
  if (pt.x > TS_MAXX) {
    TS_MAXX = pt.x;
  }
  if (pt.y > TS_MAXY) {
    TS_MAXY = pt.y;
  }
}
 
void drawTestScreen() {
  tft.setCursor(tft.width() / 2, tft.height() / 2);
  tft.setTextSize(1);
  tft.setTextColor(WHITE);
  tft.print("Screen size:");
  tft.print(tft.width());
  tft.print("x");
  tft.println(tft.height());
 
  tft.println("Calibration");
  tft.println("-------------------");
  tft.println("Press on the dot to begin");
}
