/*
 *  TextScroller.cpp - TextScroller Class Functions
 *
 *  Concept, Design and Implementation by: Craig A. Lindley
 *  Last Update: 11/06/2015
 */

#include "ESP8266_ST7735.h"
#include "TextScroller.h"

extern ESP8266_ST7735 lcd;

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// TextScroller class constructor
TextScroller::TextScroller(int charDelayMS, int size, int xOffset, int width, uint16_t fg, uint16_t bg) {
  // Save incoming
  _charDelayMS = charDelayMS;
  _size = size;
  _xOffset = xOffset;
  _width = width;
  _fg = fg;
  _bg = bg;
}

// Scroll the text string once across the display. There isn't
// any text wrapping.
void TextScroller::scrollText(int y, String text) {

  lcd.setTextWrap(false);  // Don't wrap text to next line
  lcd.setTextSize(_size);  // Set text size
  lcd.setTextColor(_fg, _bg);

  // Loop once through the string
  for (int offset = 0; offset < text.length(); offset++) {
    // Figure out how many characters in the text are left for display
    int charsLeft = text.length() - 1 - offset;

    // Construct the string to display for this iteration
    String t;
    for (int i = 0; i < MIN(_width, charsLeft); i++)
      t += text.charAt(offset + i);

    // Print  the string for this iteration at specified X and Y locations
    lcd.setCursor(_xOffset, y);
    lcd.print(t);

    // Short delay so the text doesn't move too fast
    delay(_charDelayMS);
  }
}

