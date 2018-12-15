// UTFT_Bitmap 
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of the drawBitmap()-function.
//
// This demo was made to work on the 320x240 modules.
// Any other size displays may cause strange behaviour.
//
// This program requires the UTFT library.
//
#include <pgmspace.h>
#include <UTFT.h>
#include<SPI.h>
// Declare which fonts we will be using
extern uint8_t SmallFont[];
UTFT myGLCD ( ILI9341_S5P, 5, 4, 2 );
//extern unsigned int star[0x400];
//extern unsigned int wifibmap[0x400];
//extern unsigned int bat1[0x400];
extern unsigned int startrek[0x3E04];
extern unsigned int firework[0x400];
extern unsigned int christmas_tree[0x400];
extern unsigned int haloween[0x100];
//extern unsigned int download
void setup()
{
  myGLCD.InitLCD();
  myGLCD.setFont(SmallFont);
}

void loop()
{
  myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(255, 255, 255);
 
  //  delay(5000);
    // myGLCD.fillScr(255, 255, 255);
     myGLCD.drawBitmap (97, 57, 126, 126, startrek );
     delay(5000);
    //   myGLCD.fillScr(255, 255, 255);
   
    // delay(5000);
    }
