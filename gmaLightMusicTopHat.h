#ifndef MYCONFIG_H
#define MYCONFIG_H
#define FASTLED_ALLOW_INTERRUPTS 0

#include "zGlobals.h"
//#include <FastLED.h>
#include "zEffectClass.h"

//uncomment this for debug over serial port
#define SerialDebug

#ifdef SerialDebug
#include <Streaming.h>
#endif

extern CRGB leds[NUM_LEDS];
//extern CRGB ledsrow[M_WIDTH];  // used for mirrored effects and one-row-for-all effects
#define LED1_PIN 7
#define LED2_PIN 8
#define NUM_LEDS_HALF NUM_LEDS/2

//button stuff
#define MODEBUTTON_PIN 5

//effect stuff
extern EffectClass *currEffect;

extern Config_t cnf;

//auto mode change stuff
extern uint8_t autoModeChange;  // start in auto mode change mode
#define AUTOMODE_CHANGE 10000  // change every 60 seconds
extern uint32_t lastAutoModeChangeTime;

#ifdef SerialDebug
int freeRam ();  // function returns distance between stack and heap (available ram)
#endif
#endif
