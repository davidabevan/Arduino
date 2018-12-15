
#include <picojpeg.h>
#include <User_Config.h>

/**The MIT License (MIT)

Copyright (c) 2015 by Daniel Eichhorn

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

See more at https://blog.squix.org
Wiring____________DB June 2017

LCD_______________WEMOS D! MINI
vcc_______________3.3V
gnd_______________g
CS________________D1
RESET_____________res
DC/RS_____________D2
MOSI______________D7
SCK_______________D5
LED_______________D8

       touchscreeen
  ESP                 LCD
  _______________________________
  D4-----------------T_IRQ
  D6-----------------T_D0
  D7-----------------T_DIN
  D3-----------------T_CS
  D5-----------------T_CLK
  D6-----------------SD0/MISO
  D8-----------------Led
  D5-----------------SCk
  D7-----------------SDL/MOSI
  D2-----------------D/C
  RST----------------RESET
  D1-----------------CS
  GND----------------GnD
  3V3----------------Vcc

*/

// Tft library connectors
#define TFT_DC D2
#define TFT_CS D1
#define TOUCH_CS D3
#define TOUCH_IRQ  D4
#define LED_PIN D8

// Needed for loading the map. If you want to be save better get your own key here:
// https://developer.mapquest.com/plan_purchase/steps/business_edition/business_edition_free/register
//#define MAP_QUEST_API_KEY "r19I8UVBfwIkmE4EZR9S6yMR43eMiRDZ"
#define MAP_QUEST_API_KEY "szNJqtuaEJIpLdAzxtGK2Xm3Ai3nNTIH"    //Mine

// Need for loading map by google static map api. If you want to be save better create one here
// https://developers.google.com/maps/documentation/static-maps/get-api-key?hl=de
//#define GOOGLE_API_KEY "AIzaSyBw0G8jCBry0IATNmysuyPd2fBblndS3jU"
//#define GOOGLE_API_KEY "AIzaSyBGIwiOBfyL5akl67wS98DZR6RF0bGriIg"  //Mine DB

#define GOOGLE_API_KEY "AIzaSyD8IH-E3o2KyLAHo_kKxH0tAD9GyBAcmeM"
#define MAP_ZOOM 9// Default= 11        SCALE THE MAP 9 goes to Truro area = zooming out
#define MAP_WIDTH 320
#define MAP_HEIGHT 192
// How many pixels outside the visible map should planes be requested
#define MAP_REQUEST_MARGIN 40


