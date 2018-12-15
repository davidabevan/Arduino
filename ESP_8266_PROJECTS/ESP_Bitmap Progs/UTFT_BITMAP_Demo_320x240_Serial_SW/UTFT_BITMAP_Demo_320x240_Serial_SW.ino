// UTFT_Demo_320x240_Serial_SW
// Copyright (C)2015 Dimitris Lampridis. All right reserved
//
// based on original UTFT_Demo_320x240_Serial:
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// This program is a demo of how to use most of the functions
// of the library with a supported display module.
//
// This demo was made for serial modules with a screen
// resolution of 320x240 pixels.
//
// This demo implements the serial interface via software (bit-banging).
//
// This program requires the UTFT library.

// Requred for data transfer
#include <pgmspace.h>

//Setup Bitmap data array in Progmem
extern unsigned int startrek[0x3E04];
extern unsigned int jrt3030[1110];
extern unsigned int Fringe[0xAB90];
extern unsigned int Wifi[0xC458];

#include <UTFT.h>
#include <SPI.h> // not necessary if Arduino IDE version >=1.6.6

// Declare which fonts we will be using
extern uint8_t SmallFont[];

// Modify the line below to match your display and wiring:
UTFT myGLCD ( ILI9341_S5P, 13, 14, 5, 4, 2 );//SW Serial

void setup() {

    // Setup the LCD
    myGLCD.InitLCD (  );
    myGLCD.setFont ( SmallFont );

}

void loop (  ) {
   

    // Clear the screen and draw the frame
    myGLCD.clrScr (  );

    myGLCD.setColor ( 255, 0, 0 );
    myGLCD.fillRect ( 0, 0, 319, 13 );
    myGLCD.setColor ( 64, 64, 64 );
    myGLCD.fillRect ( 0, 226, 319, 239 );
    myGLCD.setColor ( 255, 255, 255 );
    myGLCD.setBackColor ( 255, 0, 0 );
    myGLCD.print ( String("* Universal Color TFT Display Library *"), CENTER, 1 );
    myGLCD.setBackColor ( 64, 64, 64 );
    myGLCD.setColor ( 255, 255, 0 );
    myGLCD.print ( String("<http://www.RinkyDinkElectronics.com/>"), CENTER, 227 );
     myGLCD.drawBitmap (69, 0 , 183, 240, Fringe, 1);
    delay ( 5000 );
    //Draw Bitmap from Progmem
    myGLCD.fillScr(255, 255, 255);
  myGLCD.setColor(255, 255, 255);
  //My maths centre startrek logo
  // X centre of display =160 y centre= 120 Pixels=126/2=63;;  160-63=97
  // Y centre=120-63=57
    myGLCD.drawBitmap (97, 57, 126, 126, startrek, 1);//Problems fixed see .c Tab
     delay(5000);
     myGLCD.drawBitmap (105, 80, 37, 30, jrt3030, 1);
     delay(5000);
       myGLCD.fillScr(255, 255, 255);
       myGLCD.drawBitmap (40, 17, 244, 206, Wifi);
       delay(5000);
}
