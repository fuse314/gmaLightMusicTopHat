/*
  Three LED Strips mounted on hat for music festivals
  using Teensy FFT library and microphone to react to music
  (c) 2012-2015 by Gottfried Mayer www.gma.name
  
  Uses FastLED to control WS2811 controller chips
  
  Inspiration from here:
  http://www.macetech.com/blog/node/118
  
  Codebase from here:
  https://github.com/fuse314/gmaLightMusicHat/
*/

#include "gmaLightMusicTopHat.h"
#include "zGlobals.h"
#include "LEDColorMgt.h"
#include "TeensyFFTMgt.h"
#include "ModeButtonMgt.h"
#include "zEffectClass.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RF24.h>
#include <gmaRGBLight.h>
#include "nRFMgt.h"


// LED stuff
#include <FastLED.h>

#ifdef SerialDebug
#include <Streaming.h>
#endif

// button stuff
#include <OneButton.h>

CRGB leds[NUM_LEDS];

EffectClass *currEffect;

uint8_t autoModeChange;
uint32_t lastAutoModeChangeTime;
uint8_t soundForEveryone;

Config_t cnf;

TeensyFFTMgt eq;
ModeButtonMgt modeMgt;

// setup button
//OneButton modeButton(MODEBUTTON_PIN,true);

void setup()
{
  //FastLED library
  LEDS.addLeds<WS2811, LED1_PIN, GRB>(leds, 0,NUM_LEDS_HALF); //.setCorrection(TypicalLEDStrip);
  LEDS.addLeds<WS2811, LED2_PIN, GRB>(leds, NUM_LEDS_HALF,NUM_LEDS_HALF); //.setCorrection(TypicalLEDStrip);
  clearLeds(&leds[0], NUM_LEDS);
  //clearLeds(&ledsrow[0], M_WIDTH);
  LEDS.show();  // push black
  
  //initialize MSGEQ7 chip
  eq.InitFFT();
  
  soundForEveryone = 0;
  //RF24 stuff
  RF_Init();
  
  //button stuff
//  modeButton.setClickTicks(300);
//  modeButton.attachClick(modeMgt.ModeButton_Click);
//  modeButton.attachDoubleClick(modeMgt.ModeButton_DoubleClick);
//  modeButton.attachLongPressStart(modeMgt.ModeButton_Hold);

  //mode stuff
  cnf.currFrame = 0;
  cnf.currHue = 0;
  autoModeChange = 0; // default 1
  lastAutoModeChangeTime = 0;
  cnf.currMode = 15;  // first mode to run
  modeMgt.InitCurrMode(&cnf);
  
  #ifdef SerialDebug
  Serial.begin(9600);
  Serial << "Setup done" << endl;
  //cnf.debug = 1;
  #endif
}

void loop() {
  
  // call effect loop
  currEffect->step(&cnf, leds);
  if(LEDS.getBrightness() != cnf.currBright) {  // update global brightness
    LEDS.setBrightness(cnf.currBright);
  }
  // push pixels to led strip
  LEDS.show();
  // increment currFrame after effect loop - these variables will roll over
  cnf.currFrame++;
  cnf.currHue++;
  
  // random modes every 100 frames, fire mode every 20 frames
  /*if(((cnf.currMode > 14) && (cnf.currFrame % 100 == 0)) || ((cnf.currMode >= 22) && (cnf.currFrame % 13 == 0))) {
    random16_add_entropy(analogRead(A3));   // re-initialize random numbers
  }*/
  
  if((soundForEveryone == 1) || (cnf.currMode <= 11/* sound */) || 
     (cnf.currMode == 21 /* kr */) || (cnf.currMode == 24/* fire */)) {
    eq.GetFFT(&cnf);
  }
  
  // check if any buttons have been pressed
//  modeButton.tick();
  
  #ifdef SerialDebug
    if(cnf.currFrame % 200 == 0) {
      Serial << "m=" << cnf.currMode << " d=" << cnf.currDelay << endl;
    }
  #endif
  
  //RF24 stuff
  RF_Read();
  
  if(soundForEveryone == 1) {
    RF_SoundForEveryone(&cnf);
  }
    
  // only check random mode change every currDelay*150 milliseconds, default 1050 ms (one second)
  if(autoModeChange == 1 && cnf.currFrame % 150 == 0) {
    modeMgt.CheckAutoModeChange();
  }
  FastLED.delay(cnf.currDelay);
}


uint16_t XY( uint8_t x, uint8_t y)
{
  // offset x by width/4 pixels,
  //to have the center of the animation in the center of the first of two panels
  if(x < (M_WIDTH/4)) {
    x = x+(M_WIDTH/4*3);
  } else {
    x = x - (M_WIDTH/4);
  }
  uint16_t ret;
  // wrap around horizontally
  if(x >= M_WIDTH) { x = x % M_WIDTH; }
  // block wrap vertically
  if(y >= M_HEIGHT) { y = M_HEIGHT-1; }
  if(x & 0x01) { // odd columns run backwards
    ret = (x * M_HEIGHT) + ((M_HEIGHT - 1) - y);
  } else {
    ret = (x * M_HEIGHT) + y;
  }
  return ret;
}

