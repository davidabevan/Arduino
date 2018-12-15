/*
 *  ESP8266 + bmp180 + thinkspeak.com
 *
 *
 */

#include <ESP8266WiFi.h>
#include <Wire.h>

const char* ssid     = "TNCAPC2653F";
const char* password = "A7252C69DF";

const char* host = "api.thingspeak.com";
const char* apikey = "XWYQUSZFRTC4VYRM";

#define BMP180_I2CADDR 0x77

#define	BMP180_CALIB_PARAM_AC1  0xAA
#define	BMP180_CALIB_PARAM_AC2  0xAC
#define	BMP180_CALIB_PARAM_AC3	0xAE
#define	BMP180_CALIB_PARAM_AC4	0xB0
#define	BMP180_CALIB_PARAM_AC5	0xB2
#define	BMP180_CALIB_PARAM_AC6	0xB4
#define	BMP180_CALIB_PARAM_B1	0xB6
#define	BMP180_CALIB_PARAM_B2	0xB8
#define	BMP180_CALIB_PARAM_MB	0xBA
#define	BMP180_CALIB_PARAM_MC	0xBC
#define	BMP180_CALIB_PARAM_MD	0xBE

#define BMP180_CTRL_MEAS_REG	(0xF4)
#define BMP180_ADC_OUT_MSB_REG	(0xF6)
#define BMP180_ADC_OUT_LSB_REG	(0xF7)

#define BMP180_SOFT_RESET_REG	(0xE0)
/* temperature measurement */
#define BMP180_T_MEASURE	(0x2E)
/* pressure measurement*/
#define BMP180_P_MEASURE	(0x34)
/* TO be spec'd by GL or SB*/
#define BMP180_TEMP_CONVERSION_TIME (5)
#define BMP180_PARAM_MG	(3038)
#define BMP180_PARAM_MH	(-7357)
#define BMP180_PARAM_MI	(3791)


int16_t ac1, ac2, ac3, b1, b2, mb, mc, md;
uint16_t ac4, ac5, ac6;
uint8_t oss;

int32_t  temp,pres;

//--------------------------------------------------------------------------------
uint16_t read16(uint8_t reg)
{
  uint16_t data;

  Wire.beginTransmission(BMP180_I2CADDR); 
  Wire.write(reg); 
  Wire.endTransmission(); 
  
  Wire.beginTransmission(BMP180_I2CADDR);
  Wire.requestFrom(BMP180_I2CADDR, 2);
  data =  (uint16_t)Wire.read()*256+Wire.read();
  Wire.endTransmission(); 

  return data;
}
//--------------------------------------------------------------------------------
uint8_t read8(uint8_t reg)
{
  uint8_t data;

  Wire.beginTransmission(BMP180_I2CADDR); 
  Wire.write(reg); 
  Wire.endTransmission(); 
  
  Wire.beginTransmission(BMP180_I2CADDR); 
  Wire.requestFrom(BMP180_I2CADDR, 1);
  data = Wire.read(); 
  Wire.endTransmission(); 

  return data;
}
//--------------------------------------------------------------------------------
void write8(uint8_t reg, uint8_t val)
{
  Wire.beginTransmission(BMP180_I2CADDR); 
  Wire.write(reg); 
  Wire.write(val);  
  Wire.endTransmission(); 
}

//--------------------------------------------------------------------------------
void  getCalibrationData() 
{
  ac1 = read16(BMP180_CALIB_PARAM_AC1);
  ac2 = read16(BMP180_CALIB_PARAM_AC2);
  ac3 = read16(BMP180_CALIB_PARAM_AC3);
  ac4 = read16(BMP180_CALIB_PARAM_AC4);
  ac5 = read16(BMP180_CALIB_PARAM_AC5);
  ac6 = read16(BMP180_CALIB_PARAM_AC6);

  b1 = read16(BMP180_CALIB_PARAM_B1);
  b2 = read16(BMP180_CALIB_PARAM_B2);
  
  
  mb = read16(BMP180_CALIB_PARAM_MB);
  mc = read16(BMP180_CALIB_PARAM_MC);
  md = read16(BMP180_CALIB_PARAM_MD);
  
  Serial.print("ac1 = "); Serial.println(ac1);
  Serial.print("ac2 = "); Serial.println(ac2);
  Serial.print("ac3 = "); Serial.println(ac3);
  Serial.print("ac4 = "); Serial.println(ac4);
  Serial.print("ac5 = "); Serial.println(ac5);
  Serial.print("ac6 = "); Serial.println(ac6);
  Serial.print("b1 = "); Serial.println(b1);
  Serial.print("b2 = "); Serial.println(b2);
  Serial.print("mb = "); Serial.println(mb);
  Serial.print("mc = "); Serial.println(mc);
  Serial.print("md = "); Serial.println(md);
}


//--------------------------------------------------------------------------------
void getTempPress()
{
  int32_t UT, UP, B3, B5, B6, X1, X2, X3, p,T;
  uint32_t B4, B7;
  
  
   //temp
  write8(BMP180_CTRL_MEAS_REG,BMP180_T_MEASURE );
  delay(5);
  UT = read16(BMP180_ADC_OUT_MSB_REG);
  //Serial.println(UT);
  
  // press
  write8(BMP180_CTRL_MEAS_REG, BMP180_P_MEASURE + (oss << 6) );
  
  oss=oss&0x03;
  
  if (oss == 0) delay(5);
    else if (oss == 1) delay(8);
    else if (oss == 2) delay(14);
    else if (oss == 3) delay(26);
  
  UP=read16(BMP180_ADC_OUT_MSB_REG);
  UP <<= 8;
  UP += read8(BMP180_ADC_OUT_MSB_REG+2);
  UP >>= (8-oss);
    
  X1 = ((UT-ac6) * ac5) >>15;  // /2^15
  X2= ((int32_t)mc << 11) / (X1+md);
  
  B5 = X1+X2;
  T = (B5+8) >> 4;
  //Serial.println(T);
  
  B6 = B5 - 4000;
  X1 = ( (int32_t)b2  * ((B6*B6)>>12) ) >> 11;
  X2 = ( (int32_t)ac2 * B6) >> 11;
  X3 = X1 + X2;
  
  B3 = ((((int32_t)ac1*4 + X3) << oss) + 2) >> 2;
  X1 = ((int32_t)ac3 * B6) >> 13;
  X2 = ((int32_t)b1 * ((B6 * B6) >> 12)) >> 16;
  X3 = ((X1 + X2) + 2) >> 2;
  B4 = ((uint32_t)ac4 * (X3 + 32768)) >> 15;
  B7 = ((uint32_t)UP - B3) * ((uint32_t)50000 >> oss );
  
  if (B7 < 0x80000000)  p = (B7 * 2) / B4;
   else  p = (B7 / B4) * 2;
  
  X1 = (p >> 8) * (p >> 8);
  X1 = (X1 * 3038) >> 16;
  X2 = (-7357 * p) >> 16;
  p = p + ((X1 + X2 + 3791)>>4);
  
  
  temp=T;
  pres=p;
  
}
//--------------------------------------------------------------------------------

int counter;
int wlcount;

void setup() {
  Serial.begin(115200);
  delay(2000);
  Serial.println("Starting!");
 
  Wire.begin(0, 2);
  oss=3;
  getCalibrationData();
  counter=0;
  wlcount=0;
}


void loop() {

  counter++;
  
  String ou;
  String ou2;
  //getCalibrationData();  
  getTempPress();
  Serial.println(temp);
  Serial.println(pres);
  
  String tdec;
  if(temp<0) tdec=String(-1*temp%10);
   else tdec=temp%10;
  
  
  String tt=String(temp/10)+"."+tdec;
  String pp=String(pres/100)+"."+String(pres%100);
  
  ou="Temp: "+tt+" Press:" + pp;
  Serial.println(ou);
 
 
 
  wlcount=0;
  if(WiFi.status() != WL_CONNECTED) 
  {
       Serial.print("Connecting to AP: ");
       Serial.println(ssid);
       WiFi.begin(ssid, password);
       while (WiFi.status() != WL_CONNECTED) 
       {
        delay(1000);
        Serial.print(".");
        wlcount++;
        if(wlcount==20) return;
      }
  }
  
  
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) 
  {
    Serial.println("connection failed");
    return;
  }
  
  client.print(String("GET ") + "/update?key="+apikey+"&field1="+tt+"&field2="+pp+"&field3="+ESP.getFreeHeap()+"&field4="+counter+"   HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  
  
  delay(60000);  
}

