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
//start bbc
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192,168,1,17 };
byte gw[] = {192,168,1,1};
byte server[] = {212,58,226,143};
char worrd[32];
char target[7] = {'<', 't', 'i', 't', 'l', 'e', '>' };
char tolcd[80];
int counter = 0;
int lcdcount = 0;
int count = 0;
int foundcount = 0;
int linecount = 0;
boolean worded = true;
boolean taketext = false;
boolean tag = false;

int ledPin = 13;
//END bbc
#include <ESP8266WiFi.h>
#ifndef min
#define min(x,y) (((x)<(y))?(x):(y))
#endif
#ifndef max
#define max(x,y) (((x)>(y))?(x):(y))
#endif
#include <ArduinoJson.h>
const char* host = "http://feeds.bbci.co.uk/news/rss.xml";
//const char*host = "(74,125,232,128);";
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

//#define WUNDERGROUND "api.wunderground.com"
//http://feeds.bbci.co.uk/
//#define WUNDERGROUND "http://feeds.bbci.co.uk/news/rss.xml"
#define WUNDERGROUND "bbc.co.uk"
//#define WUNDERGROUND "open.live.bbc.co.uk"
//#define BBC "GET /rss/newsonline_uk_edition/front_page/rss.xml"
//#define WUNDERGROUND "newsrss.bbc.co.uk/rss/newsonline_uk_edition/front_page/rss.xml"
//#define WUNDERGROUND "http://open.live.bbc.co.uk/weather/feeds/en/2647937/observations.rss"
//#define WUNDERGROUND "http://feeds.bbci.co.uk"
//#define BBC "http://bbc.co.uk/"
// HTTP request
const char WUNDERGROUND_REQ[] =
   // "GET /api/" WU_API_KEY "/conditions/q/" WU_LOCATION ".json HTTP/1.1\r\n"
  // "GET /rss/newsonline_uk_edition/front_page/rss.xml HTTP/1.1\r\n" 
   "GET /open.live.bbc.co.uk/weather/feeds/en/2647937/observations.xml HTTP/1.1\r\n"
  //"GET /newsrss.bbc.co.uk/rss/newsonline_uk_edition/front"
    "User-Agent: ESP8266/0.1\r\n"
    "Accept: */*\r\n"
    "Host: " WUNDERGROUND "\r\n"
    "Connection: close\r\n"
    "\r\n";


// HTTP request BBC
//const char BBC_REQ[] =
//const char WUNDERGROUND_REQ[] =
// "GET /rss/newsonline_uk_edition/front_page/rss.xml HTTP/1.1\r\n" 
  //  "GET /api/" WU_API_KEY "/conditions/q/" WU_LOCATION ".json HTTP/1.1\r\n"
  //"GET /http://open.live.bbc.co.uk/weather/feeds/en/2647937/observations.rss"
   // "User-Agent: ESP8266/0.1\r\n"
   //"Accept: */*\r\n"
//   "Host: " BBC "\r\n"
    //"Host: " WUNDERGROUND "\r\n"
  // "Connection: close\r\n";
//    "\r\n";
void setup()
{
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
   WiFiClient httpclient;
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
Serial.println(respBuf);
  
  // TODO check for disconnect from AP

  // Open socket to WU server port 80
  Serial.print(F("Connecting to "));
  Serial.println(WUNDERGROUND);
//Serial.println(host);
  // Use WiFiClient class to create TCP connections
 // WiFiClient httpclient;// moved to start
  const int httpPort = 80;
  if (!httpclient.connect(WUNDERGROUND, httpPort)) {
    //if (!httpclient.connect(host, httpPort)) {
    Serial.println(F("connection failed"));
    delay(DELAY_ERROR);
    return;
  }

  // This will send the http request to the server
//  Serial.print(WUNDERGROUND_REQ);
  Serial.print(WUNDERGROUND_REQ);
 httpclient.print(WUNDERGROUND_REQ);
//  httpclient.print(BBC_REQ);
  httpclient.flush();
// working to here

//if (httpclient.available()) {

//only works if xml is formatted with line breaks
 while(linecount < 2){
char c = httpclient.read();
if (c == 10){linecount++;}}

char c = httpclient.read();
Serial.print(c);
if(c == '<' ){
for(int i=0; i<7; i++){
 Serial.print(c);
if(c != target[i]){ worded=false; }
c = httpclient.read();
Serial.print(c);
if(i==6 && worded==true){

//STUFF TO DO AFTER TITLE TAG GOES HERE
for(int i=0; i<80; i++){
tolcd[i]=' ';}

Serial.print(c);

while(tag==false){

if(c=='<'){tag=true;}

tolcd[lcdcount]=c;
lcdcount++;
//Serial.print(c);
c = httpclient.read();
}

for(int i=0; i<16; i++){
tolcd[lcdcount-1]=(' ');
lcdcount++;
}

Serial.print(lcdcount);

for(int p=0; p<(lcdcount-16); p++){

char dispchar = tolcd[p];
Serial.print(dispchar);

for(int i=0; i<16; i++){
//myGLCD.setCursor(0, 0);
//myGLCD.print String("Headlines:");
Serial.print("Headlines..");
char displaychar = tolcd[(i+counter)%lcdcount];
//myGLCD.setCursor(i,1);
//myGLCD.print(displaychar);
Serial.print(displaychar);
}

if(p==0){delay(1000);}
counter++;
delay(120);

}
counter=0;

lcdcount=0;

if(tag==true){tag=false; Serial.println(" ");}// me

}

}
}

if(worded==false){worded=true;}

delay(30000);
}


//}
