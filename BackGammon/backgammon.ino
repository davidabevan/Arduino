/////////////////////////////////////////////
//    2.8" TOUCH SCREEN Backgammon         //
//                                         //
//                rom3 09.2017             //
//                                         //
//                                         //
/////////////////////////////////////////////

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <URTouch.h>
#include <avr/pgmspace.h>
//#include "draw.h"

#define TFT_RST 8
#define TFT_DC 9
#define TFT_CS 10
#define TOUCH_ORIENTATION  LANDSCAPE

#define bg ILI9341_DARKGREEN
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
URTouch  myTouch(30, 28, 26, 24, 22);
Adafruit_GFX_Button buttons[4];

unsigned short int x, y; // position touch
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;
const long interval = 500;
char start[12] = {"Gamestart"};
char you[4] = {"YOU"};
char cpu[4] = {"CPU"};
char alone[5] = {"None"};
char human[5] = {"HvsH"};
char text;
int playeer[] = {ILI9341_LIGHTGREY, ILI9341_BLACK};
bool CPUplays;
bool player;
bool opponent;
bool state;
bool none;
bool humanOnly;
bool b, c;
bool doubleWhite;
bool doubleBlack;
int doubleGame;
int lopp;
int lop;
int dice1;
int dice2;
int dicee;
int pash;
int color;
int color2;
int barBlack;
int barWhite;
int lastBarWhite;
int lastBarBlack;
int WhiteOut;
int BlackOut;
int possible;
int possibleBar;
int movesToWinBlack;
int movesToWinWhite;
int wonBarWhite;
int wonBarBlack;
int oneBarWhite;
int oneBarBlack;
int bar[] = {6, 26, 46, 66, 86, 106, 195, 215, 235, 255, 275, 295, 295, 275, 255, 235, 215, 195, 106, 86, 66, 46, 26, 6};
int rowup[] = {6, 22, 38, 54, 70, 86};
int rowdown[] = {234, 218, 202, 186, 170, 154, 139};
int chip[2][24] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
int bartouch;
int bartouched;
int xx;
int yy;
uint32_t t;
uint32_t t2;
prog_uint8_t bar1[]PROGMEM = {
  0xff, 0xff,
  0xff, 0xff,
  0xff, 0xff,
  0x7f, 0xfe,
  0x7f, 0xfe,
  0x7f, 0xfe,
  0x7f, 0xfe,
  0x7f, 0xfe,
  0x7f, 0xfe,
  0x7f, 0xfe,
  0x7f, 0xfe,
  0x7f, 0xfe,
  0x7f, 0xfe,
  0x7f, 0xfc,
  0x7f, 0xfc,
  0x7f, 0xfc,
};
prog_uint8_t bar2[]PROGMEM = {
  0x3f, 0xfc,
  0x3f, 0xfc,
  0x3f, 0xfc,
  0x3f, 0xfc,
  0x3f, 0xfc,
  0x3f, 0xfc,
  0x3f, 0xfc,
  0x3f, 0xfc,
  0x3f, 0xfc,
  0x3f, 0xfc,
  0x3f, 0xfc,
  0x3f, 0xfc,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
};
prog_uint8_t bar3[]PROGMEM = {
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x0f, 0xf0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
};
prog_uint8_t bar4[]PROGMEM = {
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x07, 0xe0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
};
prog_uint8_t bar5[]PROGMEM = {
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
};
prog_uint8_t bar6[]PROGMEM = {
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x03, 0xc0,
  0x01, 0x80,
  0x01, 0x80,
  0x01, 0x80,
  0x01, 0x80,
  0x01, 0x80,
  0x01, 0x80,
  0x01, 0x80,
  0x01, 0x80,
  0x01, 0x80,
};
prog_uint8_t pice[]PROGMEM = {
  0x0, 0x0,
  0x7, 0xe0,
  0xf, 0xf0,
  0x3f, 0xfc,
  0x7f, 0xfe,
  0x7f, 0xfe,
  0xff, 0xff,
  0xff, 0xff,
  0xff, 0xff,
  0xff, 0xff,
  0x7f, 0xfe,
  0x7f, 0xfe,
  0x3f, 0xfc,
  0xf, 0xf0,
  0x7, 0xe0,
  0x0, 0x0,
};

PROGMEM const uint8_t *fullbar[] =
{
  bar1,
  bar2,
  bar3,
  bar4,
  bar5,
  bar6
};
prog_uchar buffer[48];

void setup() {
  pmc_enable_periph_clk(ID_TRNG);
  trng_enable(TRNG);
  myTouch.InitTouch();
  myTouch.setPrecision(PREC_HI);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9341_DARKGREEN);
  //Draw frame
  for (x = 0; x < 6; x++)
  {
    tft.drawRect(0 + x, 0 + x, 320 - 2 * x, 240 - 2 * x, ILI9341_MAROON);
  }
  //Print "Arduino" text
  tft.setCursor(80, 30);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setTextSize(4);
  tft.print("Arduino");
  //Print "Backgammon" Text
  tft.setCursor(40, 100);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(4);
  tft.print("Backgammon");
  //Create Red Button
  buttons[0].initButton(&tft, 160, 200, 200, 40, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE, start, 2);
  buttons[0].drawButton();
  b = 1;
  do {
    waitonetouch(&x, &y);
    if (buttons[0].contains(x, y))
      b = 0;
  } while (b > 0);
  tft.fillRect(6, 6, 309, 229, ILI9341_DARKGREEN);
  tft.fillRect(126, 0, 69, 239, ILI9341_MAROON);
}

void loop() {
  clear();
  drawGame();
  none = 0;
  humanOnly = 0;
  beginner();
  doubleGame = 1;
  doubleWhite = 0;
  doubleBlack = 0;
  barWhite = 0;
  barBlack = 0;
  WhiteOut = 0;
  BlackOut = 0;
  buttons[0].initButton(&tft, 144, 25, 29, 20, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE, "Roll", 1);
  buttons[0].drawButton();
  buttons[1].initButton(&tft, 176, 25, 29, 20, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE, "x2", 1);
  buttons[1].drawButton();
  buttons[2].initButton(&tft, 144, 50, 29, 20, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE, "Acc.", 1);
  buttons[2].drawButton();
  buttons[3].initButton(&tft, 176, 50, 29, 20, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE, "Den.", 1);
  buttons[3].drawButton();
  b = 1;

  do {
    player = 0;
    opponent = 1;
    lopp = 0;
    help();
    doubleHumanWhite();
    doublePlayerWhite();
    doubleCPUWhite();
    dice1 = realRandom();
    dice2 = realRandom();
    help();
    if (dice1 == dice2) {
      pash = dice1;
      lop = 4;
    } else lop = 2;
    do {
      possible = 0;
      possibleBar = 0;
      if ((lopp == 1) && (lop == 4)) dice1 = pash;
      if ((lopp == 3) && (lop == 4)) dice2 = pash;
      help();
      if ((chip[0][17] + chip[0][16] + chip[0][15] + chip[0][14] + chip[0][13] + chip[0][12] +
           chip[0][11] + chip[0][10] + chip[0][9] + chip[0][8] + chip[0][7] + chip[0][6] +
           chip[0][5] + chip[0][4] + chip[0][3] + chip[0][2] + chip[0][1] + chip[0][0] == 0) && (barWhite == 0)) lastBarWhite = 1; else lastBarWhite = 0;
      if (!CPUplays) {
        if (barWhite != 0) moveCPUWhiteBar();
        else moveCPUWhite();
      } else {
        if (barWhite != 0) moveWhiteBar();
        else moveWhite();
      }
      help();
      if (WhiteOut == 15) Winner();
      lopp += 1;
    } while (lopp < lop);
    player = 1;
    opponent = 0;
    lopp = 0;
    help();
    doubleHumanBlack();
    doublePlayerBlack();
    doubleCPUBlack();
    dice1 = realRandom();
    dice2 = realRandom();
    help();
    if (dice1 == dice2) {
      pash = dice1;
      lop = 4;
    } else lop = 2;
    do {
      possible = 0;
      possibleBar = 0;
      if ((lopp == 1) && (lop == 4)) dice1 = pash;
      if ((lopp == 3) && (lop == 4)) dice2 = pash;
      help();
      if ((chip[1][17] + chip[1][16] + chip[1][15] + chip[1][14] + chip[1][13] + chip[1][12] +
           chip[1][11] + chip[1][10] + chip[1][9] + chip[1][8] + chip[1][7] + chip[1][6] +
           chip[1][18] + chip[1][19] + chip[1][20] + chip[1][21] + chip[1][22] + chip[1][23] == 0) && (barBlack == 0)) lastBarBlack = 1; else lastBarBlack = 0;
      if (CPUplays == 1) {
        if (barBlack != 0) moveCPUBlackBar();
        else moveCPUBlack();
      } else {
        if (barBlack != 0) moveBlackBar();
        else moveBlack();
      }
      help();
      if (BlackOut == 15) Winner();
      lopp += 1;
    } while (lopp < lop);
    help();
  } while (b > 0);
}
void drawBitmapRev(int16_t x, int16_t y,
                   const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color, uint16_t bgcolor) {

  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte;

  for (j = 0; j < h; j++) {
    for (i = 0; i < w; i++) {
      if (i & 7) byte <<= 1;
      else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      if (byte & 0x80) tft.drawPixel(x + i, y - j, color);
      else tft.drawPixel(x + i, y - j, bgcolor);
    }
  }
}
void clear()
{
  for (int xx = 0; xx < 24; xx++)
  {
    chip[0][xx] = 0; //clear board player 1
    chip[1][xx] = 0; //            player 2
  }
}
void beginner()
{
  tft.fillRect(126, 0, 69, 239, ILI9341_MAROON);
  tft.fillRect(195, 110, 120, 20, ILI9341_DARKGREEN);
  tft.setTextSize(1);
  tft.setCursor(200, 116);
  tft.print("Who begins?");
  buttons[0].initButton(&tft, 160, 30, 60, 40, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE, human, 2);
  buttons[0].drawButton();
  buttons[1].initButton(&tft, 160, 90, 60, 40, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE, you, 2);
  buttons[1].drawButton();
  buttons[2].initButton(&tft, 160, 150, 60, 40, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE, cpu, 2);
  buttons[2].drawButton();
  buttons[3].initButton(&tft, 160, 210, 60, 40, ILI9341_WHITE, ILI9341_RED, ILI9341_WHITE, alone, 2);
  buttons[3].drawButton();
  b = 1;
  do {
    waitonetouch(&x, &y);
    if (buttons[0].contains(x, y)) {
      b = 0;
      humanOnly = 1;
    }
    if (buttons[1].contains(x, y)) {
      b = 0;
      CPUplays = 1;
    }
    if (buttons[2].contains(x, y)) {
      CPUplays = 0;
      b = 0;
    }
    if (buttons[3].contains(x, y)) {
      none = 1;
      b = 0;
    }
  } while (b > 0);
  tft.fillRect(6, 116, 120, 10, ILI9341_DARKGREEN);
  tft.fillRect(126, 0, 69, 239, ILI9341_MAROON);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(32, 116);
  if (humanOnly) {
    tft.print("OK, H. vs H.");
    delay(1000);
    return;
  }
  if (none) {
    tft.print("OK, play alone");
    delay(1000);
    return;
  }
  if (CPUplays) {
    tft.print("OK, You begin");
    delay(1000);
    return;
  }
  if (!CPUplays) {
    tft.print("OK, CPU begin");
    delay(1000);
    return;
  }
}
void help() {
  analyse();
  //tft.fillRect(6,116,120,10,ILI9341_DARKGREEN);
  tft.fillRect(195, 110, 120, 20, ILI9341_DARKGREEN);
  //tft.fillRect(136,2,55,10,ILI9341_MAROON);
  tft.fillRect(136, 80, 55, 10, ILI9341_MAROON);
  tft.fillRect(170, 115, 20, 10, ILI9341_MAROON);
  tft.fillRect(170, 130, 20, 10, ILI9341_MAROON);
  tft.fillRect(170, 165, 20, 10, ILI9341_MAROON);
  tft.fillRect(170, 180, 20, 10, ILI9341_MAROON);
  tft.fillRect(170, 215, 20, 10, ILI9341_MAROON);
  tft.fillRect(170, 230, 20, 10, ILI9341_MAROON);
  /*tft.setCursor(143,2);
    tft.print(dice1);
    tft.print("    ");
    tft.print(dice2);*/

  tft.setCursor(136, 80);
  tft.print("Double ");
  tft.print(doubleGame);

  tft.setCursor(136, 100);
  tft.print("---out---");
  tft.setCursor(136, 115);
  tft.print("White ");
  tft.print(WhiteOut);
  tft.setCursor(136, 130);
  tft.print("Black ");
  tft.print(BlackOut);

  tft.setCursor(136, 150);
  tft.print("--moves--");
  tft.setCursor(136, 165);
  tft.print("White ");
  tft.print(movesToWinWhite);
  tft.setCursor(136, 180);
  tft.print("Black ");
  tft.print(movesToWinBlack);


  tft.setCursor(136, 200);
  tft.print("---Bar---");
  tft.setCursor(136, 215);
  tft.print("White  ");
  tft.print(barWhite);
  tft.setCursor(136, 230);
  tft.print("Black  ");
  tft.print(barBlack);

  /*tft.setCursor(10,116);
    tft.print("Player ");
    tft.print(player+1);
    tft.print("  ");
    tft.print(lopp+1);
    tft.print(". Move");*/
  playerPrint();

  tft.setCursor(200, 110);
  tft.print("1won ");
  tft.print(wonBarWhite);
  tft.print(": 2won ");
  tft.print(wonBarBlack);

  tft.setCursor(200, 120);
  tft.print("1bar ");
  tft.print(oneBarWhite);
  tft.print(": 2bar ");
  tft.print(oneBarBlack);
  return;
}
void error() {
  tft.fillRect(6, 116, 120, 10, ILI9341_DARKGREEN);
  tft.setCursor(10, 116);
  tft.print("No Move.Try again");
  delay(1000);
  tft.fillRect(6, 116, 120, 10, ILI9341_DARKGREEN);
}
void nomove() {
  tft.fillRect(6, 116, 120, 10, ILI9341_DARKGREEN);
  tft.setCursor(10, 116);
  tft.print("No possible Move.");
  delay(1000);
  tft.fillRect(6, 116, 120, 10, ILI9341_DARKGREEN);
}
void Winner()
{
  tft.fillRect(6, 116, 120, 10, ILI9341_DARKGREEN);
  tft.fillRect(195, 116, 120, 10, ILI9341_DARKGREEN);
  tft.setCursor(10, 116);
  tft.print("Player ");
  tft.print(player + 1);
  tft.print(" wins.");
  melodie();
  //tft.fillRect(6,116,120,10,ILI9341_DARKGREEN);
  waitonetouch(&x, &y);
  loop();
}
void waitonetouch(unsigned short int *x, unsigned short int *y) {
  do
  {
    delay(100);
    if (myTouch.dataAvailable() == true)
    {
      myTouch.read();
      *x = myTouch.getX();  //Get touch point
      *y = myTouch.getY();
      tone(2, 262, 70);
      delay(100);
      noTone(2);
      return;
    }
  } while (myTouch.dataAvailable() == false);
}
void blink() {
  do {
    unsigned long currentMillis = millis();
    delay(10);
    if (myTouch.dataAvailable() == true) {
      if (chip[player][bartouch] > 6) {
        drawPice(bartouch, 86, 139);
      }
      else deleteBar(bartouch);
      myTouch.read();
      x = myTouch.getX();  //Get touch point
      y = myTouch.getY();
      tone(2, 1175, 70);
      delay(100);
      noTone(2);
      touch();
      return;
    }
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (state == true) {
        state = false;
        deleteBar(bartouch);
      } else
      {
        state = true;
        if (chip[player][bartouch] > 6) {
          drawPice(bartouch, 86, 139);
        }
        else drawPice(bartouch, rowup[chip[player][bartouch] - 1], rowdown[chip[player][bartouch]]);
      }
    }
  } while (b > 0);
}

void touch() {
  for (xx = 0; xx < 12; xx++) {
    if ((x > bar[xx]) && (x < bar[xx] + 20) && (y > 6) && (y < 100)) {
      bartouch = xx;
      return;
    }
    if ((x > bar[xx]) && (x < bar[xx] + 20) && (y > 134) && (y < 234)) {
      bartouch = 23 - xx;
      return;
    }
  }
}
int realRandom() {
  do {
    t = trng_read_output_data(TRNG);
    t2 = abs(t / 10) * 10;
    t = t - t2;
    delay(100);
  } while ((t > 6) || (t < 1));
  return t;
}
void analyse() {
  movesToWinBlack = 0;
  movesToWinWhite = 0;
  wonBarWhite = 0;
  wonBarBlack = 0;
  oneBarWhite = 0;
  oneBarBlack = 0;
  for (xx = 0; xx < 24; xx++) {
    if (chip[0][xx] > 1)wonBarWhite += 1;
    if (chip[1][xx] > 1)wonBarBlack += 1;
    if (chip[0][xx] == 1)oneBarWhite += 1;
    if (chip[1][xx] == 1)oneBarBlack += 1;
    movesToWinBlack += chip[1][xx] * (xx + 1);
    movesToWinWhite += chip[0][xx] * (24 - xx);
  }
  movesToWinBlack = barBlack * 25 + movesToWinBlack;
  movesToWinWhite = barWhite * 25 + movesToWinWhite;
}
int lastBlack()
{
  xx = 24;
  do {
    xx -= 1;
  } while ((xx >= 0) && (chip[1][xx] == 0));
  return xx;
}
int lastWhite()
{
  yy = -1;
  do {
    yy += 1;
  } while ((yy <= 23) && (chip[0][yy] == 0));
  return yy;
}
void doubleHumanWhite() {
  if ((none) && (!humanOnly)) CPUplays = 0;
  if (humanOnly) CPUplays = 1;
  if ((humanOnly) && (!doubleWhite) && (doubleGame < 64)) {
    do {
      waitonetouch(&x, &y);
      if (buttons[0].contains(x, y)) {
        b = 0;
      }
      if (buttons[1].contains(x, y)) {
        tft.fillRect(195, 116, 120, 10, ILI9341_DARKGREEN);
        tft.setCursor(200, 116);
        tft.print("Pl.2 acc. double?");
        waitonetouch(&x, &y);
        tft.fillRect(195, 116, 120, 10, ILI9341_DARKGREEN);
      }
      if (buttons[2].contains(x, y)) {
        doubleWhite = 1;
        doubleBlack = 0;
        doubleGame = doubleGame * 2;
        b = 0;
      }
      if (buttons[3].contains(x, y)) {
        //player=0;
        Winner();
        b = 0;
      }
    } while (b > 0);
  }
  b = 1;
}
void doubleHumanBlack() {
  if ((none) && (!humanOnly))CPUplays = 1;
  if (humanOnly) CPUplays = 0;
  if ((humanOnly) && (!doubleBlack) && (doubleGame < 64)) {
    do {
      waitonetouch(&x, &y);
      if (buttons[0].contains(x, y)) {
        b = 0;
      }
      if (buttons[1].contains(x, y)) {
        tft.fillRect(195, 116, 120, 10, ILI9341_DARKGREEN);
        tft.setCursor(200, 116);
        tft.print("Pl.1 acc. double?");
        waitonetouch(&x, &y);
        tft.fillRect(195, 116, 120, 10, ILI9341_DARKGREEN);
      }
      if (buttons[2].contains(x, y)) {
        doubleWhite = 0;
        doubleBlack = 1;
        doubleGame = doubleGame * 2;
        b = 0;
      }
      if (buttons[3].contains(x, y)) {
        //player=1;
        Winner();
        b = 0;
      }
    } while (b > 0);
  }
  b = 1;
}
void doublePlayerWhite() {
  if ((CPUplays) && (!humanOnly)) {
    if ((!doubleWhite) && (doubleGame < 64)) {
      waitonetouch(&x, &y);
      if (buttons[0].contains(x, y)) {
        return;
      }
      if (buttons[1].contains(x, y)) {
        if (movesToWinBlack + 50 > movesToWinWhite) {
          tft.fillRect(195, 116, 120, 10, ILI9341_DARKGREEN);
          tft.setCursor(200, 116);
          tft.print("CPU acc. double");
          doubleWhite = 1;
          doubleBlack = 0;
          doubleGame = doubleGame * 2;
          delay(1000);
        }
        else Winner();
        return;
      }
    }
  }
}
void doublePlayerBlack() {
  if ((!CPUplays) && (!humanOnly)) {
    if ((!doubleBlack) && (doubleGame < 64))
      waitonetouch(&x, &y);
    if (buttons[0].contains(x, y)) {
      return;
    }
    if (buttons[1].contains(x, y)) {
      if (movesToWinWhite + 50 > movesToWinBlack) {
        tft.fillRect(195, 116, 120, 10, ILI9341_DARKGREEN);
        tft.setCursor(200, 116);
        tft.print("CPU acc. double");
        doubleWhite = 0;
        doubleBlack = 1;
        doubleGame = doubleGame * 2;
        delay(1000);
      }
      else Winner();
      return;
    }
  }
}
void doubleCPUWhite() {
  if ((!CPUplays) && (!humanOnly)) {
    if ((!doubleWhite) && (doubleGame < 64)) {
      if ((movesToWinWhite + 50 > movesToWinBlack) && (!none)) {
        tft.fillRect(195, 116, 120, 10, ILI9341_DARKGREEN);
        tft.setCursor(200, 116);
        tft.print("Pl.2 acc. double?");
        waitonetouch(&x, &y);
        tft.fillRect(195, 116, 120, 10, ILI9341_DARKGREEN);
      }
      if (buttons[2].contains(x, y)) {
        doubleWhite = 1;
        doubleBlack = 0;
        doubleGame = doubleGame * 2;
        return;
      }
      if (buttons[3].contains(x, y)) {
        Winner();
        return;
      }

    }
  }
}

void doubleCPUBlack() {
  if ((CPUplays) && (!humanOnly)) {
    if ((!doubleBlack) && (doubleGame < 64)) {
      if ((movesToWinBlack + 50 > movesToWinWhite) && (!none)) {
        tft.fillRect(195, 116, 120, 10, ILI9341_DARKGREEN);
        tft.setCursor(200, 116);
        tft.print("Pl.1 acc. double?");
        waitonetouch(&x, &y);
        tft.fillRect(195, 116, 120, 10, ILI9341_DARKGREEN);
      }
      if (buttons[2].contains(x, y)) {
        doubleWhite = 0;
        doubleBlack = 1;
        doubleGame = doubleGame * 2;
        return;
      }
      if (buttons[3].contains(x, y)) {
        Winner();
        return;
      }
    }
  }
}
void deleteBar(int Bartouch) {
  if (Bartouch % 2 == 1) color = ILI9341_RED;
  else color = ILI9341_YELLOW;
  if (Bartouch <= 11) {
    if (chip[player][Bartouch] > 6) {
      tft.drawBitmap(bar[Bartouch], 86, fullbar[5], 16, 16, color, bg);
    }
    else tft.drawBitmap(bar[Bartouch], rowup[chip[player][Bartouch] - 1], fullbar[chip[player][Bartouch] - 1], 16, 16, color, bg);
  } else
  {
    if (chip[player][Bartouch] > 6) {
      drawBitmapRev(bar[Bartouch], 154, fullbar[5], 16, 16, color, bg);
    }
    else drawBitmapRev(bar[Bartouch], rowdown[chip[player][Bartouch] - 1], fullbar[chip[player][Bartouch] - 1], 16, 16, color, bg);
  }
}
void drawPice(int BarTouch, int up, int down) {
  if (BarTouch <= 11) {
    if (chip[player][BarTouch] > 6) {
      tft.drawBitmap(bar[BarTouch], 86, pice, 16, 16, playeer[player]);
    } else {
      tft.drawBitmap(bar[BarTouch], up, pice, 16, 16, playeer[player]);
    }
  } else
  {
    if (chip[player][BarTouch] > 6) {
      tft.drawBitmap(bar[BarTouch], 139, pice, 16, 16, playeer[player]);
    } else {
      tft.drawBitmap(bar[BarTouch], down, pice, 16, 16, playeer[player]);
    }
  }
}
void moreThanSix() {
  if (player == 0) tft.setTextColor(playeer[1]);
  else
    tft.setTextColor(playeer[0]);
  if (bartouch <= 11) {
    tft.drawBitmap(bar[bartouch], 6, pice, 16, 16, playeer[player]);
    tft.setCursor(bar[bartouch] + 6, 10);
    tft.print(chip[player][bartouch] + 1);
  } else
  {
    tft.drawBitmap(bar[bartouch], 218, pice, 16, 16, playeer[player]);
    tft.setCursor(bar[bartouch] + 6, 222);
    tft.print(chip[player][bartouch] + 1);
  }
  tft.setTextColor(ILI9341_WHITE);
}
void lessSix() {
  if (chip[player][bartouched] > 6) {
    if (player == 0) tft.setTextColor(playeer[1]);
    else
      tft.setTextColor(playeer[0]);
    if (bartouched <= 11) {
      tft.drawBitmap(bar[bartouched], 86, pice, 16, 16, playeer[player]);
      tft.drawBitmap(bar[bartouched], 6, pice, 16, 16, playeer[player]);
      if (chip[player][bartouched] - 1 > 6) {
        tft.setCursor(bar[bartouched] + 6, 10);
        tft.print(chip[player][bartouched] - 1);
      }
    } else
    {
      tft.drawBitmap(bar[bartouched], 139, pice, 16, 16, playeer[player]);
      tft.drawBitmap(bar[bartouched], 218, pice, 16, 16, playeer[player]);
      if (chip[player][bartouched] - 1 > 6) {
        tft.setCursor(bar[bartouched] + 6, 222);
        tft.print(chip[player][bartouched] - 1);
      }
    }
  } else {
    deleteBar(bartouched);
    return;
  }
  tft.setTextColor(ILI9341_WHITE);
}
void moreOrLess() {
  lessSix();
  if (chip[player][bartouch] >= 6) {
    moreThanSix();
  }
  else
  {
    drawPice(bartouch, rowup[chip[player][bartouch]], rowdown[chip[player][bartouch] + 1]);
  }
}
void drawGame() {
  color = ILI9341_RED;
  color2 = ILI9341_YELLOW;
  int yy = 0;
  for (int xx = 0; xx < 24; xx++)
  {
    for (int yy = 0; yy < 6; yy++)
    {
      if (xx % 2 == 1) color = ILI9341_RED;
      else color = ILI9341_YELLOW;
      if (xx < 12) {
        tft.drawBitmap(bar[xx], rowup[yy], fullbar[yy], 16, 16, color, bg);
      }
      else drawBitmapRev(bar[xx], rowdown[yy], fullbar[yy], 16, 16, color, bg);
    }
  }
  for (int yy = 0; yy < 2; yy++)
  {
    tft.drawBitmap(bar[0], rowup[yy], pice, 16, 16, ILI9341_LIGHTGREY);
    tft.drawBitmap(bar[23], rowdown[yy + 1], pice, 16, 16, ILI9341_BLACK);
  }
  chip[0][0] = 2;
  chip[1][23] = 2;
  for (int yy = 0; yy < 5; yy++)
  {
    tft.drawBitmap(bar[18], rowdown[yy + 1], pice, 16, 16, ILI9341_LIGHTGREY);
    tft.drawBitmap(bar[5], rowup[yy], pice, 16, 16, ILI9341_BLACK);
  }
  chip[0][18] = 5;
  chip[1][5] = 5;
  /*chip[0][19]=5;
    chip[1][4]=5;
    chip[0][20]=5;
    chip[1][3]=5;*/
  for (int yy = 0; yy < 3; yy++)
  {
    tft.drawBitmap(bar[16], rowdown[yy + 1], pice, 16, 16, ILI9341_LIGHTGREY);
    tft.drawBitmap(bar[7], rowup[yy], pice, 16, 16, ILI9341_BLACK);
  }
  chip[0][16] = 3;
  chip[1][7] = 3;
  for (int yy = 0; yy < 5; yy++)
  {
    tft.drawBitmap(bar[11], rowup[yy], pice, 16, 16, ILI9341_LIGHTGREY);
    tft.drawBitmap(bar[12], rowdown[yy + 1], pice, 16, 16, ILI9341_BLACK);
  }
  chip[0][11] = 5;
  chip[1][12] = 5;
}
void playerPrint() {
  tft.fillRect(6, 116, 120, 10, ILI9341_DARKGREEN);
  tft.fillRect(136, 2, 55, 10, ILI9341_MAROON);
  tft.setCursor(143, 2);
  tft.print(dice1);
  tft.print("    ");
  tft.print(dice2);
  tft.setCursor(10, 116);
  tft.print("Player ");
  tft.print(player + 1);
  tft.print("  ");
  tft.print(lopp + 1);
  tft.print(". Move");
}
/*
  Melody on pin 2 of DUE

  http://arduino.cc/en/Tutorial/Tone

*/

// notes in the melody:
int melody[] = {262, 196, 196, 220, 196, 0, 247, 262};
// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void melodie() {
  // iterate over the notes of the melody:

  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(2, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(2);
  }
}


/*
  Tone generator
  v1  use timer, and toggle any digital pin in ISR
   funky duration from arduino version
   TODO use FindMckDivisor?
   timer selected will preclude using associated pins for PWM etc.
    could also do timer/pwm hardware toggle where caller controls duration
*/


// timers TC0 TC1 TC2   channels 0-2 ids 0-2  3-5  6-8     AB 0 1
// use TC1 channel 0
#define TONE_TIMER TC1
#define TONE_CHNL 0
#define TONE_IRQ TC3_IRQn

// TIMER_CLOCK4   84MHz/128 with 16 bit counter give 10 Hz to 656KHz
//  piano 27Hz to 4KHz

static uint8_t pinEnabled[PINS_COUNT];
static uint8_t TCChanEnabled = 0;
static boolean pin_state = false ;
static Tc *chTC = TONE_TIMER;
static uint32_t chNo = TONE_CHNL;

volatile static int32_t toggle_count;
static uint32_t tone_pin;

// frequency (in hertz) and duration (in milliseconds).

void tone(uint32_t ulPin, uint32_t frequency, int32_t duration)
{
  const uint32_t rc = VARIANT_MCK / 256 / frequency;
  tone_pin = ulPin;
  toggle_count = 0;  // strange  wipe out previous duration
  if (duration > 0 ) toggle_count = 2 * frequency * duration / 1000;
  else toggle_count = -1;

  if (!TCChanEnabled) {
    pmc_set_writeprotect(false);
    pmc_enable_periph_clk((uint32_t)TONE_IRQ);
    TC_Configure(chTC, chNo,
                 TC_CMR_TCCLKS_TIMER_CLOCK4 |
                 TC_CMR_WAVE |         // Waveform mode
                 TC_CMR_WAVSEL_UP_RC ); // Counter running up and reset when equals to RC

    chTC->TC_CHANNEL[chNo].TC_IER = TC_IER_CPCS; // RC compare interrupt
    chTC->TC_CHANNEL[chNo].TC_IDR = ~TC_IER_CPCS;
    NVIC_EnableIRQ(TONE_IRQ);
    TCChanEnabled = 1;
  }
  if (!pinEnabled[ulPin]) {
    pinMode(ulPin, OUTPUT);
    pinEnabled[ulPin] = 1;
  }
  TC_Stop(chTC, chNo);
  TC_SetRC(chTC, chNo, rc);    // set frequency
  TC_Start(chTC, chNo);
}

void noTone(uint32_t ulPin)
{
  TC_Stop(chTC, chNo);  // stop timer
  digitalWrite(ulPin, LOW); // no signal on pin
}

// timer ISR  TC1 ch 0
void TC3_Handler ( void ) {
  TC_GetStatus(TC1, 0);
  if (toggle_count != 0) {
    // toggle pin  TODO  better
    digitalWrite(tone_pin, pin_state = !pin_state);
    if (toggle_count > 0) toggle_count--;
  } else {
    noTone(tone_pin);
  }
}
void oneTone() {
  tone(2, 1175, 70);
  delay(100);
  noTone(2);
}
void moveCPUBlack()
{ if (lastBarBlack == 1) {
    for (int xx = 0; xx < 6; xx++) {
      if ((xx + 1 == dice1) && (chip[player][xx] > 0) && (dice1 != 0))possibleBar = 1;
      if ((xx + 1 == dice2) && (chip[player][xx] > 0) && (dice2 != 0))possibleBar = 1;
    }
    if ((dice1 == 6) && (dice1 != 0) || (dice2 == 6) && (dice2 != 0) && (chip[player][4] >= 1) && (chip[player][5] == 0) ||
        (dice1 == 6) && (dice1 != 0) || (dice2 == 6) && (dice2 != 0) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 6) && (dice1 != 0) || (dice2 == 6) && (dice2 != 0) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 6) && (dice1 != 0) || (dice2 == 6) && (dice2 != 0) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 6) && (dice1 != 0) || (dice2 == 6) && (dice2 != 0) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 5) && (dice1 != 0) || (dice2 == 5) && (dice2 != 0) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 5) && (dice1 != 0) || (dice2 == 5) && (dice2 != 0) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 5) && (dice1 != 0) || (dice2 == 5) && (dice2 != 0) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 5) && (dice1 != 0) || (dice2 == 5) && (dice2 != 0) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 4) && (dice1 != 0) || (dice2 == 4) && (dice2 != 0) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 4) && (dice1 != 0) || (dice2 == 4) && (dice2 != 0) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 4) && (dice1 != 0) || (dice2 == 4) && (dice2 != 0) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 3) && (dice1 != 0) || (dice2 == 3) && (dice2 != 0) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 3) && (dice1 != 0) || (dice2 == 3) && (dice2 != 0) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 2) && (dice1 != 0) || (dice2 == 2) && (dice2 != 0) && (chip[player][0] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))
      possibleBar = 1;
  }
  for (int xx = 0; xx < 24; xx++) {
    if ((chip[player][xx] > 0) && (xx - dice1 >= 0) && (chip[opponent][xx - dice1] < 2) && (dice1 != 0))possible += 1;
    if ((chip[player][xx] > 0) && (xx - dice2 >= 0) && (chip[opponent][xx - dice2] < 2) && (dice2 != 0))possible += 1;
  }
  if ((possibleBar == 1) && (dice1 != 0)) {
    delay(500);
    bartouched = 64;
    for (int xx = 5; xx >= 0; xx--) {
      if ((xx + 1 == dice1) && (chip[player][xx] > 0)) {
        bartouched = xx;
        lessSix();
        chip[player][xx] -= 1;
        BlackOut += 1;
        dice1 = 0;
        oneTone();
        return;
      }
    }
    if ((dice1 == 6) && (chip[player][4] >= 1) && (chip[player][5] == 0))bartouched = 4;
    if ((dice1 == 6) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 3;
    if ((dice1 == 6) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 2;
    if ((dice1 == 6) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 1;
    if ((dice1 == 6) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 0;
    if ((dice1 == 5) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 3;
    if ((dice1 == 5) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 2;
    if ((dice1 == 5) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 1;
    if ((dice1 == 5) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 0;
    if ((dice1 == 4) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 2;
    if ((dice1 == 4) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 1;
    if ((dice1 == 4) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 0;
    if ((dice1 == 3) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 1;
    if ((dice1 == 3) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 0;
    if ((dice1 == 2) && (chip[player][0] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 0;
    if (bartouched != 64) {
      lessSix();
      chip[player][bartouched] -= 1;
      BlackOut += 1;
      dice1 = 0;
      oneTone();
      return;
    }
  }
  if ((possibleBar == 1) && (dice2 != 0)) {
    delay(500);
    for (int xx = 5; xx >= 0; xx--) {
      if ((xx + 1 == dice2) && (chip[player][xx] > 0)) {
        bartouched = xx;
        lessSix();
        chip[player][xx] -= 1;
        BlackOut += 1;
        dice2 = 0;
        oneTone();
        return;
      }
    }
    if ((dice2 == 6) && (chip[player][4] >= 1) && (chip[player][5] == 0))bartouched = 4;
    if ((dice2 == 6) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 3;
    if ((dice2 == 6) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 2;
    if ((dice2 == 6) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 1;
    if ((dice2 == 6) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 0;
    if ((dice2 == 5) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 3;
    if ((dice2 == 5) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 2;
    if ((dice2 == 5) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 1;
    if ((dice2 == 5) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 0;
    if ((dice2 == 4) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 2;
    if ((dice2 == 4) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 1;
    if ((dice2 == 4) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 0;
    if ((dice2 == 3) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 1;
    if ((dice2 == 3) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 0;
    if ((dice2 == 2) && (chip[player][0] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))bartouched = 0;
    if (bartouched != 64) {
      lessSix();
      chip[player][bartouched] -= 1;
      BlackOut += 1;
      dice2 = 0;
      oneTone();
      return;
    }
  }
  //pash 2 new bars
  if ((dice1 == dice2) && (lopp == 0) && (lastBlack() > lastWhite())) {
    for (xx = 23; xx >= 0; xx--) {
      if ((chip[player][xx] > 3) && (chip[opponent][xx - dice1] < 2) && (xx - dice1 >= 0) ||
          (chip[player][xx] == 2) && (chip[opponent][xx - dice1] < 2) && (xx - dice1 >= 0)) {
        for (yy = xx - 1; yy >= 0; yy--) {
          if ((chip[player][yy] > 3) && (chip[opponent][yy - dice1] < 2) && (yy - dice2 >= 0) ||
              (chip[player][yy] == 2) && (chip[opponent][yy - dice1] < 2) && (yy - dice2 >= 0)) {
            bartouched = xx - dice1;
            bartouch = xx;
            blinkCPUBlack(dice1);
            lopp += 1;
            playerPrint();
            bartouched = xx - dice1;
            bartouch = xx;
            blinkCPUBlack(dice1);
            lopp += 1;
            dice1 = 0;
            playerPrint();
            xx = yy;
            bartouched = xx - dice2;
            bartouch = xx;
            blinkCPUBlack(dice2);
            lopp += 1;
            playerPrint();
            bartouched = xx - dice2;
            bartouch = xx;
            blinkCPUBlack(dice2);
            lopp += 1;
            dice2 = 0;
            playerPrint();
            return;
          }
        }
      }
    }
  }
  // new bar with 2 dice
  if ((dice1 > dice2) && (dice1 != 0) && (dice2 != 0) && (lastBlack() > lastWhite())) {
    for (xx = 23; xx >= 0; xx--) {
      if ((chip[player][xx] > 2) && (xx - dice1 >= 0) && (chip[opponent][xx - dice1] < 2)) {
        for (yy = xx - 1; yy >= 0; yy--) {
          if ((chip[player][yy] > 2) && (yy - dice2 <= 23) && (chip[opponent][yy - dice2] < 2) && (xx - dice1 == yy - dice2)) {
            bartouched = xx - dice1;
            bartouch = xx;
            blinkCPUBlack(dice1);
            lopp += 1;
            dice1 = 0;
            playerPrint();
            xx = yy;
            bartouched = xx - dice2;
            bartouch = xx;
            blinkCPUBlack(dice2);
            lopp += 1;
            dice2 = 0;
            playerPrint();
            return;
          }
        }
      }
    }
  }
  if ((dice2 > dice1) && (dice1 != 0) && (dice2 != 0) && (lastBlack() > lastWhite())/*&&(oneBarBlack==0)*/) {
    for (xx = 23; xx >= 0; xx--) {
      if ((chip[player][xx] > 2) && (xx - dice2 >= 0) && (chip[opponent][xx - dice2] < 2)) {
        for (yy = xx - 1; yy >= 0; yy--) {
          if ((chip[player][yy] > 2) && (yy - dice1 >= 0) && (chip[opponent][yy - dice1] < 2) && (xx - dice2 == yy - dice1)) {
            bartouched = xx - dice2;
            bartouch = xx;
            blinkCPUBlack(dice2);
            lopp += 1;
            dice2 = 0;
            xx = yy;
            bartouched = xx - dice1;
            bartouch = xx;
            blinkCPUBlack(dice1);
            lopp += 1;
            dice1 = 0;
            return;
          }
        }
      }
    }
  }
  for (xx = 23; xx >= 0; xx--) {
    if ((chip[player][xx] > 2) && (xx - dice1 >= 0) && (chip[opponent][xx - dice1] == 1) && (dice1 != 0)) {
      bartouched = xx - dice1;
      bartouch = xx;
      blinkCPUBlack(dice1);
      dice1 = 0;
      return;
    }
    //new bar dice 2
    if ((chip[player][xx] > 0) && (xx - dice2 >= 0) && (chip[player][xx - dice2] == 1) && (dice2 != 0)) {
      bartouched = xx - dice2;
      bartouch = xx;
      blinkCPUBlack(dice2);
      dice2 = 0;
      return;
    }
    //throw out dice 2
    if ((chip[player][xx] > 2) && (xx - dice2 >= 0) && (chip[opponent][xx - dice2] == 1) && (dice2 != 0)) {
      bartouched = xx - dice2;
      bartouch = xx;
      blinkCPUBlack(dice2);
      dice2 = 0;
      return;
    }
    //new bar dice 1
    if ((chip[player][xx] > 0) && (xx - dice1 >= 0) && (chip[player][xx - dice1] == 1) && (dice1 != 0)) {
      bartouched = xx - dice1;
      bartouch = xx;
      blinkCPUBlack(dice1);
      dice1 = 0;
      return;
    }
    //thow possible move
    if ((chip[player][xx] > 2) && (xx - dice1 >= 0) && (chip[opponent][xx - dice1] < 2) && (dice1 != 0)) {
      bartouched = xx - dice1;
      bartouch = xx;
      blinkCPUBlack(dice1);
      dice1 = 0;
      return;
    }
    if ((chip[player][xx] > 0) && (xx - dice1 >= 0) && (chip[opponent][xx - dice1] < 2) && (dice1 != 0)) {
      bartouched = xx - dice1;
      bartouch = xx;
      blinkCPUBlack(dice1);
      dice1 = 0;
      return;
    }
    if ((chip[player][xx] > 2) && (xx - dice2 >= 0) && (chip[opponent][xx - dice2] < 2) && (dice2 != 0)) {
      bartouched = xx - dice2;
      bartouch = xx;
      blinkCPUBlack(dice2);
      dice2 = 0;
      return;
    }
    if ((chip[player][xx] > 0) && (xx - dice2 >= 0) && (chip[opponent][xx - dice2] < 2) && (dice2 != 0)) {
      bartouched = xx - dice2;
      bartouch = xx;
      blinkCPUBlack(dice2);
      dice2 = 0;
      return;
    }
  }
}
void blinkCPUBlack(int dicee) {
  oneTone();
  deleteBar(bartouch);
  delay(500);
  if (chip[player][bartouch] > 6) {
    drawPice(bartouch, 86, 139);
  }
  else {
    drawPice(bartouch, rowup[chip[player][bartouch] - 1], rowdown[chip[player][bartouch]]);
  }
  delay(500);
  deleteBar(bartouch);
  delay(500);
  if (chip[opponent][xx - dicee] == 1) {
    chip[opponent][xx - dicee] -= 1;
    barWhite += 1;
  }
  bartouched = xx;
  bartouch = xx - dicee;
  moreOrLess();
  chip[player][xx] -= 1;
  chip[player][xx - dicee] += 1;
  return;
}
void moveCPUBlackBar() {
  //possible back in game?
  if ((chip[opponent][24 - dice1] >= 2) && (chip[opponent][24 - dice2] >= 2) && (dice1 != 0) && (dice2 != 0) ||
      (chip[opponent][24 - dice1] >= 2) && (dice2 == 0) && (dice1 != 0) ||
      (chip[opponent][24 - dice2] >= 2) && (dice1 == 0) && (dice2 != 0))
  {
    nomove();
    lopp = 5;
    return;
  }
  //help();
  //delay(500);
  if ((chip[opponent][24 - dice1] == 1) && (dice1 != 0)) {
    tft.drawBitmap(bar[24 - dice1], rowdown[chip[player][24 - dice1] + 1], pice, 16, 16, ILI9341_BLACK);
    chip[opponent][24 - dice1] -= 1;
    barWhite += 1;
    barBlack -= 1;
    chip[player][24 - dice1] += 1;
    dice1 = 0;
    return;
  }
  if ((chip[opponent][24 - dice2] == 1) && (dice2 != 0)) {
    tft.drawBitmap(bar[24 - dice2], rowdown[chip[player][24 - dice2] + 1], pice, 16, 16, ILI9341_BLACK);
    chip[opponent][24 - dice2] -= 1;
    barWhite += 1;
    barBlack -= 1;
    chip[player][24 - dice2] += 1;
    dice2 = 0;
    return;
  }
  if ((chip[opponent][24 - dice1] == 0) && (dice1 != 0)) {
    tft.drawBitmap(bar[24 - dice1], rowdown[chip[player][24 - dice1] + 1], pice, 16, 16, ILI9341_BLACK);
    barBlack -= 1;
    chip[player][24 - dice1] += 1;
    dice1 = 0;
    return;
  }
  if ((chip[opponent][24 - dice2] == 0) && (dice2 != 0)) {
    tft.drawBitmap(bar[24 - dice2], rowdown[chip[player][24 - dice2] + 1], pice, 16, 16, ILI9341_BLACK);
    barBlack -= 1;
    chip[player][24 - dice2] += 1;
    dice2 = 0;
    return;
  }
}
void moveCPUWhite()
{ if (lastBarWhite == 1) {
    for (int xx = 23; xx > 17; xx--) {
      if ((24 - xx == dice1) && (chip[player][xx] > 0) && (dice1 != 0))possibleBar = 1;
      if ((24 - xx == dice2) && (chip[player][xx] > 0) && (dice2 != 0))possibleBar = 1;
    }
    if ((dice1 == 6) && (dice1 != 0) || (dice2 == 6) && (dice2 != 0) && (chip[player][19] >= 1) && (chip[player][18] == 0) ||
        (dice1 == 6) && (dice1 != 0) || (dice2 == 6) && (dice2 != 0) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 6) && (dice1 != 0) || (dice2 == 6) && (dice2 != 0) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 6) && (dice1 != 0) || (dice2 == 6) && (dice2 != 0) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 6) && (dice1 != 0) || (dice2 == 6) && (dice2 != 0) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 5) && (dice1 != 0) || (dice2 == 5) && (dice2 != 0) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 5) && (dice1 != 0) || (dice2 == 5) && (dice2 != 0) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 5) && (dice1 != 0) || (dice2 == 5) && (dice2 != 0) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 5) && (dice1 != 0) || (dice2 == 5) && (dice2 != 0) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 4) && (dice1 != 0) || (dice2 == 4) && (dice2 != 0) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 4) && (dice1 != 0) || (dice2 == 4) && (dice2 != 0) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 4) && (dice1 != 0) || (dice2 == 4) && (dice2 != 0) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 3) && (dice1 != 0) || (dice2 == 3) && (dice2 != 0) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 3) && (dice1 != 0) || (dice2 == 3) && (dice2 != 0) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 2) && (dice1 != 0) || (dice2 == 2) && (dice2 != 0) && (chip[player][23] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))
      possibleBar = 1;
  }
  for (int xx = 0; xx < 24; xx++) {
    if ((chip[player][xx] > 0) && (xx + dice1 <= 23) && (chip[opponent][xx + dice1] < 2) && (dice1 != 0))possible += 1;
    if ((chip[player][xx] > 0) && (xx + dice2 <= 23) && (chip[opponent][xx + dice2] < 2) && (dice2 != 0))possible += 1;
  }
  if ((possibleBar == 1) && (dice1 != 0)) {
    bartouched = 64;
    delay(500);
    for (int xx = 23; xx > 17; xx--) {
      if ((24 - xx == dice1) && (chip[player][xx] > 0)) {
        bartouched = xx;
        lessSix();
        chip[player][xx] -= 1;
        WhiteOut += 1;
        dice1 = 0;
        oneTone();
        return;
      }
    }
    if ((dice1 == 6) && (chip[player][19] >= 1) && (chip[player][18] == 0))bartouched = 19;
    if ((dice1 == 6) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 20;
    if ((dice1 == 6) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 21;
    if ((dice1 == 6) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 22;
    if ((dice1 == 6) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 23;
    if ((dice1 == 5) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 20;
    if ((dice1 == 5) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 21;
    if ((dice1 == 5) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 22;
    if ((dice1 == 5) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 23;
    if ((dice1 == 4) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 21;
    if ((dice1 == 4) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 22;
    if ((dice1 == 4) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 23;
    if ((dice1 == 3) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 22;
    if ((dice1 == 3) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 23;
    if ((dice1 == 2) && (chip[player][23] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 23;
    if (bartouched != 64) {
      lessSix();
      chip[player][bartouched] -= 1;
      WhiteOut += 1;
      dice1 = 0;
      oneTone();
      return;
    }
  }
  if ((possibleBar == 1) && (dice2 != 0)) {
    delay(500);
    for (int xx = 23; xx > 17; xx--) {
      if ((24 - xx == dice2) && (chip[player][xx] > 0)) {
        bartouched = xx;
        lessSix();
        chip[player][xx] -= 1;
        WhiteOut += 1;
        dice2 = 0;
        oneTone();
        return;
      }
    }
    if ((dice2 == 6) && (chip[player][19] >= 1) && (chip[player][18] == 0))bartouched = 19;
    if ((dice2 == 6) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 20;
    if ((dice2 == 6) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 21;
    if ((dice2 == 6) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 22;
    if ((dice2 == 6) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 23;
    if ((dice2 == 5) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 20;
    if ((dice2 == 5) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 21;
    if ((dice2 == 5) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 22;
    if ((dice2 == 5) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 23;
    if ((dice2 == 4) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 21;
    if ((dice2 == 4) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 22;
    if ((dice2 == 4) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 23;
    if ((dice2 == 3) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 22;
    if ((dice2 == 3) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 23;
    if ((dice2 == 2) && (chip[player][23] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))bartouched = 23;
    if (bartouched != 64) {
      lessSix();
      chip[player][bartouched] -= 1;
      WhiteOut += 1;
      dice2 = 0;
      oneTone();
      return;
    }
  }
  //pash 2 new bars
  if ((dice1 == dice2) && (lopp == 0) && (lastWhite() < lastBlack())) {
    for (xx = 0; xx <= 23; xx++) {
      if ((chip[player][xx] > 3) && (chip[opponent][xx + dice1] < 2) && (xx + dice1 <= 23) ||
          (chip[player][xx] == 2) && (chip[opponent][xx + dice1] < 2) && (xx + dice1 <= 23)) {
        for (yy = xx + 1; yy <= 23; yy++) {
          if ((chip[player][yy] > 3) && (chip[opponent][yy + dice1] < 2) && (yy + dice2 <= 23) ||
              (chip[player][yy] == 2) && (chip[opponent][yy + dice1] < 2) && (yy + dice2 <= 23)) {
            bartouched = xx + dice1;
            bartouch = xx;
            blinkCPUWhite(dice1);
            lopp += 1;
            playerPrint();
            bartouched = xx + dice1;
            bartouch = xx;
            blinkCPUWhite(dice1);
            lopp += 1;
            dice1 = 0;
            playerPrint();
            xx = yy;
            bartouched = xx + dice2;
            bartouch = xx;
            blinkCPUWhite(dice2);
            lopp += 1;
            playerPrint();
            bartouched = xx + dice2;
            bartouch = xx;
            blinkCPUWhite(dice2);
            lopp += 1;
            dice2 = 0;
            playerPrint();
            return;
          }
        }
      }
    }
  }
  // new bar with 2 dice
  if ((dice1 > dice2) && (dice1 != 0) && (dice2 != 0) && (lastWhite() < lastBlack())) {
    for (xx = 0; xx <= 23; xx++) {
      if ((chip[player][xx] > 2) && (xx + dice1 <= 23) && (chip[opponent][xx + dice1] < 2)) {
        for (yy = xx + 1; yy <= 23; yy++) {
          if ((chip[player][yy] > 2) && (yy + dice2 <= 23) && (chip[opponent][yy + dice2] < 2) && (xx + dice1 == yy + dice2)) {
            bartouched = xx + dice1;
            bartouch = xx;
            blinkCPUWhite(dice1);
            lopp += 1;
            dice1 = 0;
            playerPrint();
            xx = yy;
            bartouched = xx + dice2;
            bartouch = xx;
            blinkCPUWhite(dice2);
            lopp += 1;
            dice2 = 0;
            playerPrint();
            return;
          }
        }
      }
    }
  }
  if ((dice2 > dice1) && (dice1 != 0) && (dice2 != 0) && (lastWhite() < lastBlack())/*&&(oneBarWhite==0)*/) {
    for (xx = 0; xx <= 23; xx++) {
      if ((chip[player][xx] > 2) && (xx + dice2 <= 23) && (chip[opponent][xx + dice2] < 2)) {
        for (yy = xx + 1; yy <= 23; yy++) {
          if ((chip[player][yy] > 2) && (yy + dice1 <= 23) && (chip[opponent][yy + dice1] < 2) && (xx + dice2 == yy + dice1)) {
            bartouched = xx + dice2;
            bartouch = xx;
            blinkCPUWhite(dice2);
            lopp += 1;
            dice2 = 0;
            xx = yy;
            bartouched = xx + dice1;
            bartouch = xx;
            blinkCPUWhite(dice1);
            lopp += 1;
            dice1 = 0;
            return;
          }
        }
      }
    }
  }
  //throw out dice 1
  for (xx = 0; xx <= 23; xx++) {
    if ((chip[player][xx] > 0) && (xx + dice1 <= 23) && (chip[opponent][xx + dice1] == 1) && (dice1 != 0)) {
      bartouched = xx + dice1;
      bartouch = xx;
      blinkCPUWhite(dice1);
      dice1 = 0;
      return;
    }
    //new bar dice 2
    if ((chip[player][xx] > 2) && (xx + dice1 <= 23) && (chip[player][xx + dice2] == 1) && (dice2 != 0)) {
      bartouched = xx + dice2;
      bartouch = xx;
      blinkCPUWhite(dice2);
      dice2 = 0;
      return;
    }
    //throw out dice 2
    if ((chip[player][xx] > 0) && (xx + dice2 <= 23) && (chip[opponent][xx + dice2] == 1) && (dice2 != 0)) {
      bartouched = xx + dice2;
      bartouch = xx;
      blinkCPUWhite(dice2);
      dice2 = 0;
      return;
    }
    //new bar dice 1
    if ((chip[player][xx] > 2) && (xx + dice1 <= 23) && (chip[player][xx + dice1] == 1) && (dice1 != 0)) {
      bartouched = xx + dice1;
      bartouch = xx;
      blinkCPUWhite(dice1);
      dice1 = 0;
      return;
    }
    //thow possible move
    if ((chip[player][xx] > 2) && (xx + dice1 <= 24) && (chip[opponent][xx + dice1] < 2) && (dice1 != 0)) {
      bartouched = xx + dice1;
      bartouch = xx;
      blinkCPUWhite(dice1);
      dice1 = 0;
      return;
    }
    if ((chip[player][xx] > 0) && (xx + dice1 <= 24) && (chip[opponent][xx + dice1] < 2) && (dice1 != 0)) {
      bartouched = xx + dice1;
      bartouch = xx;
      blinkCPUWhite(dice1);
      dice1 = 0;
      return;
    }
    if ((chip[player][xx] > 2) && (xx + dice2 <= 24) && (chip[opponent][xx + dice2] < 2) && (dice2 != 0)) {
      bartouched = xx + dice2;
      bartouch = xx;
      blinkCPUWhite(dice2);
      dice2 = 0;
      return;
    }
    if ((chip[player][xx] >> 0) && (xx + dice2 <= 24) && (chip[opponent][xx + dice2] < 2) && (dice2 != 0)) {
      bartouched = xx + dice2;
      bartouch = xx;
      blinkCPUWhite(dice2);
      dice2 = 0;
      return;
    }
  }
}
void blinkCPUWhite(int dicee) {
  oneTone();
  deleteBar(bartouch);
  delay(500);
  if (chip[player][bartouch] > 6) {
    drawPice(bartouch, 86, 139);
  }
  else {
    drawPice(bartouch, rowup[chip[player][bartouch] - 1], rowdown[chip[player][bartouch]]);
  }
  delay(500);
  deleteBar(bartouch);
  delay(500);
  if (chip[opponent][xx + dicee] == 1) {
    chip[opponent][xx + dicee] -= 1;
    barBlack += 1;
  }
  bartouched = xx;
  bartouch = xx + dicee;
  moreOrLess();
  chip[player][xx] -= 1;
  chip[player][xx + dicee] += 1;
  return;
}
void moveCPUWhiteBar() {
  //possible back in game?
  if ((chip[opponent][dice1 - 1] >= 2) && (chip[opponent][dice2 - 1] >= 2) && (dice1 != 0) && (dice2 != 0) ||
      (chip[opponent][dice1 - 1] >= 2) && (dice2 == 0) && (dice1 != 0) ||
      (chip[opponent][dice2 - 1] >= 2) && (dice1 == 0) && (dice2 != 0))
  {
    nomove();
    lopp = 5;
    return;
  }
  //help();
  //delay(500);
  if ((chip[opponent][dice1 - 1] == 1) && (dice1 != 0)) {
    tft.drawBitmap(bar[dice1 - 1], rowup[chip[player][dice1 - 1]], pice, 16, 16, ILI9341_LIGHTGREY);
    chip[opponent][dice1 - 1] -= 1;
    barBlack += 1;
    barWhite -= 1;
    chip[player][dice1 - 1] += 1;
    dice1 = 0;
    return;
  }
  if ((chip[opponent][dice2 - 1] == 1) && (dice2 != 0)) {
    tft.drawBitmap(bar[dice2 - 1], rowup[chip[player][dice2 - 1]], pice, 16, 16, ILI9341_LIGHTGREY);
    chip[opponent][dice2 - 1] -= 1;
    barBlack += 1;
    barWhite -= 1;
    chip[player][dice2 - 1] += 1;
    dice2 = 0;
    return;
  }
  if ((chip[opponent][dice1 - 1] == 0) && (dice1 != 0)) {
    tft.drawBitmap(bar[dice1 - 1], rowup[chip[player][dice1 - 1]], pice, 16, 16, ILI9341_LIGHTGREY);
    barWhite -= 1;
    chip[player][dice1 - 1] += 1;
    dice1 = 0;
    return;
  }
  if ((chip[opponent][dice2 - 1] == 0) && (dice2 != 0)) {
    tft.drawBitmap(bar[dice2 - 1], rowup[chip[player][dice2 - 1]], pice, 16, 16, ILI9341_LIGHTGREY);
    barWhite -= 1;
    chip[player][dice2 - 1] += 1;
    dice2 = 0;
    return;
  }
}
void moveWhiteBar()  {
  if ((chip[opponent][dice1 - 1] >= 2) && (chip[opponent][dice2 - 1] >= 2) && (dice1 != 0) && (dice2 != 0) ||
      (chip[opponent][dice1 - 1] >= 2) && (dice2 == 0) && (dice1 != 0) ||
      (chip[opponent][dice2 - 1] >= 2) && (dice1 == 0) && (dice2 != 0)) {
    nomove();
    lopp = 5;
    return;
  }
  waitonetouch(&x, &y);
  touch();
  help();
  delay(500);
  if (bartouch > 6) {
    error();
    lopp -= 1;
    return;
  }
  switch (bartouch)
  {
    case 0: dicee = 1; break;
    case 1: dicee = 2; break;
    case 2: dicee = 3; break;
    case 3: dicee = 4; break;
    case 4: dicee = 5; break;
    case 5: dicee = 6; break;
  }
  if (chip[opponent][bartouch] >= 2) {
    error();
    lopp -= 1;
    return;
  }
  if ((dicee == dice1) || (dicee == dice2)) {
    tft.drawBitmap(bar[bartouch], rowup[chip[player][bartouch]], pice, 16, 16, ILI9341_LIGHTGREY);
  }
  else {
    error();
    lopp -= 1;
    return;
  }
  if (dicee == dice1) dice1 = 0; else dice2 = 0;
  if (chip[opponent][bartouch] == 1) {
    chip[opponent][bartouch] -= 1;
    barBlack += 1;
  }
  barWhite -= 1;
  chip[player][bartouch] += 1;
  return;
}
void moveWhite() {
  if (lastBarWhite == 1) {
    for (int xx = 23; xx > 17; xx--) {
      if ((24 - xx == dice1) && (chip[player][xx] > 0))possibleBar = 1;
      if ((24 - xx == dice2) && (chip[player][xx] > 0))possibleBar = 1;
    }
    if ((dice1 == 6) || (dice2 == 6) && (chip[player][19] >= 1) && (chip[player][18] == 0) ||
        (dice1 == 6) || (dice2 == 6) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 6) || (dice2 == 6) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 6) || (dice2 == 6) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 6) || (dice2 == 6) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 5) || (dice2 == 5) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 5) || (dice2 == 5) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 5) || (dice2 == 5) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 5) || (dice2 == 5) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 4) || (dice2 == 4) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 4) || (dice2 == 4) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 4) || (dice2 == 4) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 3) || (dice2 == 3) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 3) || (dice2 == 3) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (dice1 == 2) || (dice2 == 2) && (chip[player][23] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))
      possibleBar = 1;
  }
  for (int xx = 0; xx < 24; xx++) {
    if ((chip[player][xx] > 0) && (xx + dice1 >= 0) && (xx + dice1 <= 23) && (chip[opponent][xx + dice1] < 2) && (dice1 != 0) || (chip[player][xx] > 0) && (xx + dice2 >= 0) && (xx + dice2 <= 23) && (chip[opponent][xx + dice2] < 2) && (dice2 != 0))
      possible += 1;
  }
  if ((lastBarWhite == 0) && (possible == 0)) {
    nomove();
    lopp = 5;
    return;
  }
  waitonetouch(&x, &y); touch(); help();
  if ((lastBarWhite == 0) && (bartouch + dice1 >= 24) && (dice1 != 0) && (bartouch + dice2 >= 24) && (dice2 != 0)) {
    error();
    lopp -= 1;
    return;
  }
  if ((lastBarWhite == 0) && (bartouch + dice1 >= 24) && (dice1 != 0) && (dice2 == 0)) {
    error();
    lopp -= 1;
    return;
  }
  if ((lastBarWhite == 0) && (bartouch + dice2 >= 24) && (dice2 != 0) && (dice1 == 0)) {
    error();
    lopp -= 1;
    return;
  }
  if (chip[player][bartouch] == 0) {
    error();
    lopp -= 1;
    return;
  }
  if ((lastBarWhite == 0) && (chip[opponent][bartouch + dice1] >= 2) && (chip[player][bartouch] > 0) && (dice1 != 0) && (chip[opponent][bartouch + dice2] >= 2) && (chip[player][bartouch] > 0) && (dice2 != 0))
  {
    error();
    lopp -= 1;
    return;
  }
  if ((lastBarWhite == 0) && (chip[opponent][bartouch + dice1] >= 2) && (chip[player][bartouch] > 0) && (dice1 != 0) && (dice2 == 0))
  {
    error();
    lopp -= 1;
    return;
  }
  if ((lastBarWhite == 0) && (chip[opponent][bartouch + dice2] >= 2) && (chip[player][bartouch] > 0) && (dice2 != 0) && (dice1 == 0))
  {
    error();
    lopp -= 1;
    return;
  }
  if (bartouch % 2 == 1) color = ILI9341_RED;
  else color = ILI9341_YELLOW;
  delay(150);
  bartouched = bartouch;
  blink();
  delay(500);
  if ((bartouch == bartouched) && (possibleBar == 1) && (24 - bartouched <= dice1) && (dice1 != 0)) {
    if ((24 - bartouch == dice1) && (chip[player][bartouch] > 0)) {
      lessSix();
      chip[player][bartouched] -= 1;
      WhiteOut += 1;
      dice1 = 0;
      return;
    }
    //if((bartouch==18)&&(dice1==6)&&(chip[player][18]>0)||
    if ((bartouch == 19) && (dice1 == 6) && (chip[player][19] >= 1) && (chip[player][18] == 0) ||
        (bartouch == 20) && (dice1 == 6) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 21) && (dice1 == 6) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 22) && (dice1 == 6) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 23) && (dice1 == 6) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 20) && (dice1 == 5) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 21) && (dice1 == 5) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 22) && (dice1 == 5) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 23) && (dice1 == 5) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 21) && (dice1 == 4) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 22) && (dice1 == 4) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 23) && (dice1 == 4) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 22) && (dice1 == 3) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 23) && (dice1 == 3) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 23) && (dice1 == 2) && (chip[player][23] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))
    {
      lessSix();
      chip[player][bartouched] -= 1;
      WhiteOut += 1;
      dice1 = 0;
      return;
    }
  }
  if ((bartouch == bartouched) && (possibleBar == 1) && (24 - bartouched <= dice2) && (dice2 != 0)) {
    if ((24 - bartouch == dice2) && (chip[player][bartouch] > 0)) {
      lessSix();
      chip[player][bartouched] -= 1;
      WhiteOut += 1;
      dice2 = 0;
      return;
    }
    //if((bartouch==18)&&(dice2==6)&&(chip[player][18]>0)||
    if ((bartouch == 19) && (dice2 == 6) && (chip[player][19] >= 1) && (chip[player][18] == 0) ||
        (bartouch == 20) && (dice2 == 6) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 21) && (dice2 == 6) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 22) && (dice2 == 6) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 23) && (dice2 == 6) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 20) && (dice2 == 5) && (chip[player][20] >= 1) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 21) && (dice2 == 5) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 22) && (dice2 == 5) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 23) && (dice2 == 5) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 21) && (dice2 == 4) && (chip[player][21] >= 1) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 22) && (dice2 == 4) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 23) && (dice2 == 4) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 22) && (dice2 == 3) && (chip[player][22] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 23) && (dice2 == 3) && (chip[player][23] >= 1) && (chip[player][22] == 0) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0) ||
        (bartouch == 23) && (dice2 == 2) && (chip[player][23] >= 1) && (chip[player][21] == 0) && (chip[player][20] == 0) && (chip[player][19] == 0) && (chip[player][18] == 0))
    {
      lessSix();
      chip[player][bartouched] -= 1;
      WhiteOut += 1;
      dice2 = 0;
      return;
    }
  }
  if (chip[opponent][bartouch] > 1) {
    drawPice(bartouched, rowup[chip[player][23 - bartouched] - 1], rowdown[chip[player][23 - bartouched]]);
    error();
    lopp -= 1;
    return;
  }
  if (chip[opponent][bartouch] == 1) {
    chip[opponent][bartouch] -= 1;
    barBlack += 1;
  }
  if ((bartouched + dice1 == bartouch) && (dice1 != 0)) {
    moreOrLess();
    chip[player][bartouched] -= 1;
    chip[player][bartouch] += 1;
    dice1 = 0;
    return;
  }
  if ((bartouched + dice2 == bartouch) && (dice2 != 0)) {
    moreOrLess();
    chip[player][bartouched] -= 1;
    chip[player][bartouch] += 1;
    dice2 = 0;
    return;
  } lopp -= 1; drawPice(bartouched, rowup[chip[player][bartouched] - 1], rowdown[chip[player][bartouched]]); return;
}
void moveBlackBar()  {
  //possible back in game?
  if ((chip[opponent][24 - dice1] >= 2) && (chip[opponent][24 - dice2] >= 2) && (dice1 != 0) && (dice2 != 0) ||
      (chip[opponent][24 - dice1] >= 2) && (dice2 == 0) && (dice1 != 0) ||
      (chip[opponent][24 - dice2] >= 2) && (dice1 == 0) && (dice2 != 0))
  {
    nomove();
    lopp = 5;
    return;
  }
  waitonetouch(&x, &y);
  touch();
  help();
  delay(500);
  if (bartouch <= 17) {
    error();
    lopp -= 1;
    return;
  }
  switch (bartouch)
  {
    case 23: dicee = 1; break;
    case 22: dicee = 2; break;
    case 21: dicee = 3; break;
    case 20: dicee = 4; break;
    case 19: dicee = 5; break;
    case 18: dicee = 6; break;
  }

  if (chip[opponent][bartouch] >= 2) {
    error();
    lopp -= 1;
    return;
  }
  if ((dicee == dice1) || (dicee == dice2)) {
    tft.drawBitmap(bar[bartouch], rowdown[chip[player][bartouch] + 1], pice, 16, 16, ILI9341_BLACK);
  }
  else {
    error();
    lopp -= 1;
    return;
  }
  if (dicee == dice1) dice1 = 0; else dice2 = 0;
  if (chip[opponent][bartouch] == 1) {
    chip[opponent][bartouch] -= 1;
    barWhite += 1;
  }
  barBlack -= 1;
  chip[player][bartouch] += 1;
  return;
}
void moveBlack()  {
  if (lastBarBlack == 1) {
    for (int xx = 0; xx < 6; xx++) {
      if ((xx + 1 == dice1) && (chip[player][xx] > 0))possibleBar = 1;
      if ((xx + 1 == dice2) && (chip[player][xx] > 0))possibleBar = 1;
    }
    if ((dice1 == 6) || (dice2 == 6) && (chip[player][4] >= 1) && (chip[player][5] == 0) ||
        (dice1 == 6) || (dice2 == 6) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 6) || (dice2 == 6) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 6) || (dice2 == 6) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 6) || (dice2 == 6) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 5) || (dice2 == 5) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 5) || (dice2 == 5) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 5) || (dice2 == 5) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 5) || (dice2 == 5) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 4) || (dice2 == 4) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 4) || (dice2 == 4) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 4) || (dice2 == 4) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 3) || (dice2 == 3) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 3) || (dice2 == 3) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (dice1 == 2) || (dice2 == 2) && (chip[player][0] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))
      possibleBar = 1;
  }
  for (int xx = 0; xx < 24; xx++) {
    if ((chip[player][xx] > 0) && (xx - dice1 >= 0) && (chip[opponent][xx - dice1] < 2) && (dice1 != 0))possible += 1;
    if ((chip[player][xx] > 0) && (xx - dice2 >= 0) && (chip[opponent][xx - dice2] < 2) && (dice2 != 0))possible += 1;
  }
  if ((lastBarBlack == 0) && (possible == 0)) {
    nomove();
    lopp = 5;
    return;
  }
  waitonetouch(&x, &y); touch(); help();
  if ((lastBarBlack == 0) && (bartouch - dice1 < 0) && (dice1 != 0) && (bartouch - dice2 < 0) && (dice2 != 0)) {
    error();
    lopp -= 1;
    return;
  }
  if ((lastBarBlack == 0) && (bartouch - dice1 < 0) && (dice1 != 0) && (dice2 == 0)) {
    error();
    lopp -= 1;
    return;
  }
  if ((lastBarBlack == 0) && (bartouch - dice2 < 0) && (dice2 != 0) && (dice1 == 0)) {
    error();
    lopp -= 1;
    return;
  }
  if (chip[player][bartouch] == 0) {
    error();
    lopp -= 1;
    return;
  }
  if ((lastBarBlack == 0) && (chip[opponent][bartouch - dice1] >= 2) && (chip[player][bartouch] > 0) && (dice1 != 0) && (chip[opponent][bartouch - dice2] >= 2) && (chip[player][bartouch] > 0) && (dice2 != 0))
  {
    error();
    lopp -= 1;
    return;
  }
  if ((lastBarBlack == 0) && (chip[opponent][bartouch - dice1] >= 2) && (chip[player][bartouch] > 0) && (dice1 != 0) && (dice2 == 0))
  {
    error();
    lopp -= 1;
    return;
  }
  if ((lastBarBlack == 0) && (chip[opponent][bartouch - dice2] >= 2) && (chip[player][bartouch] > 0) && (dice2 != 0) && (dice1 == 0))
  {
    error();
    lopp -= 1;
    return;
  }
  if (bartouch % 2 == 1) color = ILI9341_RED;
  else color = ILI9341_YELLOW;
  delay(150);
  bartouched = bartouch;
  blink();
  delay(500);
  //checkBarOut();
  if ((bartouch == bartouched) && (possibleBar == 1) && (bartouched + 1 <= dice1) && (dice1 != 0)) {
    if ((bartouch + 1 == dice1) && (chip[player][bartouch] > 0)) {
      chip[player][bartouched] -= 1;
      BlackOut += 1;
      dice1 = 0;
      return;
    }
    //if((bartouch==5)&&(dice1==6)&&(chip[player][5]>=1)||
    if ((bartouch == 4) && (dice1 == 6) && (chip[player][4] >= 1) && (chip[player][5] == 0) ||
        (bartouch == 3) && (dice1 == 6) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 2) && (dice1 == 6) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 1) && (dice1 == 6) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 0) && (dice1 == 6) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 3) && (dice1 == 5) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 2) && (dice1 == 5) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 1) && (dice1 == 5) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 0) && (dice1 == 5) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 2) && (dice1 == 4) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 1) && (dice1 == 4) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 0) && (dice1 == 4) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 1) && (dice1 == 3) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 0) && (dice1 == 3) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 0) && (dice1 == 2) && (chip[player][0] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0))
    {
      chip[player][bartouched] -= 1;
      BlackOut += 1;
      dice1 = 0;
      return;
    }
  }
  if ((bartouch == bartouched) && (possibleBar == 1) && (bartouched + 1 <= dice2) && (dice2 != 0)) {
    if ((bartouch + 1 == dice2) && (chip[player][bartouch] > 0)) {
      chip[player][bartouched] -= 1;
      BlackOut += 1;
      dice2 = 0;
      return;
    }
    //if((bartouch==5)&&(dice2==6)&&(chip[player][5]>=1)||
    if ((bartouch == 4) && (dice2 == 6) && (chip[player][4] >= 1) && (chip[player][5] == 0) ||
        (bartouch == 3) && (dice2 == 6) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 2) && (dice2 == 6) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 1) && (dice2 == 6) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 0) && (dice2 == 6) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 3) && (dice2 == 5) && (chip[player][3] >= 1) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 2) && (dice2 == 5) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 1) && (dice2 == 5) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 0) && (dice2 == 5) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 2) && (dice2 == 4) && (chip[player][2] >= 1) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 1) && (dice2 == 4) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 0) && (dice2 == 4) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 1) && (dice2 == 3) && (chip[player][1] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 0) && (dice2 == 3) && (chip[player][0] >= 1) && (chip[player][1] == 0) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0) ||
        (bartouch == 0) && (dice2 == 2) && (chip[player][0] >= 1) && (chip[player][2] == 0) && (chip[player][3] == 0) && (chip[player][4] == 0) && (chip[player][5] == 0)) {
      chip[player][bartouched] -= 1;
      BlackOut += 1;
      dice2 = 0;
      return;
    }
  }
  if (chip[opponent][bartouch] > 1) {
    drawPice(bartouched, rowup[chip[player][bartouched] - 1], rowdown[chip[player][bartouched]]);
    error();
    lopp -= 1;
    return;
  }
  if (chip[opponent][bartouch] == 1) {
    chip[opponent][bartouch] -= 1;
    barWhite += 1;
  }
  if ((bartouched - dice1 == bartouch) && (dice1 != 0)) {
    moreOrLess();
    chip[player][bartouched] -= 1;
    chip[player][bartouch] += 1;
    dice1 = 0;
    return;
  }
  if ((bartouched - dice2 == bartouch) && (dice2 != 0)) {
    moreOrLess();
    chip[player][bartouched] -= 1;
    chip[player][bartouch] += 1;
    dice2 = 0;
    return;
  } lopp -= 1; drawPice(bartouched, rowup[chip[player][bartouched] - 1], rowdown[chip[player][bartouched]]); return;
}
