 

// LCD5110_Graph_Demo 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of most of the functions
// in the library.
//
// This program requires a Nokia 5110 LCD module.
//
// It is assumed that the LCD module is connected to
// the following pins using a levelshifter to get the
// correct voltage to the module.
//      SCK  - Pin 8
//      MOSI - Pin 9
//      DC   - Pin 10
//      RST  - Pin 12
//      CS   - Pin 11
//
//#include <LCD5110_Graph.h>
#include <Adafruit_ILI9341.h>
#define TFT_DC 2
#define TFT_CS 5
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
//LCD5110 myGLCD(8,9,10,12,11);

extern uint8_t SmallFont[];
extern uint8_t arduino_logo[];
extern unsigned char TinyFont[];
extern uint8_t The_End[];
extern uint8_t pacman1[];
extern uint8_t pacman2[];
extern uint8_t pacman3[];
extern uint8_t pill[];

float y;
uint8_t* bm;
int pacy;

void setup()
{
 // myGLCD.InitLCD();
 // myGLCD.setFont(SmallFont);
 tft.begin  ();
   tft.setRotation(3);
   tft.fillScreen(ILI9341_BLACK);
   tft.setCursor(0, 0);
 
  randomSeed(analogRead(7));
}

void loop()
{
  tft.fillScreen(ILI9341_CYAN);
  tft.drawBitmap(0, 0, 84, 48, arduino_logo); 
  tft.update();

  delay(20000);
  
  tft.fillScreen(ILI9341_WHITE);
 tft.print("LCD5110_CORKY", CENTER, 0);
  tft.print("DEMO", CENTER, 20);
  tft.drawRect(28, 18, 56, 28);
  for (int i=0; i<6; i++)
  {
    tft.drawLine(57, 18+(i*2), 83-(i*3), 18+(i*2));
   tft.drawLine((i*3), 28-(i*2), 28, 28-(i*2));
  }
  tft.setFont(TinyFont);
  tft.print("(C)2015 by", CENTER, 36);
  tft.print("David Bevan", CENTER, 42);
  tft.update();
  
  delay(5000);
  
  tft.fillScreen (ILI9341_CYAN);
  for (int i=0; i<48; i+=2)
  {
    tft.drawLine(0, i, 83, 47-i);
    tft.update();
  }
  for (int i=83; i>=0; i-=2)
  {
    tft.drawLine(i, 0, 83-i, 47);
    tft.update();
  }

  delay(2000);
  
  tft.fillScreen (ILI9341_MAGENTA);
  tft.drawRect(0, 0, 83, 47);
  for (int i=0; i<48; i+=4)
  {
    tft.drawLine(0, i, i*1.75, 47);
    tft.update();
  }
  for (int i=0; i<48; i+=4)
  {
    tft.drawLine(83, 47-i, 83-(i*1.75), 0);
    tft.update();
  }

  delay(2000);
  
  tft.fillScreen (ILI9341_BLUE);
  for (int i=0; i<8; i++)
  {
    tft.drawRoundRect(i*3, i*3, 83-(i*3), 47-(i*3));
    tft.update();
  }

  delay(2000);
  
  tft.fillScreen (ILI9341_YELLOW);
  for (int i=0; i<17; i++)
  {
    tft.drawCircle(41, 23, i*3);
    tft.update();
  }

  delay(2000);
  
  tft.fillScreen (ILI9341_RED);
  tft.drawRect(0, 0, 83, 47);
  tft.drawLine(0, 23, 84, 23);
  tft.drawLine(41, 0, 41, 47);
  for (int c=0; c<4; c++)
  {
    for (int i=0; i<84; i++)
    {
      y=i*0.017453292519943295769236907684886;
      myGLCD.invPixel(i, (sin(y*6)*20)+23);
      myGLCD.update();
      delay(20);
    }
  }

  delay(2000);

  for (int pc=0; pc<3; pc++)
  {
    pacy=random(0, 28);
  
    for (int i=-20; i<84; i++)
    {
      tft.fillScreen (ILI9341_Black);
      for (int p=4; p>((i+20)/20); p--)
//        tft.drawBitmap(p*20-8, pacy+7, pill, 5, 5);
      switch(((i+20)/3) % 4)
      {
        case 0: bm=pacman1;
                break;
        case 1: bm=pacman2;
                break;
        case 2: bm=pacman3;
                break;
        case 3: bm=pacman2;
                break;
      }
      tft.drawBitmap(i, pacy, bm, 20, 20);
      tft.update();
      delay(25);
    }
  }
for (int i=0; i<25; i++)
{
    tft.fillScreen (ILI9341_WHITE);
//    tft.drawBitmap(0, 24, The_End, 84, 24);
//    tft.drawBitmap (10, 26, 84, 84, The_End);
    tft.update();
    delay(100);
  }
  tft.setFont(SmallFont);
  tft.print("Runtime (ms):", CENTER, 32);
  tft.printNumI(millis(), CENTER, 40);
 tft.update();
  for (int i=0; i<5; i++)
  {
    tft.invert(true);
    delay(1000);
    tft.invert(false);
    delay(1000);
  }
}
 
