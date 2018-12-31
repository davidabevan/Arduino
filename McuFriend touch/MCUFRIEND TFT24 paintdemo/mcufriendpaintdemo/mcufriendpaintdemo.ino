// the regular Adafruit "TouchScreen.h" library only works on AVRs

// different mcufriend shields have Touchscreen on different pins
// and rotation.
// Run the UTouch_calibr_kbv sketch for calibration of your shield

//#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_TFTLCD.h> // Hardware-specific library
//Adafruit_TFTLCD tft(A3, A2, A1, A0, A4);
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>

#if defined(__SAM3X8E__)
#undef __FlashStringHelper::F(string_literal)
#define F(string_literal) string_literal
#endif


// These are the pins for some typical shields!
// S6D0154: YP=A1, XM=A2, YM=7, XP=6
// ST7783 : YP=A2, XM=A1, YM=6, XP=7
// ILI9320: YP=A2, XM=A3, YM=8, XP=9
// ILI9325: YP=A1, XM=A2, YM=7, XP=6
// ILI9325BG: YP=A2, XM=A1, YM=6, XP=7
// ILI9341: YP=A2, XM=A1, YM=7, XP=6
// ILI9488: YP=A1, XM=A2, YM=7, XP=6
// R65109V: YP=A2, XM=A1, YM=6, XP=7

// most mcufriend shields use these pins and Portrait mode:
uint8_t YP = A1;  // must be an analog pin, use "An" notation!
uint8_t XM = A2;  // must be an analog pin, use "An" notation!
uint8_t YM = 7;   // can be a digital pin
uint8_t XP = 6;   // can be a digital pin
uint8_t Landscape = 0;

uint16_t TS_LEFT = 920;
uint16_t TS_RT = 150;
uint16_t TS_TOP = 940;
uint16_t TS_BOT = 120;

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

int16_t BOXSIZE;
int16_t PENRADIUS = 3;
uint16_t oldcolor, currentcolor;

void setup(void)
{
    Serial.begin(9600);
    Serial.println(F("Paint_kbv !"));

    tft.reset();
    uint16_t identifier = tft.readID();
//    if (identifier == 0) identifier = 0x9341;
/*    if (0) {
    } else if (identifier == 0x0154) {
        Serial.println(F("Found S6D0154 LCD driver"));
        TS_LEFT = 914; TS_RT = 181; TS_TOP = 957; TS_BOT = 208;
    } else if (identifier == 0x7783) {
        Serial.println(F("Found ST7783 LCD driver"));
        TS_LEFT = 865; TS_RT = 155; TS_TOP = 942; TS_BOT = 153;
        Landscape = 1;
    } else if (identifier == 0x9320) {
        Serial.println(F("Found ILI9320 LCD driver"));
        YP = A3; XM = A2; YM = 9; XP = 8;
        TS_LEFT = 902; TS_RT = 137; TS_TOP = 941; TS_BOT = 134;
    } else if (identifier == 0x9325) {
        Serial.println(F("Found ILI9325 LCD driver"));
        TS_LEFT = 900; TS_RT = 103; TS_TOP = 96; TS_BOT = 904;
    } else if (identifier == 0x9341) {
        Serial.println(F("Found ILI9341 LCD driver BLUE"));
        TS_LEFT = 920; TS_RT = 139; TS_TOP = 944; TS_BOT = 150;
        Landscape = 0;
    } else if (identifier == 0) {
        Serial.println(F("Found ILI9341 LCD driver DealExtreme"));
        TS_LEFT = 893; TS_RT = 145; TS_TOP = 930; TS_BOT = 135;
        Landscape = 1;
    } else if (identifier == 0 || identifier == 0x9341) {
        Serial.println(F("Found ILI9341 LCD driver RED"));
        TS_LEFT = 128; TS_RT = 911; TS_TOP = 105; TS_BOT = 908;
        Landscape = 1;
    } else if (identifier == 0x9488) {
        Serial.println(F("Found ILI9488 LCD driver"));
        TS_LEFT = 904; TS_RT = 170; TS_TOP = 950; TS_BOT = 158;
    } else if (identifier == 0xB509) {
        Serial.println(F("Found R61509V LCD driver"));
        TS_LEFT = 889; TS_RT = 149; TS_TOP = 106; TS_BOT = 975;
        Landscape = 1;
    } else {
        Serial.print(F("Unknown LCD driver chip: "));
        Serial.println(identifier, HEX);
        return;
    } */ 
    ts = TouchScreen(XP, YP, XM, YM, 300);     //call the constructor AGAIN with new values.
    tft.begin(identifier);
    BOXSIZE = tft.width() / 6;
    tft.fillScreen(BLACK);

    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);

    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
    currentcolor = RED;
    delay(1000);
}

#define MINPRESSURE 10
#define MAXPRESSURE 1000

void loop()
{
    int tmp;
    TSPoint p = ts.getPoint();

    // if sharing pins, you'll need to fix the directions of the touchscreen pins
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    // we have some minimum pressure we consider 'valid'
    // pressure of 0 means no pressing!

    if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
        if (Landscape) {   // swap X and Y
            tmp = p.x;
            p.x = p.y;
            p.y = tmp;
        }
        // scale from 0->1023 to tft.width  i.e. left = 0, rt = width
        // most mcufriend have touch (with icons) that extends below the TFT 
        // screens without icons need to reserve a space for "erase"
        p.x = map(p.x, TS_LEFT, TS_RT, 0, tft.width());
        p.y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());

        if (p.y < BOXSIZE) {
            oldcolor = currentcolor;

            if (p.x < BOXSIZE) {
                currentcolor = RED;
                tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
            } else if (p.x < BOXSIZE * 2) {
                currentcolor = YELLOW;
                tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
            } else if (p.x < BOXSIZE * 3) {
                currentcolor = GREEN;
                tft.drawRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, WHITE);
            } else if (p.x < BOXSIZE * 4) {
                currentcolor = CYAN;
                tft.drawRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, WHITE);
            } else if (p.x < BOXSIZE * 5) {
                currentcolor = BLUE;
                tft.drawRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, WHITE);
            } else if (p.x < BOXSIZE * 6) {
                currentcolor = MAGENTA;
                tft.drawRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, WHITE);
            }

            if (oldcolor != currentcolor) {
                if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
                if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
                if (oldcolor == GREEN) tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
                if (oldcolor == CYAN) tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
                if (oldcolor == BLUE) tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
                if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);
            }
        }
        if (((p.y - PENRADIUS) > BOXSIZE) && ((p.y + PENRADIUS) < tft.height())) {
            tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
        }
        if (p.y > tft.height() - 10) {
            Serial.println("erase");
            // press the bottom of the screen to erase
            tft.fillRect(0, BOXSIZE, tft.width(), tft.height() - BOXSIZE, BLACK);
        }
    }
}
