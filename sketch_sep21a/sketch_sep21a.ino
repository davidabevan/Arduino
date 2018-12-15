#include <WiFiManager.h>

#include <memorysaver.h>
#include <UTFT.h>
extern uint8_t SmallFont[];
UTFT myGLCD ( ILI9341_S5P, 5, 4, 2 );

void setup() {
  // put your setup code here, to run once:
 myGLCD.InitLCD (  );
    myGLCD.setFont ( SmallFont );
}

void loop() {
  // put your main code here, to run repeatedly:
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

    myGLCD.setColor ( 0, 0, 255 );
    myGLCD.drawRect ( 0, 14, 319, 225 );

    // Draw crosshairs
    myGLCD.setColor ( 0, 0, 255 );
    myGLCD.setBackColor ( 0, 0, 0 );
    myGLCD.drawLine ( 159, 15, 159, 224 );
    myGLCD.drawLine ( 1, 119, 318, 119 );
    for ( int i = 9; i < 310; i += 10 )
        myGLCD.drawLine ( i, 117, i, 121 );
    for ( int i = 19; i < 220; i += 10 )
        myGLCD.drawLine ( 157, i, 161, i );

    yield (  );
}
