#pragma once

#define SerialDebug

#define LEDSPERSTRIP 256

#define M_HEIGHT 8
#define M_WIDTH 61
#define MAXDIM ((M_WIDTH > M_HEIGHT) ? M_WIDTH : M_HEIGHT)
#if (M_WIDTH & 0x01)
#define M_HALFWIDTH ((M_WIDTH + 1) / 2)
#else
#define M_HALFWIDTH (M_WIDTH / 2)
#endif
#define NUM_LEDS (M_HEIGHT * M_WIDTH)
#define M_XOFFSET 15
#define M_TXTWIDTH 120

#define LED1_PIN 7
#define LED2_PIN 8
#define NUM_LEDS_HALF (NUM_LEDS / 2)

#define DELAY_NORMAL 7
#define DELAY_FAST 4
#define DELAY_SLOW 15
#define DELAY_FIRE 20
#define DELAY_KR 13

#define NORMBRIGHT 32 // maximum brightness of leds (0-255)
#define LOWBRIGHT 23  // lower brightness for effects that use most of the LEDs

#define DIMSPEED 16 // the higher the faster

// this value overwrites the bright white color when loud noise is present with a rainbow color, dimmed according to loudness
// as soon as the average loudness level (0-255) of eq7Vol is greater than (AUDIO_RAINBOW_LVL), the sound color is replaced with the rainbow color.
#define AUDIO_RAINBOW_LVL 170 // set this to 256 to disable rainbow colors in GetEQColor(...)

uint16_t XY(uint8_t x, uint8_t y);

// configuration class to be passed to step() function
struct Config_t
{
  uint16_t currFrame;
  uint8_t currHue;
  uint8_t currDelay;
  uint8_t currMode;
  uint8_t currBright;
  uint8_t isModeInit;
  uint8_t canShowText;
  uint8_t eq8Band[8]; // 0=low, 8=high
  uint8_t eqVol[3];   // low(<=400), mid(1k-2.5k), high(>=6.25k)
};

// button stuff
#define MODEBUTTON_PIN 5
#define AUTOMODE_CHANGE 45000 // change every 45 seconds
