/*
 * Copyright (c) 2015-2016  Spiros Papadimitriou
 *
 * This file is part of github.com/spapadim/XPT2046 and is released
 * under the MIT License: https://opensource.org/licenses/MIT
 *
 * This software is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied.
 */
 //Wiring Diagram
//****************************************************
//                             LCD_PIN    Wemos
//TFT LCD Pin VCC                 *1       5V
//TFT LCD Pin GND                 *2       GND
//TFT LCD Pin CS  to GPIO_5       *3       D1
//TFT LCD Pin RST to RST          *4       RST
//TFT LCD Pin DC to GPIO_4        *5       D2
//TFT LCD Pin MOSI to GPIO_13     *6       D7
//TFT LCD Pin CLK to GPIO_14      *7       D5
//TFT LCD Pin LED to +3.3 V.      *8       3.3V
//TFT LCD Pin MISO ( not use )    *9       D6
//^^^^^^TOUCH^^^^^^^^^^^^^^^^^^^^^^^^
// TFT LCD PIN T-CLK GPIO14      *10       D5
// TFT LCD PIN T-CS GPIO0        *11       D3
// TFT LCD PIN T-DIN GPIO13      *12       D7
// TFT LCD PIN T-DO GPIO12       *13       D6
// TFT LCD PIN T-IRQ GPIO2       *14       D4
//****************************************************
#include <Arduino.h>
#include <SPI.h>

#include <Ucglib.h>  // Required
#include <XPT2046.h>

// Modify the following two lines to match your hardware
// Also, update calibration parameters below, as necessary
Ucglib_ILI9341_18x240x320_HWSPI ucg(/*cd=*/ 4 , /*cs=*/ 5, /*reset=*/ 5);
XPT2046 touch(/*cs=*/ 0, /*irq=*/ 2);

void setup() {
  delay(1000);
  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  //ucg.begin(UCG_FONT_MODE_SOLID);
  touch.begin(ucg.getWidth(), ucg.getHeight());  // Must be done before setting rotation
  ucg.setRotate270();
  touch.setRotation(touch.ROT270);
  ucg.clearScreen();

  // Replace these for your screen module
  touch.setCalibration(209, 1759, 1775, 273);
}

static uint16_t prev_x = 0xffff, prev_y = 0xffff;

void loop() {
  if (touch.isTouching()) {
    uint16_t x, y;
    touch.getPosition(x, y);
    if (prev_x == 0xffff) {
      ucg.drawPixel(x, y);
    } else {
      ucg.drawLine(prev_x, prev_y, x, y);
    }
    prev_x = x;
    prev_y = y;
  } else {
    prev_x = prev_y = 0xffff;
  }
  delay(20);
}
