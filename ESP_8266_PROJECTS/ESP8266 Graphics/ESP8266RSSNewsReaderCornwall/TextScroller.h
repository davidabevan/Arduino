/*
 *  TextScroller.h - Header file for TextScroller Class
 *
 *  Concept, Design and Implementation by: Craig A. Lindley
 *  Last Update: 11/06/2015
 */

#ifndef TEXT_SCROLLER_H
#define TEXT_SCROLLER_H

class TextScroller {
  public:

    TextScroller(int charDelayMS, int size, int xOffset, int width, uint16_t fg, uint16_t bg);
    void scrollText(int y, String text);

  private:
    int _charDelayMS;
    int _size;
    int _xOffset;
    int _width;
    uint16_t _fg;
    uint16_t _bg;
};

#endif


