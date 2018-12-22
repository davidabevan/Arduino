// DS3231_Serial_Easy
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// A quick demo of how to use my DS3231-library to 
// quickly send time and date information over a serial link
//
// To use the hardware I2C (TWI) interface of the Arduino you must connect
// the pins as follows:
//
// Arduino Uno/2009:
// ----------------------
// DS3231:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//          SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
//
// Arduino Leonardo:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 2 or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 3 or the dedicated SCL pin
//
// Arduino Mega:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
//
// Arduino Due:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA1 (Digital 70) pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL1 (Digital 71) pin
//
// The internal pull-up resistors will be activated when using the 
// hardware I2C interfaces.
//
// You can connect the DS3231 to any available pin but if you use any
// other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
//

 

// Init the DS3231 using the hardware interface  
#include <DS3231.h>

DS3231  rtc(SDA, SCL);

#include "SPI.h"
//#include "Adafruit_GFX.h"
//#include "Adafruit_ILI9340.h"
#include <Adafruit_GFX_AS8.h>    // Core graphics library
#include <Adafruit_ILI9341_AS8.h> // Hardware-specific library

#include "Wire.h"
//#include "ds3231.h"
#include "DS3231.h"


#define BUFF_MAX 128

uint8_t time[8];
char recv[BUFF_MAX];
unsigned int recv_size = 0;
unsigned long prev, interval = 1000;

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// These are the pins used for the arduino pro mini
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define  BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
// Using software SPI is really not suggested, its incredibly slow
//Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _mosi, _sclk, _rst, _miso);
// Use hardware SPI
//Adafruit_ILI9340 tft = Adafruit_ILI9340(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
Adafruit_ILI9341_AS8 tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
void setup() {
  
   
    Serial.println("GET time");
    tft.begin();
    tft.fillScreen(ILI9341_BLUE);
    tft.setRotation(3);


  // Setup Serial connection
  Serial.begin(115200);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  
  // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
  //rtc.setDOW(MONDAY);     // Set Day-of-Week to SUNDAY
 // rtc.setTime(15, 45, 30);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(4, 11, 2016);   // Set the date to January 1st, 2014
}

void loop()
{
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
 tft.setTextColor(ILI9341_WHITE, ILI9341_BLUE);
        tft.setTextSize(2);
        tft.setCursor(15, 10);
        tft.print("Today is");
        tft.setCursor(120, 10);
        tft.print(rtc.getDateStr());
        
         tft.setTextSize(3);
        tft.setCursor(35, 50);
        tft.print("ARDUINO CLOCK");
         
        tft.setTextSize(1);
        tft.setCursor(100, 200);
        tft.print("www.miniarduino.com");
         /////////////////////// TEMPERATURE /////////////////
        tft.setCursor(30, 220); //Go to last line of the LCD Screen
        tft.setTextSize(2);
        tft.print("Temperature: ");
        tft.setCursor(180, 220); 
//        tft.print(tempF);
        //tft.print((char)223);
        tft.print(" C");
//        prev = now;
  // Send time
  Serial.println(rtc.getTimeStr());
     ///////////////////////// TIME //////////////////////
        tft.setCursor(35, 100);
        tft.setTextSize(5);
       // tft.print(t.hour);
       tft.println(rtc.getTimeStr());
        //////////////////////// WEEK DAY ////////////////////
        tft.setTextSize(3);
        tft.setCursor(80, 150);
       //tft.printWeekday(t.wday); // day name
      // tft.print(t.wday);
        tft.print(rtc.getDOWStr());
  
  // Wait one second before repeating :)
  delay (1000);
}
