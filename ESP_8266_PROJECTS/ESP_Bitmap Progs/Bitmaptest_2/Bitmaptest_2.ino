
//extern unsigned const conix_64x64[0x1000]; // "conix_[0x1000]" must match the name in the file.
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
//extern uint8_t conix_64x64[0x1000];
//extern unsigned int conix_64x64[0x1000];

#define TFT_DC 2
#define TFT_CS 5
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
void setup()
{
  /* add in the functions to get your LCD started */
   tft.begin  ();
   tft.setRotation(3);
   tft.fillScreen(ILI9341_BLACK);
   tft.setCursor(0, 0);
 // drawBitmap(0 x, 0 y,conix_64x64, 64 w, 64 h, ); // (0,0) where on the screen, (64,64) size of image, (conix_64x64) image name.

//tft.drawBitmap(220, 160,conix_64x64, 82, 77, BLACK);}
tft.drawBitmap(0,0,64,64, download_(1)[50246], 1);
//myGLCD.drawBitmap(x,y,width,height, name, scale);
void loop()
{
}

void drawBitmap(int x, int y, int sx, int sy, unsigned int *data)
{
int tc = 0;
for(int Y = 0; Y < sy; Y++)
{
  for(int X = 0; X < sx; X++)
  {
   display.drawPixel(X+x, Y+y, pgm_read_word(&data[tc]));
   if(tc < (sx*sy)) tc++;
  }
}
}
