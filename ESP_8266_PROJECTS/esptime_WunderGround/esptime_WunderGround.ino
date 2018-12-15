/*
 Udp NTP Client
 Get the time from a Network Time Protocol (NTP) time server
 Demonstrates use of UDP sendPacket and ReceivePacket
 For more on NTP time servers and the messages needed to communicate with them,
 see http://en.wikipedia.org/wiki/Network_Time_Protocol
 created 4 Sep 2010
 by Michael Margolis
 modified 9 Apr 2012
 by Tom Igoe
 updated for the ESP8266 12 Apr 2015 
 by Ivan Grokhotkov
 This code is in the public domain.
 */
/*
 Web Client to consume Weather Underground web service
 
 This sketch connects to a website (http://api.wunderground.com)
 using an Arduino Ethernet shield and get data from site.
 
 Circuit:
 * Arduino MEGA 2560 R3 Board
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 07 Jan 2014
 by Afonso C. Turcato
 
 */
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <SPI.h>
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(23,216,168,120);  // numeric IP for Weather Underground  (no DNS)
const char server[] = "api.wunderground.com";    // name address for Weather Underground (using DNS)

const String myKey = "0e1262cc5f6a4bf9";  //See: http://www.wunderground.com/weather/api/d/docs (change here with your KEY)
const String myFeatures = "conditions";   //See: http://www.wunderground.com/weather/api/d/docs?d=data/index&MR=1
const String myCountry = "UK";        //See: http://www.wunderground.com/weather/api/d/docs?d=resources/country-to-iso-matching
const String myCity = "St_Austell";      //See: http://www.wunderground.com/weather/api/d/docs?d=data/index&MR=1
char ssid[] = "PLUSNET-9P9QR6";  //  your network SSID (name)
char pass[] = "3bb7bc7cd3";       // your network password
String responseString;

boolean startCapture;


unsigned int localPort = 2390;      // local port to listen for UDP packets

IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println();

  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  
  if (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
   String html_cmd1 = "GET /api/" + myKey + "/" + myFeatures + "/q/" + myCountry + "/" + myCity + ".json HTTP/1.1";
    String html_cmd2 = "Host: " + (String)server;
    String html_cmd3 = "Connection: close";
    
    //Uncomment this is necessary
    Serial.println("Sending commands:");
    Serial.println(" " + html_cmd1);
    Serial.println(" " + html_cmd2);
    Serial.println(" " + html_cmd3);
    Serial.println();
    
    // Make a HTTP request:
   udp.println(html_cmd1);
    udp.println(html_cmd2);
    udp.println(html_cmd3);
    udp.println();
    
    responseString = "";
    startCapture = false;   
 
  else
 // {
    // if you didn't get a connection to the server:
    Serial.println("Connection failed!");
  }
   }
     
 } 
void loop()
{
  //**********Wunderground
// if there are incoming bytes available 
  // from the server, read them and buffer:
  if (udp.available())
  {
    char c = udp.read();
    if(c == '{')
      startCapture=true;
    
    if(startCapture)
      responseString += c;
  }
  
  // if the server's disconnected, stop the client:
  //if (!client.connected()) {    
     while (WiFi.status() != WL_CONNECTED){
    Serial.println("Received " + (String)responseString.length() + " bytes");
    Serial.println("Disconnecting.");
    udp.stop();
    udp.flush();
    
    Serial.println();
    
    //Now, some examples of how to use it!
    Serial.print("Weather: ");
    Serial.println(getValuesFromKey(responseString, "weather"));
    Serial.println();
    
    Serial.print("Current Temperature: ");
    Serial.print(getValuesFromKey(responseString, "temp_c"));
    Serial.println(" oC\n");
    
    Serial.print("Relativy Humidity: ");
    Serial.println(getValuesFromKey(responseString, "relative_humidity"));
    Serial.println();
    
    Serial.print("Wind: ");
    Serial.println(getValuesFromKey(responseString, "wind_string"));
    Serial.println();
    
    Serial.print("Feels like: ");
    Serial.print(getValuesFromKey(responseString, "feelslike_c"));
    Serial.println(" oC\n");
    
    // do nothing forevermore:
    while(true);
  }
}

String getValuesFromKey(const String response, const String sKey)
{ 
  String sKey_ = sKey;
  
  sKey_ = "\"" + sKey + "\":";
  
  char key[sKey_.length()];
  
  sKey_.toCharArray(key, sizeof(key));
  
  int keySize = sizeof(key)-1;
    
  String result = NULL;
  
  int n = response.length();
  
  for(int i=0; i < (n-keySize-1); i++)
  {
    char c[keySize];
    
    for(int k=0; k<keySize; k++)
    {
      c[k] = response.charAt(i+k);
    }
        
    boolean isEqual = true;
    
    for(int k=0; k<keySize; k++)
    {
      if(!(c[k] == key[k]))
      {
        isEqual = false;
        break;
      }
    }
    
    if(isEqual)
    {     
      int j= i + keySize + 1;
      while(!(response.charAt(j) == ','))
      {
        result += response.charAt(j);        
        j++;
      }
      
      //Remove char '"'
      result.replace("\"","");
      break;
    }
  }
  
  return result;
}
  //**********Wunderground end
  
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(1000);
  
  int cb = udp.parsePacket();
  if (!cb) {
    Serial.println("no packet yet");
  }
  else {
    Serial.print("packet received, length=");
    Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;
   // Serial.print("Seconds since Jan 1 1900 = " );
   // Serial.println(secsSince1900);

    // now convert NTP time into everyday time:
   // Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    // print Unix time:
   // Serial.println(epoch);


    // print the hour, minute and second:
    Serial.print("The UTC time is ");       // UTC is the time at Greenwich Meridian (GMT)
    Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
    Serial.print(':');
    if ( ((epoch % 3600) / 60) < 10 ) {
      // In the first 10 minutes of each hour, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
    Serial.print(':');
    if ( (epoch % 60) < 10 ) {
      // In the first 10 seconds of each minute, we'll want a leading '0'
      Serial.print('0');
    }
    Serial.println(epoch % 60); // print the second
  }
  // wait ten seconds before asking for the time again
  delay(10000);
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
 // 
}
