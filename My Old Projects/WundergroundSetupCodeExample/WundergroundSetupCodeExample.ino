void setup() {
  // put your setup code here, to run once:
//--------Weather underground----------DATE____________Now defined as function db---- Get_Date SEE LINE 135

//tft.fillScreen(ILI9341_BLACK);
//wunderground.updateConditions(WUNDERGRROUND_API_KEY, WUNDERGRROUND_LANGUAGE, WUNDERGROUND_COUNTRY, WUNDERGROUND_CITY);// date and current conditions
//tft.setCursor(20,10);
//tft.print("Date");
//String date = wunderground.getDate();//**********USE________ Gets date and names it
//tft.setCursor(20,50);
// tft.print( date);// Displays date DD MMM YYYY

 delay(3000);
 //****************Display Time
 tft.fillScreen(ILI9341_BLACK);
timeClient.updateTime();// time not displayed if disabled
  String time = timeClient.getFormattedTime();// gets time and gives it a name ******USE
// String time=wunderground.getDate();//put in this line and date is displayed where time should be
   // textWidth = display->getStringWidth(time);
   tft.setCursor(20,50);
  tft.print( time);// change this to date and date will be displayed instead
delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
