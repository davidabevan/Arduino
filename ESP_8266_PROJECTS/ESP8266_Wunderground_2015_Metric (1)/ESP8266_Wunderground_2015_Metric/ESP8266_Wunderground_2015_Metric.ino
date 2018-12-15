/*
Programmed by Tufan Tas 23.01.2015 
www.tufantas.com
*/
//Libraries I put in
#include <TimeLib.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
//#include  "WProgram.h"
//*************************************************************
#include <ArduinoJson.h>
#include <UTFT.h>
#include <Time.h>
#include <Timer.h>
//#include <tinyFAT.h>
//#include <UTFT_tinyFAT.h>
//#include "OneWire.h"
//#include "DallasTemperature.h"
//#include "memorysaver.h" //if you use memorysaver.h must edit file. Inside UTFT Folder 


#define SSID "PLUSNET-9P9QR6" // insert your SSID
#define PASS "3bb7bc7cd3" // insert your password
#define LOCATIONID "UK/St_Austell" // location id
#define DST_IP "23.222.152.140" //api.wunderground.com

#define ONE_WIRE_BUS 16 
//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&oneWire);

//#define tftPwmPin 12
int x, y;

// Modify the line below to match your display and wiring:
//UTFT(byte model, int RS, int WR, int CS, int RST, int DC);
//in UTFT, RS is the data (MOSI), WR is the clock (SCK)
//UTFT myGLCD ( ST7735, 13, 14, 5, 4, 2 );//serial_SW ********Garbled
UTFT myGLCD ( ST7735, 5, 4, 2 );//Serial_HW****use the hardware SPI pins for SCK and MOSI (GPIO14 and GPIO13 

extern uint8_t  BigFont[];
extern uint8_t Inconsola[];
extern uint8_t SevenSeg_XXXL_Num[];
extern uint8_t SevenSegmentFull[];
extern uint8_t arial_normal[];
//UTFT_tinyFAT myFiles(&myGLCD); // Disabled by me
extern unsigned int homett[0x1000];
extern unsigned int rain[0x100];
extern unsigned int refresh[0x100];


const int buffer=400;//JSON Buffer size

int windGaugePanelX=671;
int windGaugePanelY=120;

int passNum = 1;
long ntpTime;
Timer t;
double tmp;
String tmpl,tmpld;
const char* iconName;
String sdFileName;


// Array of desired weather conditions & forecast.
// These must be in the order received from wunderground api server.



char* conds[]={"\"local_epoch\":","\"weather\":","\"temp_c\":","\"relative_humidity\":","\"wind_dir\":","\"wind_kph\":","\"pressure_mb\":","\"feelslike_c\":"};
int num_elements = 8;  // number of conditions you are retrieving, count of elements in conds
int num_elements_fr = 16; // number of forecast you are retrieving, count of elements in forecast

char* forecast[]={"\"celsius\":","\"celsius\":","\"icon\":","\"pop\":","\"celsius\":","\"celsius\":","\"icon\":","\"pop\":","\"celsius\":","\"celsius\":","\"icon\":","\"pop\":","\"celsius\":","\"celsius\":","\"icon\":","\"pop\":"};
char* forecast_rename[]={"\"celsius_h_0\":","\"celsius_l_0\":","\"icon_0\":","\"pop_0\":","\"celsius_h_1\":","\"celsius_l_1\":","\"icon_1\":","\"pop_1\":","\"celsius_h_2\":","\"celsius_l_2\":","\"icon_2\":","\"pop_2\":","\"celsius_h_3\":","\"celsius_l_3\":","\"icon_3\":","\"pop_3\":"}; //rename for same data name.
char* weekdayNames[]={"Sunday   ", "Monday   ", "Tuesday  ", "Wednesday", "Thursday ", "Friday   ", "Saturday "};
char close_brace ='}';
char comma = ',';
char* iconArray[]={"chanceflurries", "chancerain", "chancesleet", "chancesnow", "chancestorms", "clear", "cloudy", "flurries", "fog", "hazy", "mostlycloudy", "mostlysunny", "nt_chanceflurries", "nt_chancerain", "nt_chancesleet", "nt_chancesnow", "nt_chancetstorms", "nt_clear", "nt_cloudy", "nt_flurries", "nt_fog", "nt_hazy", "nt_mostlycloudy", "nt_mostlysunny", "nt_partlycloudy", "nt_partlysunny", "nt_rain", "nt_sleet", "nt_snow", "nt_sunny", "nt_tstorms", "partlycloudy", "partlysunny", "rain", "sleet", "snow", "sunny", "tstorms"};

void setup()
{  
//	pinMode(tftPwmPin, OUTPUT);
	//analogWrite(tftPwmPin, 250); //If you connect pwm pin to tft pwm input set brightness for Tft. (0 Min 255 Max)
 int setTime =0;// I put this in no good
int hour = 0;// me

   myGLCD.InitLCD();
   myGLCD.clrScr();
   myGLCD.setFont(Inconsola);
   myGLCD.setColor(VGA_RED);
//   file.initFAT();// Disabled by me
  
   Serial.begin(115200); // Debug
    
 //  sensors.begin(); 
   delay(1000);
   
   drawBackground();
	
	
	//sensorRead(); //Reading indoor temp sensor
	getForecast(); 
	t.every(10000, digitalClockDisplay);//every 500ms display the clock
	digitalClockDisplay();
//	t.every(50000, sensorRead);
	t.every(900000, getConds);
	t.every(6000000, getForecast);
   
}

void loop()
{
	t.update();

}


void getConds()
{
	
  Serial1.println("AT+CWJAP?"); //Check network connection. If you disconnected, reconnect for AP
  if (Serial1.find("ERROR")){
	  Serial.println("Reconnect for AP");
	  espLogin();}
  //espLogin();

  Serial1.println("AT+CIPMUX=0"); // set to single connection mode
  Serial.println("Connection Mode Single");
  
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += DST_IP;
  cmd += "\",80";
  Serial1.println(cmd);
  Serial.println(cmd);
  if(Serial1.find("ERROR")) return;
  
 // cmd = "GET /api/9021af226189803f/conditions/q/";// Authors
  cmd = "GET /api/0e1262cc5f6a4bf9/conditions/q/";
  cmd += LOCATIONID;
  cmd +=".json";
  cmd += " HTTP/1.1\r\nHost: api.wunderground.com\r\n\r\n";
  Serial1.print("AT+CIPSEND=");
  Serial1.println(cmd.length());
  if(Serial1.find(">")){
  Serial.println(">");
  }else{
    Serial1.println(F("AT+CIPCLOSE"));
    Serial.println("Connection timeout");
    delay(1000);
    getConds();
  }
  Serial1.print(cmd);
  Serial.print(cmd);
  unsigned int i = 0; //timeout counter
  char json[buffer]="{"; // array for Json parsing
  int n = 1;          // character counter for json  
  
  for (int j=0;j<num_elements;j++){
    while (!Serial1.find(conds[j])){} // find the part we are interested in.
  
    String Str1 = conds[j];
  
    for (int l=0; l<(Str1.length());l++)
        {json[n] = Str1[l];
         n++;}   
    while (i<60000) {
      if(Serial1.available()) {
        char c = Serial1.read();
         
          if(c==',') break;
          json[n]=c;
          n++;
          i=0;
        }
        i++;
      }
     if (j==num_elements-1)
        {json[n]=close_brace;}
     else   
        {json[n]=comma;}
     n++;   
  }

parseJSON(json);



// Done with processing for now - close connection
Serial1.println("AT+CIPCLOSE");
//Serial1.println("AT+CWQAP"); // If you like disconnect AP, uncomment this line

 

}



time_t requestSync()
{
	
//	setTime(ntpTime);// Need to check see line 310 also
	return 0;
}


void parseJSON(char json[400])
{
	Serial.println(json);
  StaticJsonBuffer<buffer> jsonBuffer;
 JsonObject& root = jsonBuffer.parseObject(json);
 
 if (!root.success())
{
  Serial.print("?fparseObject() failed");
  return;
}

 
 const char* pressure_mb = root["pressure_mb"];
 const char* local_epoch = root["local_epoch"];
 const char* weather = root["weather"];
 int temp_c = root["temp_c"];
 const char* humidity = root["relative_humidity"];
 const char* wind_dir = root["wind_dir"];
 int wind_kph = root["wind_kph"];
 const char* feelslike_c = root["feelslike_c"];
 
   
 Serial.println(pressure_mb);
 Serial.println(local_epoch);
// Conditions: Sunny, Cloudy, Fog, Rain, etc. 
 Serial.println(weather);
 Serial.println(temp_c);
 Serial.print(" C");
 myGLCD.setFont(SevenSegmentFull); 
  int posx;
  if (temp_c < 10) {posx = 70;}
  if (temp_c < -9) {posx = 20;}
  if (temp_c > 9 | temp_c < 0) {posx = 52;}
 myGLCD.printNumI(temp_c, posx, 42);
 
 int feelsliketoint = atoi(feelslike_c);
// int posx;
 if (feelsliketoint < 10) {posx = 70;}
 if (feelsliketoint < -9) {posx = 20;}
 if (feelsliketoint > 9 | feelsliketoint < 0) {posx = 52;}
 myGLCD.printNumI(feelsliketoint, posx, 132);
 
 int humtoint = atoi(humidity);
 
 myGLCD.printNumI(humtoint, 222, 106);
 
 
 myGLCD.setFont(Inconsola); 
 myGLCD.print("`", 120, 42); //Print degree sign
  myGLCD.print("`", 120, 132); //Print degree sign
  String pressure = pressure_mb; pressure += "mB";
  myGLCD.print(pressure, 162,208);
  myGLCD.setColor(VGA_BLUE);
 
  myGLCD.print("%",240,60 );
 myGLCD.setFont(arial_normal);
 myGLCD.setColor(VGA_LIME);
 myGLCD.print(" Temp.   ",44  ,20 );
 myGLCD.print("Feels Like",20, 110 );
 myGLCD.print("Pressure:",20, 214 );
 myGLCD.print("HUM.",226, 20 );
 myGLCD.print("                  ",20, 256 );
 myGLCD.print(weather,20, 256 );
 myGLCD.setFont(Inconsola); 
 

// Humidity 
 Serial.println(humidity);

 drawGaugePanel();
 
  myGLCD.setColor(VGA_RED);
  myGLCD.setBackColor(VGA_BLACK);
 

 Serial.println(wind_dir);

  // Wind Speed
 Serial.println(wind_kph);
 
 
 //Wind Panel (Wind direction print)
 
if (strcmp (wind_dir, "North")==0) {drawArrow(0) ;}
if (strcmp (wind_dir, "NNE")==0) {drawArrow(4.5) ;}
if (strcmp (wind_dir, "NE")==0) {drawArrow(7.5);}
if (strcmp (wind_dir, "ENE")==0) {drawArrow(12);}
if (strcmp (wind_dir, "East")==0) {drawArrow(15);}
if (strcmp (wind_dir, "ESE")==0) {drawArrow(19.5);}
if (strcmp (wind_dir, "SE")==0) {drawArrow(22.5);}
if (strcmp (wind_dir, "SSE")==0) {drawArrow(27);}
if (strcmp (wind_dir, "South")==0) {drawArrow(30);}
if (strcmp (wind_dir, "SSW")==0) {drawArrow(34);}
if (strcmp (wind_dir, "SW")==0) {drawArrow(37.5);}
if (strcmp (wind_dir, "WSW")==0) {drawArrow(41.5);}
if (strcmp (wind_dir, "West")==0) {drawArrow(45);}
if (strcmp (wind_dir, "WNW")==0) {drawArrow(49.5);}
if (strcmp (wind_dir, "NW")==0) {drawArrow(53);}
if (strcmp (wind_dir, "NNW")==0) {drawArrow(56) ;}
Serial.println(wind_dir);
myGLCD.setColor(0, 255, 0);

if ((wind_kph) < 10) {myGLCD.print("  ", 596, 242);
	myGLCD.printNumI(wind_kph, 620, 242);
}
else {
myGLCD.printNumI(wind_kph, 596, 242);}
myGLCD.print("Km/h", 660, 242);

 long longConv = atol (local_epoch);
 ntpTime = ((longConv) + 7200); 
// setTime = (ntpTime);// NEED TO CHECK
 refreshTimePrint();
}





void espLogin()
{
	
	Serial1.println("AT+RST"); // restet and test if module is redy
	delay(1000);
	if (Serial1.find("OK")) {
		Serial.println("WiFi - Module is ready");		
		} else {
		Serial.println("Module doesn't respond.");		
		espLogin();
	}
	delay(2000);
	// try to connect to wifi
	boolean connected = false;
	for (int i = 0; i < 5; i++) {
		if (connectWiFi()) {
			connected = true;			
			Serial.println("Connected to WiFi...");			
			break;
		}
	}
	if (!connected) {
		
		Serial.println("Coudn't connect to WiFi.");
		
		espLogin();
	}
	
	delay(5000);
}

boolean connectWiFi()
{
	
	String cmd = "AT+CWJAP=\"";
	cmd += SSID;
	cmd += "\",\"";
	cmd += PASS;
	cmd += "\"";
	Serial.println(cmd);
	Serial1.println(cmd);
	delay(2000);
	if (Serial1.find("OK")) {
		Serial.println("OK, Connected to WiFi.");
		return true;
		} else {
		Serial.println("Can not connect to the WiFi.");
		return false;
	}
}

void digitalClockDisplay(){
	myGLCD.setColor(255,0,0);
	
	String timp,data, data_w;
	
	//if (hour()<10)//Not working
	timp=timp+"0";
//	timp=timp+String(hour());// not working
	timp=timp+":";
	if (minute()<10)
	timp=timp+"0";
	timp=timp + String(minute());
	char charBuf[12];
	myGLCD.setFont(SevenSeg_XXXL_Num); //64*100 pixels	
		timp.toCharArray(charBuf, 12) ;
		myGLCD.print(charBuf, 478, 375);
    myGLCD.setFont(arial_normal);
	int w = (weekday()- 1);
    data=String(day())+"/"+String(month())+"/"+String(year()); //+"/"+String(data_w);

		
		myGLCD.setColor(VGA_RED);
		
		myGLCD.print(data, RIGHT, 308);
		myGLCD.print(weekdayNames[w], RIGHT, 328);
		myGLCD.setColor(VGA_LIME);
		myGLCD.print(weekdayNames[w], 358, 94);
		w = (weekday());
		if (w > 6) {w = 0;}
		myGLCD.setBackColor(VGA_BLACK);
		//myGLCD.setColor(VGA_LIME);
		myGLCD.print(weekdayNames[w], 8, 324);
		w++;
		if (w >6) {w = 0;}
		myGLCD.print(weekdayNames[w], 164, 324);
		w++;
		if (w >6) {w = 0;}
		myGLCD.print(weekdayNames[w], 320, 324);
		
		
		myGLCD.setFont(Inconsola);
		myGLCD.setColor(VGA_RED);
		
	   
	   
}


void getForecast()
{
	 Serial1.println("AT+CWJAP?");
	 if (Serial1.find("ERROR")){
		 Serial.println("NotConnectedAP");
		 espLogin();
	 
	 
	 }
	

	Serial1.println("AT+CIPMUX=0"); // set to single connection mode
	Serial.println("Connection Mode Single");
	
	String cmd = "AT+CIPSTART=\"TCP\",\"";
	cmd += DST_IP;
	cmd += "\",80";
	Serial1.println(cmd);
	Serial.println(cmd);
	if(Serial1.find("ERROR")) return;
	
	cmd = "GET /api/9021af226189803f/forecast/q/";
	cmd += LOCATIONID;
	cmd +=".json";
	cmd += " HTTP/1.1\r\nHost: api.wunderground.com\r\n\r\n";
	Serial1.print("AT+CIPSEND=");
	Serial1.println(cmd.length());
	if(Serial1.find(">")){
		Serial.println(">");
		}else{
		Serial1.println(F("AT+CIPCLOSE"));
		Serial.println("Connection timeout");
		delay(1000);
		getForecast();
	}
	Serial1.print(cmd);
	Serial.print(cmd);
	unsigned int i = 0; //timeout counter
	char json[buffer]="{"; // array for Json parsing
		int n = 1;          // character counter for json
		
		    while (!Serial1.find("\"simpleforecast\": {")) {}
		   
		for (int j=0;j<num_elements_fr;j++){
			while (!Serial1.find(forecast[j])){} // find the part we are interested in.
			
			String Str1 = forecast_rename[j];
			
			for (int l=0; l<(Str1.length());l++)
			{json[n] = Str1[l];
			n++;}
			while (i<60000) {
				if(Serial1.available()) {
					char c = Serial1.read();
					if (c== ',') {break;}
					if(c== '}') {n--;n--;n--;break;}
						
					json[n]=c;
					n++;
					i=0;
				}
				i++;
			}
			if (j==num_elements_fr-1)
			{   
				
				json[n]=close_brace;
			  
			
			}
			else
			{json[n]=comma;}
			n++;
		}

		parseForecastJSON(json);



		
		//Serial1.println("AT+CIPCLOSE");
		//delay(500);
		getConds();

	}
	
	void parseForecastJSON(char json[400])
	{
		Serial.println(json);
		StaticJsonBuffer<buffer> jsonBuffer;
		JsonObject& root = jsonBuffer.parseObject(json);
		
		if (!root.success())
		{
			Serial.print("?fparseObject() failed");
			getForecast();
		}
        
		
		const char* celsius_h_0 = root["celsius_h_0"];
		const char* celsius_l_0 = root["celsius_l_0"];
		const char* icon_0 = root["icon_0"];
		int pop_0 = root["pop_0"];
		const char* celsius_h_1 = root["celsius_h_1"];
		const char* celsius_l_1 = root["celsius_l_1"];
		const char* icon_1 = root["icon_1"];
		int pop_1 = root["pop_1"];
		const char* celsius_h_2 = root["celsius_h_2"];
		const char* celsius_l_2 = root["celsius_l_2"];
		const char* icon_2 = root["icon_2"];
		int pop_2 = root["pop_2"];
		const char* celsius_h_3 = root["celsius_h_3"];
		const char* celsius_l_3 = root["celsius_l_3"];
		const char* icon_3 = root["icon_3"];
		int pop_3 = root["pop_3"];
		
		myGLCD.setBackColor(VGA_NAVY);
		myGLCD.setColor(VGA_RED);
		myGLCD.setFont(Inconsola);
		String day1 = String(celsius_l_1) + "/" + String(celsius_h_1) + "`";
		String day2 = String(celsius_l_2) + "/" + String(celsius_h_2) + "`";
		String day3 = String(celsius_l_3) + "/" + String(celsius_h_3) + "`";
		String day0 = String(celsius_l_0) + "`/" + String(celsius_h_0) + "`";
		
		myGLCD.print("      ", 8, 294);
		myGLCD.print(day1, 8, 294);
		myGLCD.print("      ", 162, 294);
		myGLCD.print(day2, 162, 294);
		myGLCD.print("      ", 318, 294);
		myGLCD.print(day3, 318, 294);
		myGLCD.setBackColor(VGA_BLACK);
		myGLCD.print("      ", 358, 120);
		myGLCD.print(day0, 358, 120);
		//icon names
		//char iconName;
		Serial.println(pop_2);
		iconName = (icon_0);
		dayIconFix();
//		myFiles.loadBitmap(358, 170, 150, 110, (sdFileName));//Disabled by me
		Serial.println(sdFileName);
		iconName = (icon_1);
		dayIconFix();
//		myFiles.loadBitmap(8, 360, 150, 110, (sdFileName));//Disabled by me
		Serial.println(sdFileName);
		iconName = (icon_2);
		dayIconFix();
		Serial.println(sdFileName);
	//	myFiles.loadBitmap(164, 360, 150, 110, (sdFileName));
		iconName = (icon_3);
		dayIconFix();
		Serial.println(sdFileName);
	//	myFiles.loadBitmap(320, 360, 150, 110, (sdFileName));
		
		myGLCD.setColor(255,210,0);
		if (pop_0 > 0)
		{
			myGLCD.setFont(arial_normal);
			myGLCD.drawBitmap (358, 150, 16, 16, rain);
			myGLCD.print("%   ", 378, 150);
			myGLCD.printNumI(pop_0, 398, 150);
		}
		if (pop_1 > 0)
		   {
			   myGLCD.setFont(arial_normal);
			   myGLCD.drawBitmap (8, 344, 16, 16, rain);
			   myGLCD.print("%   ", 28, 344);
			   myGLCD.printNumI(pop_1, 48, 344);
		   }
		   
	    if (pop_2 > 0)
	    {
		    myGLCD.setFont(arial_normal);
		    myGLCD.drawBitmap (164, 344, 16, 16, rain);
		    myGLCD.print("%   ", 184, 344);
		    myGLCD.printNumI(pop_2, 204, 344);
	    }
		
		 if (pop_3 > 0)
		 {
			 myGLCD.setFont(arial_normal);
			 myGLCD.drawBitmap (320, 344, 16, 16, rain);
			 myGLCD.print("%   ", 340, 344);
			 myGLCD.printNumI(pop_3, 360, 344);
		 }
		myGLCD.setColor(VGA_RED);

		
	}


//void sensorRead()
//{
//sensors.requestTemperatures(); // Send the command to get temperatures
//float indoorTemp = (sensors.getTempCByIndex(0));
//Serial.println(sensors.getTempCByIndex(0));
//myGLCD.setColor(VGA_RED);
//myGLCD.setFont(SevenSegmentFull);
//myGLCD.printNumF(indoorTemp, 1, 396, 24);
//}

void drawBackground()
{

	//Boxes
	myGLCD.setColor(VGA_NAVY);
	myGLCD.fillRect(0,288,476,480);

//	myGLCD.fillRect(0,304,476,344);
	
	myGLCD.setColor(VGA_NAVY);
	myGLCD.fillRect(0,0,540,283); //Main out window
	myGLCD.setColor(VGA_BLACK);
	myGLCD.fillRect(10,10,530,278); //Main black window
	myGLCD.setColor(VGA_NAVY);
	myGLCD.fillRect(540,278,800,283);
	
	//Draw outdoor temp 
	myGLCD.fillRect(14, 14  , 188, 100);
	myGLCD.setColor(VGA_BLACK);
	myGLCD.fillRect(18, 18  , 184, 96);
	myGLCD.setColor(VGA_NAVY);
	
	//Draw Feelslike temp
	myGLCD.fillRect(14, 104  , 188, 190);
	myGLCD.setColor(VGA_BLACK);
	myGLCD.fillRect(18, 108  , 184, 186);
	myGLCD.setColor(VGA_NAVY);
	
	//Draw humidity
	myGLCD.fillRect(192, 14  , 316, 190);
	myGLCD.setColor(VGA_BLACK);
	myGLCD.fillRect(196, 18  , 312, 186);
	myGLCD.setColor(VGA_NAVY);
	
	//Draw pressure
	myGLCD.fillRect(14, 194  , 316, 250);
	myGLCD.setColor(VGA_BLACK);
	myGLCD.fillRect(18, 198  , 312, 246);
	myGLCD.setColor(VGA_NAVY);
	
	
	//draw home temp window
	myGLCD.setColor(VGA_NAVY);
	myGLCD.fillRect(320,10,530,86);
	myGLCD.setColor(VGA_BLACK);
	myGLCD.fillRect(324,17,526,82);
	myGLCD.drawBitmap (332, 16, 64, 64, homett);
	myGLCD.setColor(VGA_NAVY);
	myGLCD.fillRect(320,  86,330, 283);
	
	//Forecast days background
	myGLCD.setColor(VGA_BLACK);
	myGLCD.fillRect(8,324,157,360);
	myGLCD.fillRect(164,324,313,360);
	myGLCD.fillRect(320,324,469,360);
	



    

	
}

void drawHour(int h, int m)
{
	float x1, y1, x2, y2, x3, y3, x4, y4;
	int ph = h;
	
	myGLCD.setColor(0, 0, 0);
	if (m==0)
	{
		ph=((ph-1)*30)+((m+59)/2);
	}
	else
	{
		ph=(ph*30)+((m-1)/2);
	}
	ph=ph+270;
	
	x1=60*cos(ph*0.0175);
	y1=60*sin(ph*0.0175);
	x2=5*cos(ph*0.0175);
	y2=5*sin(ph*0.0175);
	x3=20*cos((ph+5)*0.0175);
	y3=20*sin((ph+5)*0.0175);
	x4=20*cos((ph-5)*0.0175);
	y4=20*sin((ph-5)*0.0175);
	
	myGLCD.drawLine(x1+windGaugePanelX, y1+windGaugePanelY, x3+windGaugePanelX, y3+windGaugePanelY);
	myGLCD.drawLine(x3+windGaugePanelX, y3+windGaugePanelY, x2+windGaugePanelX, y2+windGaugePanelY);
	myGLCD.drawLine(x2+windGaugePanelX, y2+windGaugePanelY, x4+windGaugePanelX, y4+windGaugePanelY);
	myGLCD.drawLine(x4+windGaugePanelX, y4+windGaugePanelY, x1+windGaugePanelX, y1+windGaugePanelY);

	myGLCD.setColor(255, 255, 0);
	h=(h*30)+(m/2);
	h=h+270;
	
	x1=60*cos(h*0.0175);
	y1=60*sin(h*0.0175);
	x2=5*cos(h*0.0175);
	y2=5*sin(h*0.0175);
	x3=20*cos((h+5)*0.0175);
	y3=20*sin((h+5)*0.0175);
	x4=20*cos((h-5)*0.0175);
	y4=20*sin((h-5)*0.0175);
	
	myGLCD.drawLine(x1+windGaugePanelX, y1+windGaugePanelY, x3+windGaugePanelX, y3+windGaugePanelY);
	myGLCD.drawLine(x3+windGaugePanelX, y3+windGaugePanelY, x2+windGaugePanelX, y2+windGaugePanelY);
	myGLCD.drawLine(x2+windGaugePanelX, y2+windGaugePanelY, x4+windGaugePanelX, y4+windGaugePanelY);
	myGLCD.drawLine(x4+windGaugePanelX, y4+windGaugePanelY, x1+windGaugePanelX, y1+windGaugePanelY);
}

void drawArrow(float m)
{
	float x1, y1, x2, y2, x3, y3, x4, y4;
	int pm = m-1;
	
	myGLCD.setColor(0, 0, 0);
	if (pm==-1)
	pm=59;
	pm=pm*6;
	pm=pm+270;
	
	x1=80*cos(pm*0.0175);
	y1=80*sin(pm*0.0175);
	x2=5*cos(pm*0.0175);
	y2=5*sin(pm*0.0175);
	x3=30*cos((pm+4)*0.0175);
	y3=30*sin((pm+4)*0.0175);
	x4=30*cos((pm-4)*0.0175);
	y4=30*sin((pm-4)*0.0175);
	
	

	myGLCD.setColor(0, 255, 0);
	m=m*6;
	m=m+270;
	
	x1=80*cos(m*0.0175);
	y1=80*sin(m*0.0175);
	x2=5*cos(m*0.0175);
	y2=5*sin(m*0.0175);
	x3=30*cos((m+4)*0.0175);
	y3=30*sin((m+4)*0.0175);
	x4=30*cos((m-4)*0.0175);
	y4=30*sin((m-4)*0.0175);
	
	myGLCD.drawLine(x1+windGaugePanelX, y1+windGaugePanelY, x3+windGaugePanelX, y3+windGaugePanelY);
	myGLCD.drawLine(x3+windGaugePanelX, y3+windGaugePanelY, x2+windGaugePanelX, y2+windGaugePanelY);
	myGLCD.drawLine(x2+windGaugePanelX, y2+windGaugePanelY, x4+windGaugePanelX, y4+windGaugePanelY);
	myGLCD.drawLine(x4+windGaugePanelX, y4+windGaugePanelY, x1+windGaugePanelX, y1+windGaugePanelY);
}

void drawGaugeLines(float s)
{
	s = (s-0.1);
	float x1, y1, x2, y2;
	int ps = s-1;
	
	myGLCD.setColor(0, 0, 0);
	if (ps==-1)
	ps=59;
	ps=ps*6;
	ps=ps+270;
	
	x1=95*cos(ps*0.0175);
	y1=95*sin(ps*0.0175);
	x2=80*cos(ps*0.0175);
	y2=80*sin(ps*0.0175);
	
	

	myGLCD.setColor(0, 0, 0);
	s=s*6;
	s=s+270;
	
	x1=65*cos(s*0.0175);
	y1=65*sin(s*0.0175);
	x2=30*cos(s*0.0175);
	y2=30*sin(s*0.0175);
	
	myGLCD.drawLine(x1+windGaugePanelX, y1+windGaugePanelY, x2+windGaugePanelX, y2+windGaugePanelY);
}
void drawGaugePanel()
{
	

//Wind gauge panel
myGLCD.setColor(VGA_NAVY);
myGLCD.fillCircle(670, 120, 110);
myGLCD.setColor(VGA_RED);
myGLCD.fillCircle(670, 120, 70);
myGLCD.setColor(VGA_SILVER);
myGLCD.fillCircle(670, 120, 5);

for (float i = 0; i < 60; i+=7.5)
{
	drawGaugeLines(i);
}


myGLCD.setBackColor(VGA_TRANSPARENT);
myGLCD.setColor(VGA_SILVER);
myGLCD.setFont(Inconsola);
myGLCD.print("N", 660,18);
myGLCD.print("NE", 728,38,47);
myGLCD.print("E", 750,110);
myGLCD.print("SE", 705,195,-48);
myGLCD.print("S", 660,200);
myGLCD.print("SW", 600,160,47);
myGLCD.print("W", 568,110);
myGLCD.print("NW", 586,58,-42);
				}
				
void dayIconFix()
{
	int i;
	
	for (i = 0; i < 40; i++)
	{
		
		if (strcmp (iconName, iconArray[i])==0) {i=i+1; sdFileName = "w"; sdFileName +=i; sdFileName += ".raw"; break;}
		
	}
	
	
}

void refreshTimePrint()
{
	

//int hour = 0;//me
myGLCD.setBackColor(VGA_BLACK);
myGLCD.setColor(VGA_LIME);
myGLCD.setFont(arial_normal);
myGLCD.drawBitmap (518, 316, 16, 16, refresh);
String refreshTime;

if (hour()<10)
refreshTime=refreshTime+"0";
refreshTime=refreshTime+String(hour());
refreshTime=refreshTime+":";
if (minute()<10)
refreshTime=refreshTime+"0";
refreshTime=refreshTime + String(minute());
myGLCD.print(refreshTime, 538, 316);
Serial.println(refreshTime);

}

