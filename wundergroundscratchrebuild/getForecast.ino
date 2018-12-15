void getForecast()// Line 103
{
  static char respBuf[4096];
 WiFiClient httpclient;
// WiFiClient client;
  const int httpPort = 80;
 if (!httpclient.connect(WUNDERGROUND, httpPort)) {
    Serial.println("connection failed");
    return;
  }
 // This will send the http request to the server
  Serial.print(WUNDERGROUND_REQ);
  httpclient.print(WUNDERGROUND_REQ);
  httpclient.flush();
 
 // int retryCounter = 0;
 // while(!httpclient.available()) {
   // delay(1000);
   // retryCounter++;
   // if (retryCounter > 10) {
     // return;
   // }
 //// Collect http response headers and content from Weather Underground
  // HTTP headers are discarded.
  // The content is formatted in JSON and is left in respBuf.
  int respLen = 0;
  bool skip_headers = true;
  while (httpclient.connected() || httpclient.available()) {
    if (skip_headers) {
      String aLine = httpclient.readStringUntil('\n');
      //Serial.println(aLine);
      // Blank line denotes end of headers
      if (aLine.length() <= 1) {
        skip_headers = false;
      }
    }
    else {
      int bytesIn;
      bytesIn = httpclient.read((uint8_t *)&respBuf[respLen], sizeof(respBuf) - respLen);
      Serial.print(F("bytesIn ")); Serial.println(bytesIn);
      if (bytesIn > 0) {
        respLen += bytesIn;
        if (respLen > sizeof(respBuf)) respLen = sizeof(respBuf);
      }
      else if (bytesIn < 0) {
        Serial.print(F("read error "));
        Serial.println(bytesIn);
      }
    }
    delay(1);
  }
  httpclient.stop();

  if (respLen >= sizeof(respBuf)) {
    Serial.print(F("respBuf overflow "));
    Serial.println(respLen);
    delay(DELAY_ERROR);
    return;
  }
  // Terminate the C string
  respBuf[respLen++] = '\0';
  Serial.print(F("respLen "));
  Serial.println(respLen);
  //Serial.println(respBuf);
bool showWeather(char *json);
  if (showWeather(respBuf)) {
    delay(DELAY_NORMAL);
  }
  else {
    delay(DELAY_ERROR);
  }
