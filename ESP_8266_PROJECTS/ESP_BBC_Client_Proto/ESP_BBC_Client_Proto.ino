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
#define WUNDERGROUND "google.com"
//#define BBC "GET /rss/newsonline_uk_edition/front_page/rss.xml"
//#define BBC "http://newsrss.bbc.co.uk/rss/newsonline_uk_edition/front_page/rss.xml"
//#define BBC "http://open.live.bbc.co.uk/weather/feeds/en/2647937/observations.rss"
//#define BBC "http://feeds.bbci.co.uk/"
//#define BBC "http://bbc.co.uk/"
// HTTP request
//const char WUNDERGROUND_REQ[] =
   // "GET /api/" WU_API_KEY "/conditions/q/" WU_LOCATION ".json HTTP/1.1\r\n"
   // "User-Agent: ESP8266/0.1\r\n"
   // "Accept: */*\r\n"
   // "Host: " WUNDERGROUND "\r\n"
   // "Connection: close\r\n"
   // "\r\n";


// HTTP request BBC
const char BBC_REQ[] =
 "GET /rss/newsonline_uk_edition/front_page/rss.xml HTTP/1.1\r\n" 
  //  "GET /api/" WU_API_KEY "/conditions/q/" WU_LOCATION ".json HTTP/1.1\r\n"
  //"GET /http://open.live.bbc.co.uk/weather/feeds/en/2647937/observations.rss"
    "User-Agent: ESP8266/0.1\r\n"
   "Accept: */*\r\n"
//    "Host: " BBC "\r\n"
    "Connection: close\r\n"
    "\r\n";
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

   // Use WiFiClient class to create TCP connections
 // WiFiClient client;
 // const int httpPort = 100;
 // if (!client.connect(host, httpPort)) {
   // Serial.println("BBC connection failed");
  //  return;
 // }
}

static char respBuf[4096];

void loop()
{
  // TODO check for disconnect from AP

  // Open socket to WU server port 80
  Serial.print(F("Connecting to "));
  //Serial.println(WUNDERGROUND);
Serial.println(host);
  // Use WiFiClient class to create TCP connections
  WiFiClient httpclient;
  const int httpPort = 80;
  if (!httpclient.connect(WUNDERGROUND, httpPort)) {
    //if (!httpclient.connect(host, httpPort)) {
    Serial.println(F("connection failed"));
    delay(DELAY_ERROR);
    return;
  }

  // This will send the http request to the server
//  Serial.print(WUNDERGROUND_REQ);
  Serial.print(BBC_REQ);
 // httpclient.print(WUNDERGROUND_REQ);
  httpclient.print(BBC_REQ);
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
