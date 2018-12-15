/*
 An example startup on a 2.2" ILI9341 TFT 240x320
 colour screen
 
 

 This example uses the hardware SPI and a board based on the ATmega328
 such as an UNO.  If using a Mega or outher micocontroller then comment out
 the following line:
 #define F_AS_T
 in  the "Adafruit_ILI9341_FAST.h" found within the Adafruit_ILI9341_AS
 library folder. Change pins for other Arduinos to the hardware SPI pins.

 Needs Fonts 2, and 4 (also Font 6 if using a large size meter)

 Alan Senior 18/3/2015
 */

// These are the connections from the UNO to the display
#define sclk 13  // Don't change
#define mosi 11  // Don't change
#define cs   10  // If cs and dc pin allocations are changed then 
#define dc   9   // comment out #define F_AS_T line in "Adafruit_ILI9341_FAST.h"
// (which is inside "Adafriit_ILI9341_AS" library)

#define rst  7  // Can alternatively connect this to the Arduino reset

// Meter colour schemes
#define RED2RED 0
#define GREEN2GREEN 1
#define BLUE2BLUE 2
#define BLUE2RED 3
#define GREEN2RED 4
#define RED2GREEN 5
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#include <Adafruit_GFX_AS.h>     // Core graphics library
#include <Adafruit_ILI9341_AS.h> // Fast hardware-specific library
#include <SPI.h>

#define ILI9341_GREY 0x2104 // Dark grey 16 bit colour

Adafruit_ILI9341_AS tft = Adafruit_ILI9341_AS(cs, dc, rst); // Invoke custom library




void setup(void) {
  tft.init();

  tft.setRotation(3);

  tft.fillScreen(ILI9341_RED);
  
}


void loop() {
tft.setCursor(12, 112);   
tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(4);
  tft.println("Temp");  
}
