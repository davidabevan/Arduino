#include <ArduinoJson.h>
#include <UTFT.h>
#include <Time.h>
#include <Timer.h>
//#include <tinyFAT.h>
//#include <UTFT_tinyFAT.h>
//#include "memorysaver.h" //if you use memorysaver.h must edit file. Inside UTFT Folder 

#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define SSID "PLUSNET-9P9QR6" // insert your SSID
#define PASS "3bb7bc7cd3" // insert your password
#define LOCATIONID "UK/St_Austell" // location id
#define DST_IP "23.222.152.140" //api.wunderground.com

// Modify the line below to match your display and wiring:
//UTFT(byte model, int RS, int WR, int CS, int RST, int DC);
//in UTFT, RS is the data (MOSI), WR is the clock (SCK)
//UTFT myGLCD ( ST7735, 13, 14, 5, 4, 2 );//serial_SW ********Garbled
UTFT myGLCD ( ST7735, 5, 4, 2 );//Serial_HW****use the hardware SPI pins for SCK and MOSI (GPIO14 and GPIO13 

extern uint8_t  BigFont[];
extern uint8_t Inconsola[];
extern uint8_t SevenSeg_XXXL_Num[];
extern uint8_t SevenSegmentFull[];
extern uint8_t arial_normal[];
//UTFT_tinyFAT myFiles(&myGLCD); // Disabled by me
extern unsigned int homett[0x1000];
extern unsigned int rain[0x100];
extern unsigned int refresh[0x100];


const int buffer=400;//JSON Buffer size

int windGaugePanelX=671;
int windGaugePanelY=120;

int passNum = 1;
long ntpTime;
Timer t;
double tmp;
String tmpl,tmpld;
const char* iconName;
String sdFileName;

// Array of desired weather conditions & forecast.
// These must be in the order received from wunderground api server.

char* conds[]={"\"local_epoch\":","\"weather\":","\"temp_c\":","\"relative_humidity\":","\"wind_dir\":","\"wind_kph\":","\"pressure_mb\":","\"feelslike_c\":"};
int num_elements = 8;  // number of conditions you are retrieving, count of elements in conds
int num_elements_fr = 16; // number of forecast you are retrieving, count of elements in forecast

char* forecast[]={"\"celsius\":","\"celsius\":","\"icon\":","\"pop\":","\"celsius\":","\"celsius\":","\"icon\":","\"pop\":","\"celsius\":","\"celsius\":","\"icon\":","\"pop\":","\"celsius\":","\"celsius\":","\"icon\":","\"pop\":"};
char* forecast_rename[]={"\"celsius_h_0\":","\"celsius_l_0\":","\"icon_0\":","\"pop_0\":","\"celsius_h_1\":","\"celsius_l_1\":","\"icon_1\":","\"pop_1\":","\"celsius_h_2\":","\"celsius_l_2\":","\"icon_2\":","\"pop_2\":","\"celsius_h_3\":","\"celsius_l_3\":","\"icon_3\":","\"pop_3\":"}; //rename for same data name.
char* weekdayNames[]={"Sunday   ", "Monday   ", "Tuesday  ", "Wednesday", "Thursday ", "Friday   ", "Saturday "};
char close_brace ='}';
char comma = ',';
char* iconArray[]={"chanceflurries", "chancerain", "chancesleet", "chancesnow", "chancestorms", "clear", "cloudy", "flurries", "fog", "hazy", "mostlycloudy", "mostlysunny", "nt_chanceflurries", "nt_chancerain", "nt_chancesleet", "nt_chancesnow", "nt_chancetstorms", "nt_clear", "nt_cloudy", "nt_flurries", "nt_fog", "nt_hazy", "nt_mostlycloudy", "nt_mostlysunny", "nt_partlycloudy", "nt_partlysunny", "nt_rain", "nt_sleet", "nt_snow", "nt_sunny", "nt_tstorms", "partlycloudy", "partlysunny", "rain", "sleet", "snow", "sunny", "tstorms"};

void setup() {
  
   myGLCD.InitLCD();
   myGLCD.clrScr();
   myGLCD.setFont(Inconsola);
   myGLCD.setColor(VGA_RED);
//   file.initFAT();// Disabled by me
   Serial.begin(9600); // Debug
  delay(1000);
 // getForecast(); 
  t.every(10000, digitalClockDisplay);//every 500ms display the clock
}

void loop() {
  t.update();


}


void digitalClockDisplay(){
  myGLCD.setColor(255,0,0);
  
  String timp,data, data_w;
  
  //if (hour()<10)//Not working
  timp=timp+"0";
//  timp=timp+String(hour());// not working
  timp=timp+":";
  if (minute()<10)
  timp=timp+"0";
  timp=timp + String(minute());
  char charBuf[12];
  myGLCD.setFont(SevenSeg_XXXL_Num); //64*100 pixels  
    timp.toCharArray(charBuf, 12) ;
    myGLCD.print(charBuf, 478, 375);
    myGLCD.setFont(arial_normal);
  int w = (weekday()- 1);
    data=String(day())+"/"+String(month())+"/"+String(year()); //+"/"+String(data_w);

    
    myGLCD.setColor(VGA_RED);
    
    myGLCD.print(data, RIGHT, 308);
    myGLCD.print(weekdayNames[w], RIGHT, 328);
    myGLCD.setColor(VGA_LIME);
    myGLCD.print(weekdayNames[w], 358, 94);
    w = (weekday());
    if (w > 6) {w = 0;}
    myGLCD.setBackColor(VGA_BLACK);
    //myGLCD.setColor(VGA_LIME);
    myGLCD.print(weekdayNames[w], 8, 324);
    w++;
    if (w >6) {w = 0;}
    myGLCD.print(weekdayNames[w], 164, 324);
    w++;
    if (w >6) {w = 0;}
    myGLCD.print(weekdayNames[w], 320, 324);
    
    
    myGLCD.setFont(Inconsola);
    myGLCD.setColor(VGA_RED);
    
     
     
}

