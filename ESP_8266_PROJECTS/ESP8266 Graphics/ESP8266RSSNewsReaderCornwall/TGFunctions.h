/*
 *  TGFunctions.h - Text and Graphics Support Functions
 *
 *  Concept, Design and Implementation by: Craig A. Lindley
 *  Last Update: 11/06/2015
 */

#ifndef TGFUNCTIONS_H
#define TGFUNCTIONS_H

extern ESP8266_ST7735 lcd;

// Clear the display
void clearDisplay() {
  // Set all pixels to black
  lcd.fillScreen(COLOR_BLACK);
}

// Get the width in pixels of a text string of specified size
int getTextWidth(const char *text, int size) {
  int len = strlen(text);

  // Chars are 5 px wide with 1 px space = 6
  return 6 * len * size;
}

// Calculate the x offset necessary to center a text string of specified size
int xOffsetForCenteredText(const char *text, int size) {
  return (lcd.width() - getTextWidth(text, size)) / 2;
}

// Draw a text string at specified location with specified size and color
void drawText(int x, int y, int size, const char *text, uint16_t fgColor, uint16_t bgColor) {
  lcd.setCursor(x, y);
  lcd.setTextSize(size);
  lcd.setTextColor(fgColor, bgColor);
  lcd.print(text);
}

// Draw a text string of specified size and color centered on display with y position
void drawCenteredText(int y, int size, const char *text, uint16_t fgColor, uint16_t bgColor) {
  drawText(xOffsetForCenteredText(text, size), y, size, text, fgColor, bgColor);
}

// Draw display frame
void drawDisplayFrame() {
  // Draw frame around display
  lcd.drawRect(0, 0, lcd.width(),      lcd.height(),     COLOR_BLUE);
  lcd.drawRect(1, 1, lcd.width() - 2 , lcd.height() - 2, COLOR_RED);
  lcd.drawRect(2, 2, lcd.width() - 4 , lcd.height() - 4, COLOR_BLUE);
}

// Draw WiFi Icon centered on display
void drawWiFiIcon(uint16_t color) {
  // Calculate position of icon
  int xOffset = (lcd.width()  - WIFI_ICON_WIDTH)  / 2;
  int yOffset = (lcd.height() - WIFI_ICON_HEIGHT) / 2;

  lcd.drawXBitmap(xOffset, yOffset, WiFiIcon, WIFI_ICON_WIDTH, WIFI_ICON_HEIGHT, color);
}

#endif

