#ifndef ZGLOBALS_H
#define ZGLOBALS_H
#include <stdint.h>

#define M_HEIGHT 8
#define M_WIDTH 64
#define M_HALFWIDTH (M_WIDTH/2)
#define NUM_LEDS (M_HEIGHT * M_WIDTH)

#define DELAY_NORMAL 7
#define DELAY_FAST 4
#define DELAY_SLOW 18
#define DELAY_FIRE 10
#define DELAY_KR 10

#define NORMBRIGHT 32  // maximum brightness of leds (0-255)

#define FASTLED_ALLOW_INTERRUPTS 0

#define DIMSPEED 16     // the higher the faster
//#define DIMSPEED_KR 35

// this value overwrites the bright white color when loud noise is present with a rainbow color, dimmed according to loudness
// as soon as the average loudness level (0-255) of eq7Vol is greater than (AUDIO_RAINBOW_LVL), the sound color is replaced with the rainbow color.
#define AUDIO_RAINBOW_LVL 170   // set this to 256 to disable rainbow colors in GetEQColor(...)

uint16_t XY( uint8_t x, uint8_t y);

// configuration class to be passed to step() function
struct Config_t {
  uint16_t currFrame;
  uint8_t  currHue;
  uint8_t  currDelay;
  uint8_t  currMode;
  uint8_t  currBright;
  
  uint8_t eq8Band[8]; // 0=low, 8=high
  uint8_t eqVol[3];  // low(<=400), mid(1k-2.5k), high(>=6.25k)
};

extern uint8_t soundForEveryone;

// comment out to get RF24 module working
//#define NOWIRELESS

#endif
