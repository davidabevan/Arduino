#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

#include <UTFT.h>
#include <SPI.h> 
const char SSID[]     = "PLUSNET-9P9QR6";
const char PASS[]     = "3bb7bc7cd3";
#include <ESP8266WiFi.h>
extern uint8_t SmallFont[];



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


void setup()
{
UTFT myGLCD ( ILI9341_S5P, 5, 4, 2 );
Serial.begin(9600);
// pinMode(1, OUTPUT);
delay(1000);
 // Setup the LCD
    myGLCD.InitLCD (  );
    myGLCD.setFont ( SmallFont );
 myGLCD.clrScr (  );
 myGLCD.setColor ( 255, 255, 255 );
    myGLCD.setBackColor ( 255, 0, 0 );

//Serial.println(“connecting…”);

//if (client.connect()) {
// Print a message to the LCD.
//lcd.clear();
//Serial.println(“connected”);
//delay(1000);
//lcd.print(“connected.”);

Serial.println();
  Serial.println();
  Serial.print(F("Connecting to "));
  Serial.println(SSID);

  WiFi.begin();

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }

  Serial.println();
  Serial.println(F("WiFi connected"));
  Serial.println(F("IP address: "));
  Serial.println(WiFi.localIP());
}
delay(1000);
client.println("GET /rss/newsonline_uk_edition/front_page/rss.xml");
client.println();
} else {
Serial.println("connection failed");
myGLCD.print("connection failed.");
}
}

void loop()
{
// lcd.clear();

if (client.available()) {

//only works if xml is formatted with line breaks
/* while(linecount < 2){
char c = client.read();
if (c == 10){linecount++;}}*/

char c = client.read();

if(c == '<'){
for(int i=0; i<7; i++){
// Serial.print(c);
if(c != target[i]){ worded=false; }
c = client.read();

if(i==6 && worded==true){

//STUFF TO DO AFTER TITLE TAG GOES HERE
for(int i=0; i<80; i++){
tolcd[i]=' ';}

//Serial.print(c);

while(tag==false){

if(c=='<'){tag=true;}

tolcd[lcdcount]=c;
lcdcount++;
//Serial.print(c);
c = client.read();
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
myGLCD.setCursor(0, 0);
myGLCD.print String("Headlines:");
char displaychar = tolcd[(i+counter)%lcdcount];
myGLCD.setCursor(i,1);
myGLCD.print(displaychar);

}

if(p==0){delay(1000);}
counter++;
delay(120);

}
counter=0;

lcdcount=0;

//if(tag==true){tag=false; Serial.println(” “);}// me

}

}
}

if(worded==false){worded=true;}

}
}


