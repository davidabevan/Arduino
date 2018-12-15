/***************************************************************************
  This is a library for the BME280 humidity, temperature & pressure sensor

  Designed specifically to work with the Adafruit BME280 Breakout
  ----> http://www.adafruit.com/products/2650

  These sensors use I2C or SPI to communicate, 2 or 4 pins are required
  to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Limor Fried & Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution

 /*
 *  This sketch sends data via HTTP GET requests to thingspeak service every 10 minutes
 *  You have to set your wifi credentials and your thingspeak key.
 *  Deepsleep modification
 *  Esp8266 is pin 8 needs hard wireing with very fine wire to RST
 *  Espduino pin is miso/D12
 * ESP8266_12 Connect the DTR RST pin of the board to the XPD pin GPio16, of D0 which will make sure the chip can wake up from the deep sleep mode.
 ******************************/
 
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme; // I2C
//Adafruit_BME280 bme(BME_CS); // hardware SPI
//Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);

//const char* ssid     = "TNCAPC2653F";
//const char* password = "A7252C69DF";
const char* ssid     = "PLUSNET-9P9QR6";
const char* password = "3bb7bc7cd3";

const char* host = "api.thingspeak.com";
//const char* thingspeak_key = "6538YM84385NBODK";//St_Blazey
//const char* thingspeak_key = "XWYQUSZFRTC4VYRM";//Stenalees
const char* apikey = "G0A35KRSSPS2RA53";//Stenalees
int wlcount;
int counter;
//DEEPSLEEP******************************
void turnOff(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, 1);
}
void setup() {
  Serial.begin(9600);
  
  // disable all output to save power
 // turnOff(0);
  //turnOff(2);
  turnOff(4);
  turnOff(5);
  turnOff(12);
  turnOff(13);
  turnOff(14);
  turnOff(15);
 Wire.begin(0,2);//Needed for ESP8266 Starts I2C
  Serial.println(F("BME280 test"));
 if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    Serial.println("Could Not find a valid BME280 Sensor"); 
    while (1);
         }
  wlcount=0; 
  counter=0;      
//}


//void loop() {
 Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
    delay(2000);
     // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

int value = 0;

void loop() {
    counter++;
   
  //delay(5000);
  //++value;

  Serial.print("connecting to ");
  Serial.println(host);
  
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return;
  }
  
  client.print(String("GET ") + "/update?key="+apikey+"&field1="+bme.readTemperature()+"&field2="+bme.readHumidity()+"&field3="+bme.readPressure()+"&field4="+counter+"   HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection. going to sleep...");
  delay(1000);  

  
// go to deepsleep for 10 minutes
  // ESP.deepSleep(60000000, WAKE_RF_DEFAULT); // Sleep for 60 seconds
 // ESP.deepSleep(10 * 60 * 1000000,WAKE_RF_DEFAULT);
}
//DOES NOT WORK NO CONNECTION
