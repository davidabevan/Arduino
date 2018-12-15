#include <WiFiManager.h>

#include <memorysaver.h>
#include <UTFT.h>
//for Compass
int x, y;
int windGaugePanelX=671;
int windGaugePanelY=120;
extern uint8_t Inconsola[];
char* conds[]={"\"local_epoch\":","\"weather\":","\"temp_c\":","\"relative_humidity\":","\"wind_dir\":","\"wind_kph\":","\"pressure_mb\":","\"feelslike_c\":"};

/****************************
The MIT License (MIT)
Copyright (c) 2015 by bbx10node@gmail.com
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************/

//#include <ESP8266WiFi.h> Causes compilation faliure use
//WIFI Manager instead DB 21/09/2016
#ifndef min
#define min(x,y) (((x)<(y))?(x):(y))
#endif
#ifndef max
#define max(x,y) (((x)>(y))?(x):(y))
#endif
#include <ArduinoJson.h>
extern uint8_t SmallFont[];
UTFT myGLCD ( ILI9341_S5P, 5, 4, 2 );
const char SSID[]     = "PLUSNET-9P9QR6";
const char PASSWORD[] = "3bb7bc7cd3";

// Use your own API key by signing up for a free developer account.
// http://www.wunderground.com/weather/api/
#define WU_API_KEY "0e1262cc5f6a4bf9"

// Specify your favorite location one of these ways.
//#define WU_LOCATION "CA/HOLLYWOOD"

// US ZIP code
//#define WU_LOCATION ""
//#define WU_LOCATION "90210"

// Country and city
#define WU_LOCATION "UK/St_Austell"

// 5 minutes between update checks. The free developer account has a limit
// on the  number of calls so don't go wild.
#define DELAY_NORMAL    (5*60*1000)
// 20 minute delay between updates after an error
#define DELAY_ERROR     (20*60*1000)

#define WUNDERGROUND "api.wunderground.com"

// HTTP request
const char WUNDERGROUND_REQ[] =
    "GET /api/" WU_API_KEY "/conditions/q/" WU_LOCATION ".json HTTP/1.1\r\n"
    "User-Agent: ESP8266/0.1\r\n"
    "Accept: */*\r\n"
    "Host: " WUNDERGROUND "\r\n"
    "Connection: close\r\n"
    "\r\n";
//#include <UTFT.h>
//#include <SPI.h> // not necessary if Arduino IDE version >=1.6.6

// Declare which fonts we will be using
//extern uint8_t SmallFont[];

// Modify the line below to match your display and wiring:
//UTFT myGLCD ( ILI9341_S5P, 13, 14, 5, 4, 2 );

void setup()
{
   myGLCD.InitLCD();
   myGLCD.clrScr();
   myGLCD.setFont(Inconsola);
   myGLCD.setColor(VGA_RED);
   // Setup the LCD
   // myGLCD.InitLCD (  );
  //  myGLCD.setFont ( SmallFont );

  Serial.begin(9600);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(SSID);

  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  Serial.println();
  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());
}

static char respBuf[4096];

void loop()
{
  // TODO check for disconnect from AP

  // Open socket to WU server port 80
  Serial.print(F("Connecting to "));
  Serial.println(WUNDERGROUND);

  // Use WiFiClient class to create TCP connections
  WiFiClient httpclient;
  const int httpPort = 80;
  if (!httpclient.connect(WUNDERGROUND, httpPort)) {
    Serial.println(F("connection failed"));
    delay(DELAY_ERROR);
    return;
  }

  // This will send the http request to the server
  Serial.print(WUNDERGROUND_REQ);
  httpclient.print(WUNDERGROUND_REQ);
  httpclient.flush();

  // Collect http response headers and content from Weather Underground
  // HTTP headers are discarded.
  // The content is formatted in JSON and is left in respBuf.
  int respLen = 0;
  bool skip_headers = true;
  while (httpclient.connected() || httpclient.available()) {
    if (skip_headers) {
      String aLine = httpclient.readStringUntil('\n');
      //Serial.println(aLine);
      // Blank line denotes end of headers
      if (aLine.length() <= 1) {
        skip_headers = false;
      }
    }
    else {
      int bytesIn;
      bytesIn = httpclient.read((uint8_t *)&respBuf[respLen], sizeof(respBuf) - respLen);
      Serial.print(F("bytesIn ")); Serial.println(bytesIn);
      if (bytesIn > 0) {
        respLen += bytesIn;
        if (respLen > sizeof(respBuf)) respLen = sizeof(respBuf);
      }
      else if (bytesIn < 0) {
        Serial.print(F("read error "));
        Serial.println(bytesIn);
      }
    }
    delay(1);
  }
  httpclient.stop();

  if (respLen >= sizeof(respBuf)) {
    Serial.print(F("respBuf overflow "));
    Serial.println(respLen);
    delay(DELAY_ERROR);
    return;
  }
  // Terminate the C string
  respBuf[respLen++] = '\0';
  Serial.print(F("respLen "));
  Serial.println(respLen);
  //Serial.println(respBuf);

  if (showWeather(respBuf)) {
    delay(DELAY_NORMAL);
  }
  else {
    delay(DELAY_ERROR);
  }
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
 // const float temp_f = current["temp_f"];
 // Serial.print(temp_f, 1); Serial.print(F(" F, "));
 // const float temp_c = current["temp_c"];
 //// Serial.print(temp_c, 1); Serial.print(F(" C, "));
 // const char *humi = current[F("relative_humidity")];
 // Serial.print(humi);   Serial.println(F(" RH"));
 // const char *weather = current["weather"];
 // Serial.println(weather);
 // const char *pressure_mb = current["pressure_mb"];
 //  Serial.println(pressure_mb);
const char *windspeed = current ["wind_mph"];
Serial.print("WindSpeed ");
Serial.print(windspeed);
Serial.println(" MPH");
const char *windgust = current ["wind_gust_mph"];
Serial.print("Wind Gusting to ");
Serial.print(windgust);
Serial.println(" MPH");
const char* windtext = current ["wind_string"];
Serial.println(windtext);

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
}
//Wind Panel (Wind direction print)
 void compass(){
  char *wind_dir;
  int *wind_kph;
if (strcmp (wind_dir, "North")==0) {drawArrow(0) ;}
if (strcmp (wind_dir, "NNE")==0) {drawArrow(4.5) ;}
if (strcmp (wind_dir, "NE")==0) {drawArrow(7.5);}
if (strcmp (wind_dir, "ENE")==0) {drawArrow(12);}
if (strcmp (wind_dir, "East")==0) {drawArrow(15);}
if (strcmp (wind_dir, "ESE")==0) {drawArrow(19.5);}
if (strcmp (wind_dir, "SE")==0) {drawArrow(22.5);}
if (strcmp (wind_dir, "SSE")==0) {drawArrow(27);}
if (strcmp (wind_dir, "South")==0) {drawArrow(30);}
if (strcmp (wind_dir, "SSW")==0) {drawArrow(34);}
if (strcmp (wind_dir, "SW")==0) {drawArrow(37.5);}
if (strcmp (wind_dir, "WSW")==0) {drawArrow(41.5);}
if (strcmp (wind_dir, "West")==0) {drawArrow(45);}
if (strcmp (wind_dir, "WNW")==0) {drawArrow(49.5);}
if (strcmp (wind_dir, "NW")==0) {drawArrow(53);}
if (strcmp (wind_dir, "NNW")==0) {drawArrow(56) ;}
Serial.println(wind_dir);//me
myGLCD.setColor(0, 255, 0);

//if ((wind_kph) < 10) {myGLCD.print("  ", 596, 242);
  myGLCD.printNumI(wind_kph, 620, 242);
}
else {
myGLCD.printNumI(wind_kph, 596, 242);}
myGLCD.print("Km/h", 660, 242);
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
