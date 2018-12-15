#include "DigiKeyboard.h"
#include <EEPROM.h>   
 
int tempOffset = 10; //set the offset here after calibrating against known source
unsigned int logInterval = 120; //log a temperature every X seconds
unsigned int addressLimit = 511; 
unsigned int address = 0; 
unsigned int mode = 1;

void setup(void)
{

  pinMode(5, INPUT);
  pinMode(1, OUTPUT);
  digitalWrite(5,HIGH);
  int modeInput = digitalRead(5);
  if(modeInput == LOW){
    mode = 0;
  }
  
  if(mode == 1){
    analogReference(INTERNAL1V1);
  }

}


void ledState(int state){
  digitalWrite(1,state);
}

void readTemp(){

  ledState(HIGH);
  int returned = EEPROM.read(address);
  
  if(returned == 255){ //stop when we hit 255 - which means we got it all
    address = addressLimit+1;
    return;
  }
    
  address++;
  // this is generally not necessary but with some older systems it seems to
  // prevent missing the first character after a delay:
  DigiKeyboard.sendKeyStroke(0);
  
  // Type out this string letter by letter on the computer (assumes US-style
  // keyboard)
  
  DigiKeyboard.println(returned);
  
  // It's better to use DigiKeyboard.delay() over the regular Arduino delay()
  // if doing keyboard stuff because it keeps talking to the computer to make
  // sure the computer knows the keyboard is alive and connected
  
  DigiKeyboard.delay(15);
  ledState(LOW);
  DigiKeyboard.delay(15);
  


  
}

void writeTemp(){
  ledState(HIGH);
  int raw = analogRead(A0+15); 
  /* Original code used a 13 Cdeg adjustment. But based on my results, I didn't seem to need it. */
  // raw -= 13; // raw adjust = kelvin
  //int in_c = raw - 273; // celcius
  //in_c = round(in_c);
  
  int in_f = ((raw - 273)*1.8)+32; // temp in f
  in_f = round(in_f)+tempOffset;
  
  EEPROM.write(address, 255);//set next block to 255 so we know where it stopped
  
  EEPROM.write(address, in_f);
  
  address++; //increment address
  
  //delay until next log interval but blink while delaying
  int i =0;
  while (i<logInterval){
    ledState(HIGH);
    DigiKeyboard.delay(500);
    ledState(LOW);
    DigiKeyboard.delay(500);
    i++;
  }
  
}
 
void loop(){

    
  if(address>addressLimit){
    ledState(LOW);
    DigiKeyboard.delay(1000);
  }
  else if(mode ==1){
    writeTemp();
  }
  else if(mode ==0){
    readTemp();
  }


}
