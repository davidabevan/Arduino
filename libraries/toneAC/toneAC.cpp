// ---------------------------------------------------------------------------
// Created by Tim Eckel - teckel@leethost.com
// Copyright 2013 License: GNU GPL v3 http://www.gnu.org/licenses/gpl-3.0.html
//
// See "toneAC.h" for purpose, syntax, version history, links, and more.
// ---------------------------------------------------------------------------

#include "toneAC.h"

unsigned long _tAC_time; // Used to track end note with timer when playing note in the background.
bool _tAC_Noise; // Used to flag if noise or normal note being played
bool* _tAC_NoiseCompleted;
#ifndef TONEAC_TINY
uint8_t _tAC_volume[] = { 200, 100, 67, 50, 40, 33, 29, 22, 11, 2 }; // Duty for linear volume control.
#endif

#ifndef TONEAC_TINY
void toneAC(unsigned long frequency, uint8_t volume, unsigned long length, uint8_t background) {
  if (frequency == 0 || volume == 0) { noToneAC(); return; } // If frequency or volume are 0, turn off sound and return.
  if (volume > 10) volume = 10;                              // Make sure volume is in range (1 to 10).
#else
void toneAC(unsigned long frequency, unsigned long length) {
  _tAC_Noise=false;
  if (frequency == 0) { noToneAC(); return; }                // If frequency is 0, turn off sound and return.
#endif
  
  PWMT1DREG |= _BV(PWMT1AMASK) | _BV(PWMT1BMASK); // Set timer 1 PWM pins to OUTPUT (because analogWrite does it too).

  uint8_t prescaler = _BV(CS10);                 // Try using prescaler 1 first.
  unsigned long top = F_CPU / frequency / 2 - 1; // Calculate the top.
  if (top > 65535) {                             // If not in the range for prescaler 1, use prescaler 256 (122 Hz and lower @ 16 MHz).
    prescaler = _BV(CS12);                       // Set the 256 prescaler bit.
    top = top / 256 - 1;                         // Calculate the top using prescaler 256.
  }
#ifndef TONEAC_TINY
  unsigned int duty = top / _tAC_volume[volume - 1]; // Calculate the duty cycle (volume).
#else
  unsigned int duty = top >> 1;                      // 50% duty cycle (loudest and highest quality).
#endif

#ifndef TONEAC_TINY
  if (length > 0 && background) {  // Background tone playing, returns control to your sketch.
#else
  if (length > 0) {                // Background tone playing, returns control to your sketch.
#endif
    _tAC_time = millis() + length; // Set when the note should end.
    TIMSK1 |= _BV(OCIE1A);         // Activate the timer interrupt.
  }

  ICR1   = top;                         // Set the top.
  if (TCNT1 > top) TCNT1 = top;         // Counter over the top, put within range.
  TCCR1B = _BV(WGM13)  | prescaler;     // Set PWM, phase and frequency corrected (top=ICR1) and prescaler.
  OCR1A  = OCR1B = duty;                // Set the duty cycle (volume).
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1B0); // Inverted/non-inverted mode (AC).

#ifndef TONEAC_TINY
  if (length > 0 && !background) { delay(length); noToneAC(); } // Just a simple delay, doesn't return control till finished.
#endif
}

void setnoiseAC(uint8_t volume=10)  {
   uint8_t prescaler = _BV(CS10);                 // Try using prescaler 1 first.
 // unsigned long top = F_CPU / frequency / 2 - 1; // Calculate the top.
  unsigned long top = F_CPU / random(125,1000) / 2 - 1; // Calculate the top.
  if (top > 65535) {                             // If not in the range for prescaler 1, use prescaler 256 (122 Hz and lower @ 16 MHz).
    prescaler = _BV(CS12);                       // Set the 256 prescaler bit.
    top = top / 256 - 1;                         // Calculate the top using prescaler 256.
  }
  
  #ifndef TONEAC_TINY
    unsigned int duty = top / _tAC_volume[volume - 1]; // Calculate the duty cycle (volume).
  #else
    unsigned int duty = top >> 1;                      // 50% duty cycle (loudest and highest quality).
  #endif

  ICR1   = top;                         // Set the top.
  if (TCNT1 > top) TCNT1 = top;         // Counter over the top, put within range.
  TCCR1B = _BV(WGM13)  | prescaler;     // Set PWM, phase and frequency corrected (top=ICR1) and prescaler.
  OCR1A  = OCR1B = duty;                // Set the duty cycle (volume).
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) | _BV(COM1B0); // Inverted/non-inverted mode (AC).
}


void noiseAC(unsigned long length, uint8_t volume, bool* Completed)  {
	// generates noise for length time (milli's), default 100 (1 tenth of a second)
	// this part just sets up interupts and length for noise to play for, frequence set in setnoiseAC()
  *Completed=false;
  _tAC_NoiseCompleted=Completed;
  _tAC_Noise=true;
  _tAC_time = millis() + length; // Set when the noise should end.
  TIMSK1 |= _BV(OCIE1A);         // Activate the timer interrupt.
  
  PWMT1DREG |= _BV(PWMT1AMASK) | _BV(PWMT1BMASK); // Set timer 1 PWM pins to OUTPUT (because analogWrite does it too).
  setnoiseAC(volume);
 
}

void noToneAC() {
  TIMSK1 &= ~_BV(OCIE1A);     // Remove the timer interrupt.
  TCCR1B  = _BV(CS11);        // Default clock prescaler of 8.
  TCCR1A  = _BV(WGM10);       // Set to defaults so PWM can work like normal (PWM, phase corrected, 8bit).
  PWMT1PORT &= ~_BV(PWMT1AMASK); // Set timer 1 PWM pins to LOW.
  PWMT1PORT &= ~_BV(PWMT1BMASK); // Other timer 1 PWM pin also to LOW.  
  _tAC_Noise=false;
  *_tAC_NoiseCompleted=true; 
}

ISR(TIMER1_COMPA_vect) { // Timer interrupt vector.
  if (millis() >= _tAC_time) {
    noToneAC(); // Check to see if it's time for the note to end.
  }
  else  {
    // are we playing noise, if so update to a new random frequency and 
    if(_tAC_Noise)
          setnoiseAC();      
  }
}