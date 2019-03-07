#include <M5Stack.h>
#include "utility/MPU9250.h"

MPU9250 IMU;
int screen_width = 320;
int screen_height = 240;

// Logo
const int stars_max = 40;
struct starsObject
{
  int x;
  int y;
  int width = 1;
  int height = 1;
  int color = 0x0000;
};
extern unsigned char logo[];
extern unsigned char craft_logo[];
int craft_logo_wh = 36;
int craft_logo_x;
int craft_logo_y;
starsObject starsArray[stars_max];
unsigned long stars_time = 2000;
unsigned long  stars_pre_millis = 0;

// Craft
extern unsigned char craft[];
extern unsigned char explode[];
int craft_width = 50;
int craft_height = 50;
int craft_x;
int craft_y;
int craft_step = 2; // px
unsigned long moveCraft_time = 10; 
unsigned long  moveCraft_pre_millis = 0;

// Space debris
const int spaceDebris_max = 100;
struct spaceDebrisObject
{
  int x;
  int y;
  int width = 15;
  int height = 15;
  bool hidden;
};
spaceDebrisObject spaceDebrisArray[spaceDebris_max];
unsigned long moveSpaceDebris_time = 40; 
unsigned long moveSpaceDebris_pre_millis = 0;

// Bullet
const int bullets_max = 3;
struct bulletsObject
{
  int x;
  int y;
  int width = 3;
  int height = 6;
  bool busy;
};
bulletsObject bulletsObjectArray[bullets_max];
unsigned long moveBullets_time = 5; 
unsigned long moveBullets_pre_millis = 0;
bool openFire = false;

// Health & score
int statusBar_height = 30;
int health;
int score;
 
void setup() {
  M5.begin();
  Wire.begin();
  IMU.initMPU9250();
  IMU.calibrateMPU9250(IMU.gyroBias, IMU.accelBias);
  M5.Lcd.setBrightness(150);
  gameReset();
}

void loop() {
  startGame();
  gameLoop();
  gameOver();
}

void gameReset() {
  craft_logo_x = 178;
  craft_logo_y = 75;
  craft_x = (screen_width / 2) - (craft_width / 2);
  craft_y = 180;
  spaceDebris_gen();
  bullets_gen();
  health = 3;
  score = 0;
}

void startGame() {
  M5.Lcd.fillScreen(0x0000);
  M5.Lcd.drawBitmap(0, 0, screen_width, screen_height, (uint16_t *)logo);
  M5.Lcd.drawBitmap(craft_logo_x, craft_logo_y, craft_logo_wh, craft_logo_wh, (uint16_t *)craft_logo);
  M5.Lcd.setCursor(35, 160);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(0x7bef);
  M5.Lcd.print("please, press any key");
  while(true)
  {
    M5.update();
    if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed()) break;
    drawStars();
  }
  moveLogoCraft();
  M5.Lcd.fillScreen(0x0000);
  drawHealthAndScore();
}

void drawStars() {
  unsigned long millis_ = millis();
  if ((millis_ - stars_pre_millis) >= stars_time)
  {
    stars_pre_millis = millis_;
    for (int i = 0; i < stars_max; i++)
    {
      if (random(2) > 0)
      {
        if (starsArray[i].color == (int)0x0000)
        {
          starsArray[i].x = random(0, screen_width);
          starsArray[i].y = random(0, 75);
          starsArray[i].color = (int)0xffff;
        }
        else if (starsArray[i].color == (int)0xffff)
          starsArray[i].color = (int)0x7bef;
        else if (starsArray[i].color == (int)0x7bef)
          starsArray[i].color = (int)0x0000; 
        M5.Lcd.fillRect(starsArray[i].x, starsArray[i].y, starsArray[i].width, starsArray[i].height, starsArray[i].color);
      }
    }
  }
}

void moveLogoCraft() {
  while (true)
  {
    if ((craft_logo_y + craft_logo_wh) <= 0) break;
    M5.Lcd.fillRect(craft_logo_x, craft_logo_y, craft_logo_wh, craft_logo_wh, 0x0000);
    M5.Lcd.drawBitmap(craft_logo_x, --craft_logo_y, craft_logo_wh, craft_logo_wh, (uint16_t *)craft_logo);
    delay(15);
  }
}

void gameOver() {
  M5.Lcd.fillScreen(0x0000);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(0x7bef);
  M5.Lcd.setCursor(35, 80);
  M5.Lcd.print("GAME OVER");
  M5.Lcd.setCursor(35, 110);
  M5.Lcd.print("score: ");
  M5.Lcd.print(score);
  M5.Lcd.setCursor(35, 140);
  M5.Lcd.print("please, press any key");  
  gameReset();
  while(true)
  {
    M5.update();
    if (M5.BtnA.wasPressed() || M5.BtnB.wasPressed() || M5.BtnC.wasPressed()) break;
  }
}

void gameLoop() {
  while (true)
  {
    if (!moveCraft(getAccel('X'))) break;
    if (!moveSpaceDebris()) break;
    fire(getAccel('Y'));
    if (health < 0) break;
  }
  craftExplode();  
}

int getAccel(char axis) {
  if (IMU.readByte(MPU9250_ADDRESS, INT_STATUS) & 0x01)
  {
    IMU.readAccelData(IMU.accelCount);
    IMU.getAres();
    switch(axis)
    {
      case 'X':
        IMU.ax = (float)IMU.accelCount[0] * IMU.aRes * 1000;
        return IMU.ax;
      case 'Y':
        IMU.ax = (float)IMU.accelCount[1] * IMU.aRes * 1000;
        return IMU.ax;
      case 'Z':
        IMU.az = (float)IMU.accelCount[2] * IMU.aRes * 1000;
        return IMU.az;
    }
  }
  return 0;
}

bool moveCraft(int vector) {
  unsigned long millis_ = millis();
  if (((millis_ - moveCraft_pre_millis) >= moveCraft_time))
  {
    moveCraft_pre_millis = millis_;  
    int craft_x_pre = craft_x;

    if (abs(vector) > 70)
    {
      if (vector > 0)
        craft_x -= craft_step;
      else if (vector < 0)
        craft_x += craft_step;
      M5.Lcd.fillRect(craft_x_pre, craft_y, craft_width, craft_height, 0x0000);
    }

    if ((craft_x < (screen_width - craft_width - craft_step)) && (craft_x > craft_step))
    { 
      M5.Lcd.drawBitmap(craft_x, craft_y, craft_width, craft_height, (uint16_t *)craft);
    }
    else
    {
      return false;                                                                               
    }
  }
  return true;
}

void craftExplode() {
  M5.Lcd.fillRect(craft_x, craft_y, craft_width, craft_height, 0x0000);
  M5.Lcd.drawBitmap(craft_x, craft_y, craft_width, craft_height, (uint16_t *)explode);
  delay(300);
}

void spaceDebris_gen() {
  for (int i = 0; i < spaceDebris_max; i++)
  {
    spaceDebrisArray[i].x = random(craft_width + (craft_width / 2), (screen_width - craft_width - (craft_width / 2)));
    spaceDebrisArray[i].y = -random(1, 500) * 10;
    spaceDebrisArray[i].hidden = false;
  }
}

bool moveSpaceDebris() {
  unsigned long millis_ = millis();
  if (((millis_ - moveSpaceDebris_pre_millis) >= moveSpaceDebris_time))
  {
    moveSpaceDebris_pre_millis = millis_; 
    for (int i = 0; i < spaceDebris_max; i++)
    {
      if (spaceDebrisArray[i].hidden == false)
      {
        if (spaceDebrisArray[i].y >= statusBar_height)
        {
          M5.Lcd.fillRect(spaceDebrisArray[i].x, spaceDebrisArray[i].y, spaceDebrisArray[i].height, spaceDebrisArray[i].width, 0x0000);
          spaceDebrisArray[i].y++;
          M5.Lcd.fillRect(spaceDebrisArray[i].x, spaceDebrisArray[i].y, spaceDebrisArray[i].height, spaceDebrisArray[i].width, GREEN);
        }
        else
        {
          spaceDebrisArray[i].y++;
        }
        
        if (spaceDebrisArray[i].y >= screen_height)
        {
          spaceDebrisArray[i].hidden = true;
          health--;
          drawHealthAndScore();
        }

        if ((((spaceDebrisArray[i].x + spaceDebrisArray[i].width) >= craft_x) && (spaceDebrisArray[i].x <= (craft_x + craft_width))) && ((spaceDebrisArray[i].y + spaceDebrisArray[i].height) >= (craft_y + (craft_height / 2))) && (spaceDebrisArray[i].y <= (craft_y + craft_height)))
        {
          return false; 
        }
      }
    }
  }
  return true;
}

void bullets_gen() {
  for (int i = 0; i < spaceDebris_max; i++)
  {
    spaceDebrisArray[i].x = random(craft_width + (craft_width / 2), (screen_width - craft_width - (craft_width / 2)));
    spaceDebrisArray[i].y = -random(1, 500) * 10;
    spaceDebrisArray[i].width = 10;
    spaceDebrisArray[i].height = 10;
    spaceDebrisArray[i].hidden = false;
  }
}

void fire(int vector) {
  if (vector < -250)
  {
    if (!openFire)
    {
      for (int i = 0; i < bullets_max; i++)
      {
        if (!bulletsObjectArray[i].busy)
        {
          openFire = true;
          bulletsObjectArray[i].x = ((craft_x + (craft_width / 2)) - 1);
          bulletsObjectArray[i].y = craft_y;
          bulletsObjectArray[i].busy = true;
          break;
        }
      }
    }
  }
  else
  {
    openFire = false;
  }

  unsigned long millis_ = millis();
  if (((millis_ - moveBullets_pre_millis) >= moveBullets_time))
  {
    moveBullets_pre_millis = millis_; 
    for (int i = 0; i < bullets_max; i++)
    {
      M5.Lcd.fillRect(bulletsObjectArray[i].x, bulletsObjectArray[i].y, bulletsObjectArray[i].width, bulletsObjectArray[i].height, 0x0000);
      if (bulletsObjectArray[i].busy)
      {
        bulletsObjectArray[i].y--;
        M5.Lcd.fillRect(bulletsObjectArray[i].x, bulletsObjectArray[i].y, bulletsObjectArray[i].width, bulletsObjectArray[i].height, 0xff80);
        if (bulletsObjectArray[i].y <= statusBar_height)
        {
          bulletsObjectArray[i].busy = false;
        }
        for (int j = 0; j < spaceDebris_max; j++)
        {
          if (((((spaceDebrisArray[j].x + spaceDebrisArray[j].width) >= bulletsObjectArray[i].x) && (spaceDebrisArray[j].x <= (bulletsObjectArray[i].x + bulletsObjectArray[i].width))) && ((spaceDebrisArray[j].y + spaceDebrisArray[j].height) >= (bulletsObjectArray[i].y + (bulletsObjectArray[i].height / 2))) && (spaceDebrisArray[j].y <= (bulletsObjectArray[i].y + bulletsObjectArray[i].height)) && (!spaceDebrisArray[j].hidden)))
          {
            bulletsObjectArray[i].busy = false;
            spaceDebrisArray[j].hidden = true;
            M5.Lcd.fillRect(bulletsObjectArray[i].x, bulletsObjectArray[i].y, bulletsObjectArray[i].width, bulletsObjectArray[i].height, 0x0000);
            M5.Lcd.fillRect(spaceDebrisArray[j].x, spaceDebrisArray[j].y, spaceDebrisArray[j].width, spaceDebrisArray[j].height, 0x0000);
            score++;  
            drawHealthAndScore();
          }
        }
      }
    }
  }
}

void drawHealthAndScore() {
  M5.Lcd.fillRect(0, 0, 320, statusBar_height, 0x0000);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setCursor(10, 2);
  for (int i = 0; i < health; i++)
  {
    M5.Lcd.print((char)0x3);
  }
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(0xff80);
  M5.Lcd.setCursor(190, 8);
  M5.Lcd.print("SCORE: ");
  M5.Lcd.print(score);
}

