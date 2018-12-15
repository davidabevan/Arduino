/*  
 Gilchrist 6/2/2014 1.0
 Updated by Alan Senior 18/1/2015
 Updated by Roger Schaefer to use NTP June 2015
 */
///////////////////////////////////////////////////////////////////////////////////////////
//       This version uses the Timezone library to set timezone and daylight savings time
///////////////////////////////////////////////////////////////////////////////////////////
/*
// These are the connections for the UNO
#define sclk 13  // Don't change
#define mosi 11  // Don't change
#define cs   10
#define dc   9
#define rst  7  // you can also connect this to the Arduino reset */
#include <SPI.h>
#include "Ucglib.h"           //  http://code.google.com/p/ucglib/
#include <Time.h>              // http://www.arduino.cc/playground/Code/Time
#include <Timezone.h>          // https://github.com/JChristensen/Timezone

Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);  //  TFT-Pro Ver 1

/*  US Eastern Time Zone (New York, Detroit)
TimeChangeRule myDST = {"EDT", Second, Sun, Mar, 2, -240};    //Daylight time = UTC - 4 hours
TimeChangeRule mySTD = {"EST", First, Sun, Nov, 2, -300};     //Standard time = UTC - 5 hours
Timezone myTZ(myDST, mySTD);
*/

//US Central Time Zone (Chicago, St. Louis)
TimeChangeRule myDST = {"CDT", Second, Sun, Mar, 2, -300};    //Daylight time = UTC - 5 hours
TimeChangeRule mySTD = {"CST", First, Sun, Nov, 2, -360};     //Standard time = UTC - 6 hours
Timezone myTZ(myDST, mySTD);

TimeChangeRule *tcr;        //pointer to the time change rule, use to get TZ abbrev
time_t utc, local;
ucg_int_t   x, y, StrWidth;
char DateStr[40] ;
String Date;
int previousDay = 0;
int previousTime = 61;

#define TIME_HEADER  "T"   // Header tag for serial time sync message
#define TIME_REQUEST  7    // ASCII bell character requests a time sync message
#define LED 13

void setup(void) {
  Serial.begin(9600);  
  pinMode(LED, OUTPUT);
  ucg.begin(UCG_FONT_MODE_SOLID);  ucg.setRotate270();
  delay(1000);  
  waitToSync();
  drawFrame();  
}
//-----------------------------------------------------------End Setup
//////////////////////////////////////////////////////////////////////
void loop() {
  if (previousTime != minute()) DisplayTime(now());
  printSeconds(now());
  if (previousDay != day()) displayDate(now());
  processSyncMessage();  
}
//-----------------------------------------------------------End Loop
/////////////////////////////////////////////////////////////////////
static uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}
//--------------------------------------------------------
void processSyncMessage() {
  unsigned long pctime;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     if( pctime >= DEFAULT_TIME) { // check the integer is a valid time (greater than Jan 1 2013)
       //setTime(pctime); // Sync Arduino clock to the time received on the serial port
       setTime(myTZ.toLocal(pctime));
     }
  }
}
//-------------------------------------------------Print time
void DisplayTime(time_t t){
  previousTime = minute();
  ucg.setFontMode(UCG_FONT_MODE_SOLID);  ucg.setRotate270();
  //y = 182;  ucg.setPrintPos(40,y);  // was 52
  ucg.setColor(0x41, 0x69, 0xff);   // light blue
  ucg.setFont(ucg_font_logisoso62n);
  
  if (((second(t)) < 5) && (minute(t)) < 1)
  {
   box();  //  draw a box of background color to remove old leading digit
   ucg.setColor(0x41, 0x69, 0xff);   // light blue
  };
  
  if (hourFormat12(t) < 10){
    y = 182;  ucg.setPrintPos(80,y);
  }
  else {
    y = 182;  ucg.setPrintPos(40,y);
  };
  ucg.print(hourFormat12(t));
  printDigits(minute());   
  //printSeconds(now());
  
  ucg.setPrintPos(250,150);
  ucg.setFont(ucg_font_logisoso20);
  if (isAM()) ucg.print("am");
  else ucg.print("pm");
}
//------------------------------------------------------------------
void printSeconds(time_t t){
  ucg.setFont(ucg_font_logisoso20); 
  ucg.setPrintPos(237,180);
  printDigits(second());
}
  
//------------------------------------------------------------------
//---------------blink led to indicate power up
void FastBlink(){
  for(int i = 0; i<15; i++)
  {
    digitalWrite(LED,HIGH);
    delay(50);
    digitalWrite(LED,LOW);
    delay(50);
  }
}
///////////////////////////////////////
void crlf(){
  y = y + ucg.getFontAscent() - ucg.getFontDescent();
  if (y > (245-ucg.getFontAscent())) y = (248 - ucg.getFontAscent()) ;
  y = y + 1;
  ucg.setPrintPos(0, y );
}
///////////////////////////////////////
void center(ucg_int_t Str){
  x = ( 160 - (Str/2));
  ucg.setPrintPos(x, y);
}
////////////////////////////////////////
void box()
{
  ucg.setColor(0, 0, 0);   //   black
  //ucg.setColor(193, 240, 193);  //  light green
  // Box is x, y, width, height
  ucg.drawBox(50, 120, 50, 62);
}
//-------------------------------------------------Format Digits
void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  ucg.print(":");
  if(digits < 10)
    ucg.print('0');
  ucg.print(digits);
}
//---------------------------------------------
void waitToSync(){
  if(timeStatus()!= timeSet) 
     Serial.println("Waiting to sync with NTP");
  else
     Serial.println("NTP has set the system time");
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);  
  ucg.clearScreen();
  ucg.setRotate270(); 
  ucg.setFont(ucg_font_helvB18);
  ucg.setColor(0, 255, 255, 255);
  ucg.setPrintPos(0,125);
  ucg.print("Waiting to sync with NTP");
  ucg.begin(UCG_FONT_MODE_SOLID);
  while (timeStatus()!= timeSet){
  processSyncMessage();
  }
  ucg.clearScreen();
  if(timeStatus()!= timeSet) 
     Serial.println("Waiting to sync with NTP");
  else
     Serial.println("NTP has set the system time");
}
//---------------------------------------------
void displayDate(time_t t){
  previousDay = day();
  ucg.setFontMode(UCG_FONT_MODE_SOLID);  ucg.setRotate270();
  ucg.setFont(ucg_font_helvB18);
  ucg.setColor(255, 255, 255);
  crlf();
  Date = (monthStr(month(t)));
  Date = Date + ' ';
  Date = Date + (day(t));
  Date = Date + ", ";
  Date = Date + (year(t));
  Date = "     " + Date + "     ";
  Date.toCharArray(DateStr, 35);
  StrWidth = ucg.getStrWidth(DateStr);
  center(StrWidth);
  ucg.print(Date);
  crlf();  y++;
  
  ucg.setColor(0, 00, 255, 255);   // CYAN
  ucg.print("                        ");
  StrWidth = ucg.getStrWidth(dayStr(weekday()));
  center(StrWidth);
  ucg.print(dayStr(weekday()));
  ucg.print("     ");
  ucg.setColor(1,0,0,0);
}
//---------------------------------------------
void drawFrame(){
  ucg_int_t w = 320;
  ucg_int_t h = 100;
  String message = "Space for Rent";
  ucg.setRotate270();
  ucg.drawFrame(x,  y,  w,  h);
  ucg.setColor(0, 255, 0, 0);
  ucg.setFontMode(UCG_FONT_MODE_SOLID);
  ucg.setFont(ucg_font_helvB24);
  y = 62;
  message.toCharArray(DateStr, 35);
  StrWidth = ucg.getStrWidth(DateStr);
  center(StrWidth);
  ucg.print(message);
}
