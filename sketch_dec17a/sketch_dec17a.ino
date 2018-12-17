

#include <ESP8266WiFi.h>
//#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
//#include "OLEDDisplayUi.h"
//#include "ssd1306xled.h"

//#include "SSD1306.h"
// OLED SDA=D3, SCL=D4
// Display Settings
SSD1306Wire  display(0x3c, 4, 5);// using GPIO instead D0, D2 Espduino SCL SCA

#include "spritebank.h"

#define MAXLEVELSHIELDED 3

// var public
uint8_t Live = 0;
uint8_t ShieldRemoved = 0;
uint8_t MONSTERrest = 0;
uint8_t LEVELS = 0;
uint8_t SpeedShootMonster = 0;
uint8_t ShipDead = 0;
uint8_t ShipPos = 64;
// fin var public

//#define joyX A0 // analog, left = 0, center ~=512, right=1024
//#define joyY D8 // not used here
#define joyBTN 15 // button was D8
#define SOUND_PIN 4 // speaker + pin was D2
void setup() {
  // put your setup code here, to run once:
//Serial.begin(115200);
  WiFi.forceSleepBegin();
  
  display.init();
  display.flipScreenVertically();

  //pinMode(joyX, INPUT);
  
  pinMode(joyBTN, INPUT);
  //pinMode(SOUND_PIN, OUTPUT);
  
  //Serial.println();
  //Serial.println("Ok");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Tiny Space Invaders");
  display.display();
  delay(5000);
}

void LoadMonstersLevels(int8_t Levels, SPACE *space) {
  uint8_t x, y;
  for (y = 0; y < 4; y++) {
    for (x = 0; x < 6; x++) {
      space->MonsterGrid[y][x] = pgm_read_byte(&MonstersLevels[(Levels * 24) + ((y) * 6) + (x)]);
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
#define SHOOTS 2
  uint8_t Decompte = 0;
  uint8_t VarPot = 64;
  uint8_t MyShootReady = SHOOTS;
  SPACE space;
NEWGAME:;
  Live = 3;
  LEVELS = 0;
  while (1) {
    drawIntroImage();
    if (digitalRead(joyBTN) == HIGH) {
      //Sound(100, 125);
      //Sound(50, 125);
      break;
    }
  }
}




void drawIntroImage() {
  display.clear();
  display.drawXbm(0, 0, 128, 55, intro);
  display.display();  
}



uint8_t UFOWrite(uint8_t x, uint8_t y, SPACE *space) {
  if ((space->UFOxPos != -120) && (y == 0) && ((space->UFOxPos <= (x)) && (space->UFOxPos >= (x - 14)))) {
    return pgm_read_byte(&Monsters[(x - space->UFOxPos) + (6 * 14) + (space->oneFrame * 14)]);
  }
  return 0x00;
}



