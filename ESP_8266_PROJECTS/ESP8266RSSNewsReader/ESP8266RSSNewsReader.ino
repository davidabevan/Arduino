/*
 * 
 *  ESP8266 News Feed Reader (RSS)
 *
 *  This hardware/software combination implements an RSS news feed
 *  reader.
 *
 *  The hardware consists of the following parts:
 *    NodeMCU Amica R2 from Electrodragon
 *    1.8" SPI LCD Color Display from Adafruit - Product ID: 358
 *    Pushbutton switch
 *
 *  The connections between the NodeMCU board the the display are
 *  as follows:
 *
 *  ESP8266 Pin  LCD Display Pin       Function
 *  --------------------------------------------------------------------
 *      D3            Lite       Backlight light LED
 *                    MISO       Master In Slave Out (unused)
 *      D5  pin 09    CLK        SPI Clock
 *      D7  pin 08    MOSI       Master Out Slave In (data from Esp8266->display)
 *      D8  pin 10    TFT_CS     Display chip select
 *                    SD_CS      SD card chip select (unused)
 *      D4  pin 07         D/C        Data/Command toggle
 *                    Reset      Display controller reset (unused)
 *      3V3           Vcc        Power for the display
 *      GND           Gnd        Ground for the display
 *
 *  A pushbutton switch is connected between GND and D1 (GPIO5). When pressed
 *  the RSS feed is advanced.
 *
 *  Concept, Design and Implementation by: Craig A. Lindley
 *  Last Update: 11/06/2015
 */

 //Wiring Diagram ST7735 BREAKOUT BOARD TFT_LCD KMR 1.8 SPI
//****************************************************
//                                   LCD_PIN  Notes NODEMCU
//TFT LCD 01 to Pin GND                 *01   GND
//TFT LCD 02 to Pin VCC                 *02   VCC
//TFT LCD 06 to Pin RST to RST          *06
//TFT LCD 07 to Pin DC to GPIO_2        *07    A0     D4
//TFT LCD 08 to Pin MOSI to GPIO_13     *08    SDA    D7
//TFT LCD 09 to Pin CLK to GPIO_14      *09           D5
//TFT LCD 10 to Pin CS  to GPIO_5       *10           D1
//TFT LCD Pin MISO ( not use )    *12         NOT USED
//TFT LCD 15 to Pin LED to +3.3 V.      *15   LED VCC
//TFT LCD 16 TO GND                     *16     GND
//**********SD_READER_PINS******************************
//SD CS                           *14
//SD MISO                         *12
//SD MOSI                         *13
//SD SCK                          *11

#include <Adafruit_GFX.h>
#include <SPI.h>
#include <ESP8266WiFi.h>
#include "ESP8266_ST7735.h"
#include "Icons.h"
#include "TGFunctions.h"
#include "TextScroller.h"
#include "RSSReader.h"

// Array of feed URLs
const char *rssFeedURLs [] = {
   "http://www.cornwalllive.com/staustell.rss",
 "http://www.cornwalllive.com/weather.rss",
  "http://www.cornwalllive.com/live.rss",
   "http://www.cornwalllive.com/emergency-services.rss",
   "http://www.cornwalllive.com/all-content.rss",
  "www.npr.org/rss/rss.php?id=1001",
  "http://rss.cnn.com/rss/cnn_topstories.rss",
  "http://feeds.bbci.co.uk/news/rss.xml",
  "http://feeds.bbci.co.uk/news/world/rss.xml",
  "http://news.sky.com/sky-news/rss/home/rss.xml",
 "http://feeds.bbci.co.uk/news/technology/rss.xml",
  //"http://feeds.bbci.co.uk/news/rss.xml",
  //"http://hosted.ap.org/lineups/SCIENCEHEADS-rss_2.0.xml?SITE=OHLIM&SECTION=HOME",
 // "http://www.latimes.com/rss2.0.xml",
 // "http://rss.cnn.com/rss/cnn_tech.rss",
 // "http://feeds.reuters.com/reuters/topNews",

 "rssfeeds.usatoday.com/usatoday-NewsTopStories",
};

#define NUMBER_OF_FEEDS (sizeof(rssFeedURLs) / sizeof(char *))
int rssFeedIndex;

// ***************************************************************
// Start of user configuration items
// ***************************************************************

// Set your WiFi login credentials
const char * WIFI_SSID = "PLUSNET-9P9QR6";
const char * WIFI_PASS = "3bb7bc7cd3";

// ***************************************************************
// End of user configuration items
// ***************************************************************

#define APPNAME "Esp8266 RSS News Reader"
#define CREDITS "Craig A. Lindley"
#define PBMSG   "Pushbutton Advances Feed"

// Y positions of the various displayed strings on the LCD display
#define APPNAME_Y 10
#define CREDITS_Y 25
#define DATE_Y    57
#define SCROLL_Y  80
#define PBMSG_Y  111

// Connections between NodeMCU module and Adafruit 1.8" LCD display
#define TFT_CS    15
#define TFT_DC     2
#define TFT_LITE   0

// Create LCD driver instance
ESP8266_ST7735 lcd = ESP8266_ST7735(TFT_CS, TFT_DC);

// Create a text scroller instance
TextScroller textScroller = TextScroller(200, 2, 9, 12, COLOR_RED, COLOR_BLACK);

// Create RSS reader instance with 3 second timeout
RSSReader reader = RSSReader(3000);

// Callback called every time a title tag is found in the RSS XML
void titleCallback(char *titleStr) {

  char buffer[TITLE_BUFFER_SIZE];

  Serial.print("\nTitle: ");
  Serial.println(titleStr);

  // Make buffer empty
  buffer[0] = '\0';

  // First add a leading space char to make reading easier
  strcpy(buffer, " ");

  // Then add the title string
  strcat(buffer, titleStr);

  // Then add some trailing spaces
  strcat(buffer, "   ");

  // Scroll the composite text
  textScroller.scrollText(SCROLL_Y, buffer);
}

// Callback called every time a pubDate tag is found in the RSS XML
void pubDateCallback(char *dateStr) {

  Serial.print("PubDate: ");
  Serial.println(dateStr);
  drawCenteredText(DATE_Y, 1, dateStr, COLOR_RED, COLOR_BLACK);
}

/*******************************************************************/
/***                     Main Program Setup                     ***/
/*******************************************************************/

void setup() {

  // Backlight off until everything is initialized
  pinMode(TFT_LITE, OUTPUT);
  digitalWrite(TFT_LITE, LOW);

  // Initialize serial interface and allow it to stablize
  Serial.begin(115200);
  delay(1000);

  // Initialize the LCD (blacktab) display
  lcd.init();

  // Set display orientation to landscape
  lcd.setRotation(3);

  // Clear the display
  clearDisplay();

  // Draw the frame around the display
  drawDisplayFrame();

  // Draw credits on display
  drawCenteredText(APPNAME_Y, 1, APPNAME, COLOR_GREEN, COLOR_BLACK);
  drawCenteredText(CREDITS_Y, 1, CREDITS, COLOR_GREEN, COLOR_BLACK);

  // Display the WiFi logo icon
  drawWiFiIcon(COLOR_GREEN);

  // Backlight on to show initial WiFi screen
  digitalWrite(TFT_LITE, HIGH);

  Serial.print("\n\nConnecting to: ");
  Serial.println(WIFI_SSID);

  // Attempt WiFi network connection
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Clear the display
  clearDisplay();

  // Draw the frame around the display
  drawDisplayFrame();

  // Draw program information on screen
  drawCenteredText(APPNAME_Y, 1, APPNAME, COLOR_GREEN, COLOR_BLACK);
  drawCenteredText(CREDITS_Y, 1, CREDITS, COLOR_GREEN, COLOR_BLACK);
  drawCenteredText(PBMSG_Y,   1, PBMSG,   COLOR_GREEN, COLOR_BLACK);

  // Setup callbacks for title and pubDate tags in RSS XML
  reader.setTitleCallback(&titleCallback);
  reader.setPubDateCallback(&pubDateCallback);

  // Initialize feed index to first entry in feed list
  rssFeedIndex = 0;
}

/*******************************************************************/
/***                      Main Program Loop                      ***/
/*******************************************************************/

void loop() {

  // Short delay to keep networking happy
  delay(1);

  // Get URL of RSS feed to display
  const char *url = rssFeedURLs[rssFeedIndex];

  // Read and parse the RSS feed
  bool result = reader.read(url);
  if (result) {
    // The pushbutton was pressed so advance to the next feed
    // when button is released.
    rssFeedIndex++;
    rssFeedIndex %= NUMBER_OF_FEEDS;
  }
}


