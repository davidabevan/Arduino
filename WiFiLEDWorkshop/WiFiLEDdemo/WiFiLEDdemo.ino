//#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Adafruit_NeoPixel.h>
#include "font5x7.h"

#define PIN_BUTTON   0
#define PIN_LED     14//din
#define NUM_LEDS    64

String scrolltext = " Hello World!";
uint16_t scrollwait = 75;
uint32_t scrollcolor = 0x002000;
byte scrollindex = 0; // scroll character index

// Neopixel object
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

byte demo_index = 0;
byte brightness = 28;       // default brightness: 48
uint32_t pixels[NUM_LEDS];  // pixel buffer. this buffer allows you to set arbitrary
                            // brightness without destroying the original color values

ESP8266WebServer server(80);  // create web server at HTTP port 80

// Forward declare functions
String get_ap_name();
void button_handler();
void on_status();
void on_change_color();
void on_homepage();
void show_leds();
void demo_wipe();
void demo_rainbow();
void demo_scrolltext();

void show_leds() {
  uint32_t r, g, b;
  uint32_t c;
  for(byte i=0;i<NUM_LEDS;i++) {
    r = (pixels[i]>>16)&0xFF;
    g = (pixels[i]>>8)&0xFF;
    b = (pixels[i])&0xFF;
    r = r*brightness/255;
    g = g*brightness/255;
    b = b*brightness/255;
    c = (r<<16) + (g<<8) + b;
    leds.setPixelColor(i, c);
  }
  leds.show();
}

void setup() {
  Serial.begin(115200);
  
  // Set pin mode
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED,    OUTPUT);

  // Initialize LEDs
  leds.begin();
  leds.show();

  // Set WiFi SSID
  String ap_name = get_ap_name();
  WiFi.persistent(false);
  WiFi.softAP(ap_name.c_str());
  WiFi.mode(WIFI_AP);
  
  // Set server callback functions
  server.on("/",   on_homepage);    
  server.on("/js", on_status);
  server.on("/cc", on_change_color);
  server.begin();
  
  // Set button handler
  attachInterrupt(PIN_BUTTON, button_handler, FALLING);
}

// The variable below is modified by interrupt service routine
// so declare it as volatile
volatile boolean button_clicked = false;

void loop() {
  switch(demo_index) {
  case 0:
    demo_wipe();
    break;
    
  case 1:
    demo_rainbow();
    break;

  default:
    server.handleClient();
    if(scrolltext.length() > 0) {
      demo_scrolltext();
    }
    break;
  }   
  
  if(button_clicked) {
    demo_index ++;  // upon button click, proceed to the next demo
    button_clicked = false;
  }
}

/* ----------------
 * Color Wipe Demo
 * ---------------- */

void wipe(uint32_t c, byte wait) {  // wipe with a given color
  for(byte i=0; i<NUM_LEDS; i++) {
    leds.setPixelColor(i, c);
    leds.show();
    delay(wait);
  } 
}

void demo_wipe() {
  static byte idx = 0;
  switch(idx) {
    case 0:
      wipe(0x200000, 30);
      delay(100);
      break;
    case 1:
      wipe(0x002000, 30);
      delay(100);
      break;
    case 2:
      wipe(0x000020, 30);
      delay(100);
      break;
  }
  idx=(idx+1)%3;
}

/* ----------------
 *   Rainbox Demo
 * ---------------- */

uint32_t wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return leds.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return leds.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return leds.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void demo_rainbow() {
  static byte idx = 0;
  for(byte i=0;i<NUM_LEDS;i++) {
    pixels[i] = wheel((i+idx)&0xFF);
  }
  show_leds();
  delay(10);
  idx++;
}

/* ----------------
 * Scroll Text Demo
 * ---------------- */

void drawCol(char c, int i){
  if(i >= 0 && i < 8){
    for(int j = 0; j < 8; j++){
        if(c & 0x1){
          leds.setPixelColor(i*8+j, scrollcolor);
        } else {
          leds.setPixelColor(i*8+j, 0);
        }
        c >>= 1;
    }
  }
}

void drawChar(char c, int offset){
  char col;
  for(int i = 0; i < 8; i++){
    if(i - offset >= 0 && i - offset < 8){
      col = pgm_read_byte(font+(c*8)+i);
      drawCol(col,i - offset);
    }
  }
}

void demo_scrolltext() {

  for(byte j = 0; j < 8; j++){
    for(byte k = 0; k < 2; k++){
      drawChar(scrolltext.charAt(scrollindex+k),j - k*8);
      drawCol(0,5-j+k*6);
    }
    delay(scrollwait);  
    leds.show();
  }

  scrollindex = (scrollindex+1)%scrolltext.length();
}

/* ----------------
 *  WebServer Demo
 * ---------------- */

#include "html.h"
void on_homepage() {
  String html = FPSTR(index_html);
  server.send(200, "text/html", html);
}

// this returns device variables in JSON, e.g.
// {"pixels":xxxx,"blink":1}
void on_status() {
  String html = "";
  html += "{\"brightness\":";
  html += brightness; 
  html += "}";
  server.send(200, "text/html", html);
}

void on_change_color() {
  uint16_t i;
  if(server.hasArg("pixels")) {
    String val = server.arg("pixels");
    for(i=0;i<NUM_LEDS;i++) {
      // every pixel color is 6 bytes storing the hex value
      // pixels are specified in row-major order
      // here we need to flip it to column-major order to 
      // match the physical connection of the leds
      byte r=i/5, c=i%5;
      pixels[c*7+r] = strtol(val.substring(i*6, i*6+6).c_str(), NULL, 16);
    }
    scrolltext = "";
  }
  if(server.hasArg("clear")) {
    for(i=0;i<NUM_LEDS;i++) {
      pixels[i] = 0;
    }
    scrolltext = "";
  }
  if(server.hasArg("brightness")) {
    brightness = server.arg("brightness").toInt();
    scrolltext = "";
  }
  if(server.hasArg("scrolltext")) {
    scrolltext = server.arg("scrolltext");
    scrolltext = " "+scrolltext;
    scrollindex = 0;
    if(server.hasArg("wait")) {
      scrollwait = server.arg("wait").toInt();
      if(scrollwait<5) scrollwait=5;
    }
    if(server.hasArg("color")) {
      scrollcolor = strtol(server.arg("color").c_str(), NULL, 16);
    }
  }
  if(scrolltext.length() == 0)
    show_leds();
  server.send(200, "text/html", "{\"result\":1}");
}

char dec2hex(byte dec) {
  if(dec<10) return '0'+dec;
  else return 'A'+(dec-10);
}

// AP name is ESP_ following by 
// the last 6 bytes of MAC address
String get_ap_name() {
  static String ap_name = "";
  if(!ap_name.length()) {
    byte mac[6];
    WiFi.macAddress(mac);
    ap_name = "ESP_";
    for(byte i=3;i<6;i++) {
      ap_name += dec2hex((mac[i]>>4)&0x0F);
      ap_name += dec2hex(mac[i]&0x0F);
    }
  }
  return ap_name;
}

void button_handler() {
  button_clicked = true;
}


