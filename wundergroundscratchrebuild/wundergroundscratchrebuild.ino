#include <functional>
#include <algorithm>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <SPI.h>
//#include "memorysaver.h";
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <UTFT.h>
#include <Time.h>
#include <Timer.h>
//#include <Ticker.h>
//#include <JsonListener.h>
//#include "SSD1306Wire.h"
//#include "OLEDDisplayUi.h"
//#include "Wire.h"
//#include "WundergroundClient.h"
//#include "TimeClient.h"
//#include "ThingspeakClient.h"

//******Define Screen Pins**********
// Modify the line below to match your display and wiring:
//UTFT(byte model, int RS, int WR, int CS, int RST, int DC);
//in UTFT, RS is the data (MOSI), WR is the clock (SCK)
//UTFT myGLCD ( ST7735, 13, 14, 5, 4, 2 );//serial_SW ********Garbled
UTFT myGLCD ( ST7735, 5, 4, 2 );//Serial_HW****use the hardware SPI pins for SCK and MOSI (GPIO14 and GPIO13 


// WIFI
const char* WIFI_SSID = "PLUSNET-9P9QR6";//Turned off trying wifi persistance
const char* WIFI_PWD = "3bb7bc7cd3";
//const char* WIFI_SSID = "TNCAPC2653F";
//const char* WIFI_PWD = "A7252C69DF";


// Display Settings Oled
//const int I2C_DISPLAY_ADDRESS = 0x3c;
//const int SDA_PIN = 0;
//const int SDC_PIN = 2;

// Use hardware SPI (on ESP8266, #13, #12, #11)
//Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
#define LOCATIONID "UK/St_Austell" // location id
#define DST_IP "23.222.152.140" //api.wunderground.com

// TimeClient settings
const float UTC_OFFSET = 1;

// Wunderground Settings
const boolean IS_METRIC = true;
const String WUNDERGRROUND_API_KEY = "0e1262cc5f6a4bf9";
const String WUNDERGRROUND_LANGUAGE = "ENG";
const String WUNDERGROUND_COUNTRY = "UK";
const String WUNDERGROUND_CITY = "St_Austell";
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
// 5 minutes between update checks. The free developer account has a limit
// on the  number of calls so don't go wild.
#define DELAY_NORMAL    (5*60*1000)
// 20 minute delay between updates after an error
#define DELAY_ERROR     (20*60*1000)
#define WU_API_KEY "0e1262cc5f6a4bf9"
#define WUNDERGROUND "api.wunderground.com"
// Country and city
#define WU_LOCATION "UK/St_Austell"
#ifndef min
#define min(x,y) (((x)<(y))?(x):(y))
#endif
#ifndef max
#define max(x,y) (((x)>(y))?(x):(y))
#endif
#include <ArduinoJson.h>
// HTTP request
const char WUNDERGROUND_REQ[] =
    "GET /api/" WU_API_KEY "/conditions/q/" WU_LOCATION ".json HTTP/1.1\r\n"
    "User-Agent: ESP8266/0.1\r\n"
    "Accept: */*\r\n"
    "Host: " WUNDERGROUND "\r\n"
    "Connection: close\r\n"
    "\r\n";

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

//Function Prototypes************************************
void parseJSON(char json[400])
{
  Serial.println(json);
  StaticJsonBuffer<buffer> jsonBuffer;
 JsonObject& root = jsonBuffer.parseObject(json);
 
 if (!root.success())
{
  Serial.print("?fparseObject() failed");
  return;
} 
}
void getConds()
{
   
  //End Me  
 // Serial.println("AT+CWJAP?"); //Check network connection. If you disconnected, reconnect for AP
  //if (Serial.find("ERROR")){
   // Serial.println("Reconnect for AP");
   // espLogin();}
  //espLogin();
WiFiClient client;
  client.println("AT+CIPMUX=0"); // set to single connection mode
  Serial.println("Connection Mode Single");
  
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += DST_IP;
  cmd += "\",80";
  client.println(cmd);
  client.println(cmd);
  if(Serial.find("ERROR")) return;
  Serial.println("Line 126 Wifi Client");
 // cmd = "GET /api/9021af226189803f/conditions/q/";//authors
   cmd = "GET /api/0e1262cc5f6a4bf9/conditions/q/";
  cmd += LOCATIONID;
  cmd +=".json";
  cmd += " HTTP/1.1\r\nHost: api.wunderground.com\r\n\r\n";
  client.print("AT+CIPSEND=");
  client.println(cmd.length());
  if(Serial.find(">")){
  Serial.println(">");
  }else{
    client.println(F("AT+CIPCLOSE"));
    Serial.println("Connection timeout");
    delay(1000);
    getConds();
  }
  client.print(cmd);
  client.print(cmd);
  unsigned int i = 0; //timeout counter
  char json[buffer]="{"; // array for Json parsing
  int n = 1;          // character counter for json  
  
  for (int j=0;j<num_elements;j++){
    while (!Serial.find(conds[j])){} // find the part we are interested in.
  
    String Str1 = conds[j];
  
    for (int l=0; l<(Str1.length());l++)
        {json[n] = Str1[l];
         n++;}   
    while (i<60000) {
      if(Serial.available()) {
        char c = Serial.read();
         
          if(c==',') break;
          json[n]=c;
          n++;
          i=0;
        }
        i++;
      }
     if (j==num_elements-1)
        {json[n]=close_brace;}
     else   
        {json[n]=comma;}
     n++;   
  }

parseJSON(json);



// Done with processing for now - close connection
client.println("AT+CIPCLOSE");
//Serial1.println("AT+CWQAP"); // If you like disconnect AP, uncomment this line

 

}

// modtohere

time_t requestSync()
{
  
  setTime(ntpTime);// Need to check see line 310 also
  return 0;
}

void dayIconFix()
{
  int i;
  
  for (i = 0; i < 40; i++)
  {
    
    if (strcmp (iconName, iconArray[i])==0) {i=i+1; sdFileName = "w"; sdFileName +=i; sdFileName += ".raw"; break;}
      
  }
    
}
void parseForecastJSON(char json[400])
  {
    Serial.println(json);
    StaticJsonBuffer<buffer> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(json);
    
    if (!root.success())
    {
      Serial.print("?fparseObject() failed");
//      getForecast();
    }
    const char* celsius_h_0 = root["celsius_h_0"];
    const char* celsius_l_0 = root["celsius_l_0"];
    const char* icon_0 = root["icon_0"];
    int pop_0 = root["pop_0"];
    const char* celsius_h_1 = root["celsius_h_1"];
    const char* celsius_l_1 = root["celsius_l_1"];
    const char* icon_1 = root["icon_1"];
    int pop_1 = root["pop_1"];
    const char* celsius_h_2 = root["celsius_h_2"];
    const char* celsius_l_2 = root["celsius_l_2"];
    const char* icon_2 = root["icon_2"];
    int pop_2 = root["pop_2"];
    const char* celsius_h_3 = root["celsius_h_3"];
    const char* celsius_l_3 = root["celsius_l_3"];
    const char* icon_3 = root["icon_3"];
    int pop_3 = root["pop_3"];
    
    myGLCD.setBackColor(VGA_NAVY);
    myGLCD.setColor(VGA_RED);
    myGLCD.setFont(Inconsola);
    String day1 = String(celsius_l_1) + "/" + String(celsius_h_1) + "`";
    String day2 = String(celsius_l_2) + "/" + String(celsius_h_2) + "`";
    String day3 = String(celsius_l_3) + "/" + String(celsius_h_3) + "`";
    String day0 = String(celsius_l_0) + "`/" + String(celsius_h_0) + "`";
    
    myGLCD.print("      ", 8, 294);
    myGLCD.print(day1, 8, 294);
    myGLCD.print("      ", 162, 294);
    myGLCD.print(day2, 162, 294);
    myGLCD.print("      ", 318, 294);
    myGLCD.print(day3, 318, 294);
    myGLCD.setBackColor(VGA_BLACK);
    myGLCD.print("      ", 358, 120);
    myGLCD.print(day0, 358, 120);
    //icon names
    //char iconName;
    Serial.println(pop_2);
    iconName = (icon_0);
    dayIconFix();
//    myFiles.loadBitmap(358, 170, 150, 110, (sdFileName));//Disabled by me
    Serial.println(sdFileName);
    iconName = (icon_1);
    dayIconFix();
//    myFiles.loadBitmap(8, 360, 150, 110, (sdFileName));//Disabled by me
    Serial.println(sdFileName);
    iconName = (icon_2);
    dayIconFix();
    Serial.println(sdFileName);
  //  myFiles.loadBitmap(164, 360, 150, 110, (sdFileName));
    iconName = (icon_3);
    dayIconFix();
    Serial.println(sdFileName);
  //  myFiles.loadBitmap(320, 360, 150, 110, (sdFileName));
    
    myGLCD.setColor(255,210,0);
    if (pop_0 > 0)
    {
      myGLCD.setFont(arial_normal);
      myGLCD.drawBitmap (358, 150, 16, 16, rain);
      myGLCD.print("%   ", 378, 150);
      myGLCD.printNumI(pop_0, 398, 150);
    }
    if (pop_1 > 0)
       {
         myGLCD.setFont(arial_normal);
         myGLCD.drawBitmap (8, 344, 16, 16, rain);
         myGLCD.print("%   ", 28, 344);
         myGLCD.printNumI(pop_1, 48, 344);
       }
       
      if (pop_2 > 0)
      {
        myGLCD.setFont(arial_normal);
        myGLCD.drawBitmap (164, 344, 16, 16, rain);
        myGLCD.print("%   ", 184, 344);
        myGLCD.printNumI(pop_2, 204, 344);
      }
    
     if (pop_3 > 0)
     {
       myGLCD.setFont(arial_normal);
       myGLCD.drawBitmap (320, 344, 16, 16, rain);
       myGLCD.print("%   ", 340, 344);
       myGLCD.printNumI(pop_3, 360, 344);
     }
    myGLCD.setColor(VGA_RED);
  }




bool showWeather(char *json)
{
  StaticJsonBuffer<3*1024> jsonBuffer;

  // Skip characters until first '{' found
  // Ignore chunked length, if present
  char *jsonstart = strchr(json, '{');
  //Serial.print(F("jsonstart ")); Serial.println(jsonstart);
  if (jsonstart == NULL) {
    Serial.println(F("JSON data missing"));
    return false;
  }
  json = jsonstart;

  // Parse JSON
  JsonObject& root = jsonBuffer.parseObject(json);
  if (!root.success()) {
    Serial.println(F("jsonBuffer.parseObject() failed"));
    return false;
  } 
   // Extract weather info from parsed JSON
  JsonObject& current = root["current_observation"];
  const float temp_f = current["temp_f"];
  Serial.print(temp_f, 1); Serial.print(F(" F, "));
  const float temp_c = current["temp_c"];
  Serial.print(temp_c, 1); Serial.print(F(" C, "));
  const char *humi = current[F("relative_humidity")];
  Serial.print(humi);   Serial.println(F(" RH"));
  const char *weather = current["weather"];
  Serial.println(weather);
  const char *pressure_mb = current["pressure_mb"];
  Serial.println(pressure_mb);
  const char *observation_time = current["observation_time_rfc822"];
  Serial.println(observation_time);

  // Extract local timezone fields
  const char *local_tz_short = current["local_tz_short"];
  Serial.println(local_tz_short);
  const char *local_tz_long = current["local_tz_long"];
  Serial.println(local_tz_long);
  const char *local_tz_offset = current["local_tz_offset"];
  Serial.println(local_tz_offset);
  return true;
  delay(1000);
}

// }
    
  // void getForecast() {//me
// Serial.println("Getting Forecast line 315");
  //unsigned int i = 0; //timeout counter
  //char json[buffer]="{"; // array for Json parsing
  //  int n = 1;          // character counter for json
    
    //    while (!Serial.find("\"simpleforecast\": {")) {}
       
    //for (int j=0;j<num_elements_fr;j++){
      //while (!Serial.find(forecast[j])){} // find the part we are interested in.
      
      //String Str1 = forecast_rename[j];
      
     // for (int l=0; l<(Str1.length());l++)
     // {json[n] = Str1[l];
     // n++;}
     // while (i<60000) {
      //  if(Serial.available()) {
       //   char c = Serial1.read();
         // if (c== ',') {break;}
          //if(c== '}') {n--;n--;n--;break;}
            
         // json[n]=c;
         // n++;
         // i=0;
       // }
       // i++;
     // }
     // if (j==num_elements_fr-1)
     // {   
        
      //  json[n]=close_brace;
    
     // }
     // else
     // {json[n]=comma;}
     // n++;
   // }

   // parseForecastJSON(json);
    
  //  Serial.println("AT+CIPCLOSE"); //was commented out db***********************
   // delay(500);
   // getConds();
  //}
 
 

void refreshTimePrint()
{

//int hour = 0;//me
myGLCD.setBackColor(VGA_BLACK);
myGLCD.setColor(VGA_LIME);
myGLCD.setFont(arial_normal);
myGLCD.drawBitmap (518, 316, 16, 16, refresh);
String refreshTime;

if (hour()<10)
refreshTime=refreshTime+"0";
refreshTime=refreshTime+String(hour());
refreshTime=refreshTime+":";
if (minute()<10)
refreshTime=refreshTime+"0";
refreshTime=refreshTime + String(minute());
myGLCD.print(refreshTime, 538, 316);
Serial.println(refreshTime);

}

void drawArrow(float m)
{
  float x1, y1, x2, y2, x3, y3, x4, y4;
  int pm = m-1;
  
  myGLCD.setColor(0, 0, 0);
  if (pm==-1)
  pm=59;
  pm=pm*6;
  pm=pm+270;
  
  x1=80*cos(pm*0.0175);
  y1=80*sin(pm*0.0175);
  x2=5*cos(pm*0.0175);
  y2=5*sin(pm*0.0175);
  x3=30*cos((pm+4)*0.0175);
  y3=30*sin((pm+4)*0.0175);
  x4=30*cos((pm-4)*0.0175);
  y4=30*sin((pm-4)*0.0175);
  
  myGLCD.setColor(0, 255, 0);
  m=m*6;
  m=m+270;
  
  x1=80*cos(m*0.0175);
  y1=80*sin(m*0.0175);
  x2=5*cos(m*0.0175);
  y2=5*sin(m*0.0175);
  x3=30*cos((m+4)*0.0175);
  y3=30*sin((m+4)*0.0175);
  x4=30*cos((m-4)*0.0175);
  y4=30*sin((m-4)*0.0175);
  
  myGLCD.drawLine(x1+windGaugePanelX, y1+windGaugePanelY, x3+windGaugePanelX, y3+windGaugePanelY);
  myGLCD.drawLine(x3+windGaugePanelX, y3+windGaugePanelY, x2+windGaugePanelX, y2+windGaugePanelY);
  myGLCD.drawLine(x2+windGaugePanelX, y2+windGaugePanelY, x4+windGaugePanelX, y4+windGaugePanelY);
  myGLCD.drawLine(x4+windGaugePanelX, y4+windGaugePanelY, x1+windGaugePanelX, y1+windGaugePanelY);
}

void drawGaugeLines(float s)
{
  s = (s-0.1);
  float x1, y1, x2, y2;
  int ps = s-1;
  
  myGLCD.setColor(0, 0, 0);
  if (ps==-1)
  ps=59;
  ps=ps*6;
  ps=ps+270;
  
  x1=95*cos(ps*0.0175);
  y1=95*sin(ps*0.0175);
  x2=80*cos(ps*0.0175);
  y2=80*sin(ps*0.0175);
  
  myGLCD.setColor(0, 0, 0);
  s=s*6;
  s=s+270;
  
  x1=65*cos(s*0.0175);
  y1=65*sin(s*0.0175);
  x2=30*cos(s*0.0175);
  y2=30*sin(s*0.0175);
  
  myGLCD.drawLine(x1+windGaugePanelX, y1+windGaugePanelY, x2+windGaugePanelX, y2+windGaugePanelY);
}
 void drawGaugePanel()
{
//Wind gauge panel
myGLCD.setColor(VGA_NAVY);
myGLCD.fillCircle(670, 120, 110);
myGLCD.setColor(VGA_RED);
myGLCD.fillCircle(670, 120, 70);
myGLCD.setColor(VGA_SILVER);
myGLCD.fillCircle(670, 120, 5);

for (float i = 0; i < 60; i+=7.5)
{
  drawGaugeLines(i);
  }


myGLCD.setBackColor(VGA_TRANSPARENT);
myGLCD.setColor(VGA_SILVER);
myGLCD.setFont(Inconsola);
myGLCD.print("N", 660,18);
myGLCD.print("NE", 728,38,47);
myGLCD.print("E", 750,110);
myGLCD.print("SE", 705,195,-48);
myGLCD.print("S", 660,200);
myGLCD.print("SW", 600,160,47);
myGLCD.print("W", 568,110);
myGLCD.print("NW", 586,58,-42);
  }
    
void digitalClockDisplay(){
  myGLCD.setColor(255,0,0);
  
  String timp,data, data_w;
  
  if (hour()<10)//Not working
  timp=timp+"0";
  timp=timp+String(hour());// not working
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


//void t.update();
// Set to false, if you prefere imperial/inches, Fahrenheit
//WundergroundClient wunderground(IS_METRIC);

//char junk; // for compilitaion of functions force the IDE to put all the function definitions at the top
void setup() {
  WiFiClient client;
   myGLCD.InitLCD();
   myGLCD.clrScr();
   myGLCD.setFont(Inconsola);
   myGLCD.setColor(VGA_RED);
//   file.initFAT();// Disabled by me
   //Serial = SERIAL_OUT;
  Serial.begin(9600);
// WiFi.begin();//(WIFI_SSID, WIFI_PWD);//WiFi persistence
WiFi.begin(WIFI_SSID, WIFI_PWD);
  int counter = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    //tft.fillScreen(ILI9341_BLACK);
    //tft.setTextColor(ILI9341_YELLOW); tft.setTextSize(2);
    Serial.println("Connecting to WiFi");
    //    tft.println(WIFI_SSID);//wifi persistence
    Serial.println(WIFI_SSID);
     counter++;

  }
  Serial.println("");
  Serial.print("Local IP: ");
  Serial.println(WiFi.localIP());
  delay(1000);

//********End WiFi setup
//  getForecast();  // Line 425
  t.every(10000, digitalClockDisplay);//every 500ms display the clock
//  digitalClockDisplay();
//  t.every(50000, sensorRead);
//  t.every(900000, getConds);
  t.every(6000000, getForecast);
//}

  
void loop() {
  
t.update();
//getForecast();
}


