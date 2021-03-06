      /////////////////////////////////////////////
     //    2.8" TOUCH SCREEN TIC TAC TOE        //
    //                                         //
   //          http://www.educ8s.tv           //
  //                                         //
 //         modified 08.2017 by rom3        // 
/////////////////////////////////////////////

#include <SPI.h>
#include <Adafruit_GFX.h>
//#include <Adafruit_ILI9341.h>
#include <Adafruit_TFTLCD.h>
#include <URTouch.h>
//#include <TouchScreen.h>
//#define TFT_RST 8
//#define TFT_DC 9
//#define TFT_CS 10
#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4
#define TOUCH_ORIENTATION  LANDSCAPE
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
//Adafruit_ILI9341 tft = Adafruit_ILI9341(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);//(TFT_CS, TFT_DC, TFT_RST);

Adafruit_GFX_Button buttons[9];

URTouch  myTouch(30, 28, 26, 24, 22);

char start[10] = {"Gamestart"};
char you[4] = {"YOU"};
char cpu[4] = {"CPU"};
char again[7] = {"Again?"};
int player;
int difficulty=8;
unsigned short int x,y,b; // position touch

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

int board[]={0,0,0,0,0,0,0,0,0};// holds position data 0 is blank, 1 human, 2 is computer
unsigned turn;

const unsigned char circle[]PROGMEM={
0b0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xf0,0x0,0x0,0x0,
0x0,0x0,0xf,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x7f,0xf0,0x3,0xff,0x80,0x0,0x0,0x0,0x0,0xff,0x80,0x0,0x7f,0xc0,0x0,0x0,0x0,0x1,0xfe,0x0,0x0,0x1f,0xe0,0x0,0x0,
0x0,0x3,0xf8,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x3,0xf8,0x0,0x0,0x0,0xf,0xe0,0x0,0x0,0x1,0xfc,0x0,0x0,0x0,0xf,0xc0,0x0,0x0,0x0,0xfc,0x0,0x0,0x0,0x1f,0x80,0x0,0x0,0x0,0x7e,0x0,0x0,
0x0,0x3f,0x0,0x0,0x0,0x0,0x3f,0x0,0x0,0x0,0x3e,0x0,0x0,0x0,0x0,0x1f,0x0,0x0,0x0,0x7e,0x0,0x0,0x0,0x0,0x1f,0x80,0x0,0x0,0x7c,0x0,0x0,0x0,0x0,0xf,0x80,0x0,0x0,0x7c,0x0,0x0,0x0,0x0,0xf,0x80,0x0,
0x0,0xf8,0x0,0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0xf8,0x0,0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0xf8,0x0,0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0xf0,0x0,0x0,0x0,0x0,0x3,0xc0,0x0,0x1,0xf0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,
0x1,0xf0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x1,0xf0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x1,0xf0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x1,0xf0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x1,0xf0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,
0x1,0xf0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x1,0xf0,0x0,0x0,0x0,0x0,0x3,0xe0,0x0,0x0,0xf0,0x0,0x0,0x0,0x0,0x3,0xc0,0x0,0x0,0xf8,0x0,0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0xf8,0x0,0x0,0x0,0x0,0x7,0xc0,0x0,
0x0,0xf8,0x0,0x0,0x0,0x0,0x7,0xc0,0x0,0x0,0x7c,0x0,0x0,0x0,0x0,0xf,0x80,0x0,0x0,0x7c,0x0,0x0,0x0,0x0,0xf,0x80,0x0,0x0,0x7e,0x0,0x0,0x0,0x0,0x1f,0x80,0x0,0x0,0x3e,0x0,0x0,0x0,0x0,0x1f,0x0,0x0,
0x0,0x3f,0x0,0x0,0x0,0x0,0x3f,0x0,0x0,0x0,0x1f,0x80,0x0,0x0,0x0,0x7e,0x0,0x0,0x0,0xf,0xc0,0x0,0x0,0x0,0xfc,0x0,0x0,0x0,0xf,0xe0,0x0,0x0,0x1,0xfc,0x0,0x0,0x0,0x7,0xf0,0x0,0x0,0x3,0xf8,0x0,0x0,
0x0,0x3,0xf8,0x0,0x0,0x7,0xf0,0x0,0x0,0x0,0x1,0xfe,0x0,0x0,0x1f,0xe0,0x0,0x0,0x0,0x0,0xff,0x80,0x0,0x7f,0xc0,0x0,0x0,0x0,0x0,0x7f,0xf0,0x3,0xff,0x80,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xfe,0x0,0x0,0x0,
0x0,0x0,0xf,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xf0,0x0,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0x80,0x0,0x0,0x0,0x0,0x0,0x0,0x7,0xf8,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};
const unsigned char x_bitmap[]PROGMEM={
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x3,0xff,0xff,0xc0,0x1,0xff,0xff,0xe0,0x0,
0x1,0xff,0xff,0xe0,0x1,0xff,0xff,0xc0,0x0,0x1,0xff,0xff,0xf0,0x3,0xff,0xff,0xc0,0x0,0x0,0xff,0xff,0xf0,0x7,0xff,0xff,0x80,0x0,0x0,0xff,0xff,0xf8,0x7,0xff,0xff,0x80,0x0,0x0,0x7f,0xff,0xf8,0xf,0xff,0xff,0x0,0x0,
0x0,0x3f,0xff,0xfc,0xf,0xff,0xfe,0x0,0x0,0x0,0x3f,0xff,0xfe,0x1f,0xff,0xfe,0x0,0x0,0x0,0x1f,0xff,0xfe,0x1f,0xff,0xfc,0x0,0x0,0x0,0x1f,0xff,0xff,0x3f,0xff,0xfc,0x0,0x0,0x0,0xf,0xff,0xff,0x7f,0xff,0xf8,0x0,0x0,
0x0,0xf,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xf0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,
0x0,0x1,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xfe,0x0,0x0,0x0,
0x0,0x0,0x3f,0xff,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x1f,0xff,0xff,0xfc,0x0,0x0,0x0,0x0,0x0,0x3f,0xff,0xff,0xfe,0x0,0x0,0x0,
0x0,0x0,0x3f,0xff,0xff,0xfe,0x0,0x0,0x0,0x0,0x0,0x7f,0xff,0xff,0xff,0x0,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x0,0xff,0xff,0xff,0xff,0x80,0x0,0x0,0x0,0x1,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,
0x0,0x1,0xff,0xff,0xff,0xff,0xc0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x3,0xff,0xff,0xff,0xff,0xe0,0x0,0x0,0x0,0x7,0xff,0xff,0xff,0xff,0xf0,0x0,0x0,0x0,0xf,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,
0x0,0xf,0xff,0xff,0xff,0xff,0xf8,0x0,0x0,0x0,0x1f,0xff,0xff,0x7f,0xff,0xfc,0x0,0x0,0x0,0x1f,0xff,0xfe,0x3f,0xff,0xfc,0x0,0x0,0x0,0x3f,0xff,0xfc,0x3f,0xff,0xfe,0x0,0x0,0x0,0x3f,0xff,0xfc,0x1f,0xff,0xfe,0x0,0x0,
0x0,0x7f,0xff,0xf8,0x1f,0xff,0xff,0x0,0x0,0x0,0xff,0xff,0xf8,0xf,0xff,0xff,0x80,0x0,0x0,0xff,0xff,0xf0,0x7,0xff,0xff,0x80,0x0,0x1,0xff,0xff,0xe0,0x7,0xff,0xff,0xc0,0x0,0x1,0xff,0xff,0xe0,0x3,0xff,0xff,0xc0,0x0,
0x3,0xff,0xff,0xc0,0x3,0xff,0xff,0xe0,0x0,0x3,0xff,0xff,0xc0,0x1,0xff,0xff,0xe0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
};


void setup()
{
myTouch.InitTouch();
  myTouch.setPrecision(PREC_HI);
  tft.begin();
  tft.setRotation(3);
}

void loop()
{
   int board[9] = {0,0,0,0,0,0,0,0,0};

   drawStartScreen();
    do{
    myTouch.read();
      x = myTouch.getX();  //Get touch point  
      y = myTouch.getY();
   delay(100);
   }while(!(buttons[0].contains(x,y)));

   tft.fillScreen(BLACK);
    //Draw white frame
    tft.drawRect(0,0,320,240,WHITE);
    //Print "Tic Tac Toe" Text
    tft.setCursor(30,30);
    tft.setTextColor(WHITE);
    tft.setTextSize(4);
    tft.print("Tic Tac Toe");
    //Print "YouTube!" text 
    tft.setCursor(30,100);
    tft.setTextColor(GREEN);
    tft.setTextSize(4);
    tft.print("Who begins");
    //Create Red Button
    // create buttons // x, y, w, h, outline, fill, text
          buttons[0].initButton(&tft, 100,200,80,40,WHITE, RED, WHITE,
                      you, 2); 
          buttons[0].drawButton();
          // create buttons // x, y, w, h, outline, fill, text
          buttons[1].initButton(&tft, 200,200,80,40,WHITE, RED, WHITE,
                      cpu, 2); 
          buttons[1].drawButton();
    b=1;
    do{
    myTouch.read();
      x = myTouch.getX();  //Get touch point  
      y = myTouch.getY();
    if (buttons[0].contains(x,y))
    {
      b=0;
      player = 1;
      tft.fillScreen(BLACK);
      //Draw white frame
      tft.drawRect(0,0,320,240,WHITE);
      tft.setCursor(30,30);
      tft.setTextColor(WHITE);
      tft.setTextSize(2);
      tft.print("Ok, you begin.");
      delay(2000);
    }
      if(buttons[1].contains(x,y))
      {
        b=0;
        player = 2;
        tft.fillScreen(BLACK);
        //Draw white frame
        tft.drawRect(0,0,320,240,WHITE);
        tft.setCursor(30,30);
        tft.setTextColor(WHITE);
        tft.setTextSize(2);
        tft.print("Ok, CPU begins."); 
        delay(2000);
       }
    }while(b);
    
    tft.fillScreen(BLACK);
    tft.drawRect(0,0,319,240,WHITE);
   
   drawVerticalLine(125);
   drawVerticalLine(195);
   drawHorizontalLine(80);
   drawHorizontalLine(150);
   
       for(turn = 0; turn < 9 && win(board) == 0; ++turn) {
        if((turn+player) % 2 == 0)
            computerMove(board);
            else {
            //draw(board);
            playerMove(board);
        }
    }
    switch(win(board)) {
        case 0:
            Serial.println("It's a draw.\n");
            break;
        case 1:
            //draw(board);
            Serial.println("You lose.\n");
            break;
        case -1:
            Serial.println("You win!\n");
            break;
    }
   do{}while(myTouch.dataAvailable()==false); 
      //x = map(tp.y, 930, 88, 0, 480);
      //y = map(tp.x, 908, 125, 0, 320);
      //delay(250);}
    }
void drawHorizontalLine(int y)
{
  int i=0;
  for(i=0;i<7;i++)
  {
    tft.drawLine(60,y+i,270,y+i,WHITE);
  }
}

void drawVerticalLine(int x)
{
  int i=0;
  for(i=0;i<7;i++)
  {
    tft.drawLine(x+i,20,x+i,220,WHITE);
  }
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

  buttons[0].initButton(&tft, 160,200,200,40,WHITE, RED, WHITE, start, 2); 
          buttons[0].drawButton();
  
}

void drawCircle(int x, int y)
{
  drawBitmap(x,y,circle,65,65,RED);
}

void drawX(int x, int y)
{
  drawBitmap(x,y,x_bitmap,65,65,BLUE);
}
void drawBitmap(int16_t x, int16_t y,
 const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color) {

  int16_t i, j, byteWidth = (w + 7) / 8;
  uint8_t byte;

  for(j=0; j<h; j++) {
    for(i=0; i<w; i++) {
      if(i & 7) byte <<= 1;
      else      byte   = pgm_read_byte(bitmap + j * byteWidth + i / 8);
      if(byte & 0x80) tft.drawPixel(x+i, y+j, color);
    }
  }
}
void computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1, 0);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[move] = 1;
    drawCpuMove(move);
    delay(100);
}

void playerMove(int board[9]) {
    int move = 0;
    b = 1;
      do{    
    if (myTouch.dataAvailable() == true)
    {
      myTouch.read();
      x = myTouch.getX();  //Get touch point  
      y = myTouch.getY();
      
      if((x>55 && x<125)&& (y>0 && y<80)) //0
      {
        if(board[0]==0)
        {
          move=0;
          b=0;  
          }
      }
       else if((x>125 && x<195) && (y>0 && y<80)) //1
      {
       
        if(board[1]==0)
        {
         move=1;
         b=0;  
        }
      }
       else if((x>195&&x<265)&& (y>0 && y<80)) //2
       {
        if(board[2]==0)
        {
         move=2;
         b=0;  
        }
      }

    else if((x>55 && x<125)&& (y>80 && y<155)) //3
      {
        if(board[3]==0)
        {
         move=3;
         b=0;  
        }
      }

       else if((x>125 && x<195)&& (y>80 && y<155)) //4
      {
        if(board[4]==0)
        {
         move=4;
         b=0;  
        }
      }

      else if((x>195&&x<265)&& (y>80 && y<155)) //5
      {
        if(board[5]==0)
        {
         move=5;
         b=0;  
        }
      }

       else if((x>55 && x<125)&& (y>155 && y<235)) //6
      {
        if(board[6]==0)
        {
         move=6;
         b=0;  
        }
      }

        else if((x>125 && x<195)&& (y>155 && y<235)) //7
      {
        if(board[7]==0)
        {
         move=7;
         b=0;  
        }
      }

       else if((x>195&&x<265)&& (y>155 && y<235)) //8
      {
        if(board[8]==0)
        {
         move=8;
         b=0;  
        }
      }
      
    }
   }while(b);
    board[move] = -1;
    drawPlayerMove(move);
    delay(100);
}
int win(const int board[9]) {
    //list of possible winning positions
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int winPos;
    for(winPos = 0; winPos < 8; ++winPos) {
        if(board[wins[winPos][0]] != 0 && board[wins[winPos][0]] == board[wins[winPos][1]] && board[wins[winPos][0]] == board[wins[winPos][2]])
            return board[wins[winPos][2]];
    }
    return 0;
}

int minimax(int board[9], int player, int depth) {
    //check the positions for players
    int winner = win(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
     
        if(board[i] == 0) {
            board[i] = player;
            int thisScore=0;
            if (depth<difficulty){
              thisScore = -minimax(board, player*-1,depth+1);
            }
            
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }
            //choose the worst move for opponent
            board[i] = 0;
        }
    }
    if(move == -1) return 0;
    return score;
}
void drawCpuMove(int move)
{
  switch(move)
  {
    case 0: drawCircle(55,15);  break;
    case 1: drawCircle(130,15); break;
    case 2: drawCircle(205,15); break;
    case 3: drawCircle(55,85);  break;
    case 4: drawCircle(130,85); break;
    case 5: drawCircle(205,85); break;
    case 6: drawCircle(55,155); break;
    case 7: drawCircle(130,155);break;
    case 8: drawCircle(205,155);break;
  }
}

void drawPlayerMove(int move)
{
  switch(move)
  {
    case 0: drawX(55,15);  break;
    case 1: drawX(130,15); break;
    case 2: drawX(205,15); break;
    case 3: drawX(55,85);  break;
    case 4: drawX(130,85); break;
    case 5: drawX(205,85); break;
    case 6: drawX(55,155); break;
    case 7: drawX(130,155);break;
    case 8: drawX(205,155);break;
  }
}

