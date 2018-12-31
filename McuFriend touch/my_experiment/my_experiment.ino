#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;       // hard-wired for UNO shields anyway.
#include <TouchScreen.h>

char *name = "Please Calibrate.";  //edit name of shield
const int XP=6,XM=A2,YP=A1,YM=7; //ID=0x9341
const int TS_LEFT=201,TS_RT=899,TS_TOP=157,TS_BOT=900;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;

#define MINPRESSURE 200
#define MAXPRESSURE 1000

int16_t BOXSIZE;
int16_t PENRADIUS = 1;
uint16_t ID, oldcolor, currentcolor;
uint8_t Orientation = 3;    //0 PORTRAIT,1 landscape 2 port. 3portrait usb lowright

// Assign human-readable names to some common 16-bit color values:
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
 void palatte()
{
    BOXSIZE = tft.width() / 6;
    tft.fillScreen(BLACK);

    tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
    tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
    tft.fillRect(BOXSIZE * 2, 0, BOXSIZE, BOXSIZE, GREEN);
    tft.fillRect(BOXSIZE * 3, 0, BOXSIZE, BOXSIZE, CYAN);
    tft.fillRect(BOXSIZE * 4, 0, BOXSIZE, BOXSIZE, BLUE);
    tft.fillRect(BOXSIZE * 5, 0, BOXSIZE, BOXSIZE, MAGENTA);

    tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
    currentcolor = RED;
    delay(1000);
}
void createStartButton()
{
    //Create Red Button
  tft.fillRect(60,180, 200, 40, RED);
  tft.drawRect(60,180,200,40,WHITE);
  tft.setCursor(72,188);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.print("Start Game");
}

void drawStartScreen()
{
   tft.fillScreen(BLACK);
  
  //Draw white frame
  tft.drawRect(0,0,319,240,WHITE);
  
  //Print "Tic Tac Toe" Text
  tft.setCursor(30,100);
  tft.setTextColor(WHITE);
  tft.setTextSize(4);
  tft.print("Tic Tac Toe");
  
  //Print "YouTube!" text 
  tft.setCursor(80,30);
  tft.setTextColor(GREEN);
  tft.setTextSize(4);
  tft.print("Arduino");

  createStartButton();
  
}
//void show_Serial(void)
void showcoords(void)
{
 tp = ts.getPoint();
        pinMode(XM, OUTPUT);
        pinMode(YP, OUTPUT);
        if (tp.z < MINPRESSURE || tp.z > MAXPRESSURE);
        if (tp.x > 450 && tp.x < 570  && tp.y > 450 && tp.y < 570) break;
        tft.setCursor(0, (tft.height() * 3) / 4);
        tft.print("tp.x=" + String(tp.x) + " tp.y=" + String(tp.y) + "   ");
    }
void setup(void)
{
    uint16_t tmp;

    tft.reset();
    ID = tft.readID();
    tft.begin(ID);
    Serial.begin(9600);
    //show_Serial();
    tft.setRotation(Orientation);
    tft.fillScreen(BLACK);
   // show_tft();
//palatte();
//drawStartScreen();
}


void loop() {
  
