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

#define USE_OCTOWS2811
#include<OctoWS2811.h>
#define OCTO_LEDS_PER_STRIP 256
#define OCTO_STRIPS 8
#define OCTO_NUM_LEDS (OCTO_LEDS_PER_STRIP * OCTO_STRIPS)
// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5
// I am only using  7,8
#define OCTO_OFFSET (OCTO_LEDS_PER_STRIP * 2)

#include <FastLED.h>
#include "zGlobals.h"
Config_t cnf;

#include "LEDColorMgt.h"
#include "TeensyFFTMgt.h"
#include <ParticleSys.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <RF24.h>
#include <gmaRGBLight.h>
#include "nRFMgt.h"


// LED stuff
CRGB leds[OCTO_NUM_LEDS];
CRGBPalette16 currPalette;
CRGB currColor;

//effects
#include "Effect_Fire.h"
#include "Effect_KR.h"
#include "Effect_Particle.h"
#include "Effect_Rainbow.h"
#include "Effect_Random.h"
#include "Effect_Sine.h"
#include "Effect_Sound.h"

typedef void (*functionList)(); // definition for list of effect function pointers
#define numEffects (sizeof(effectList) / sizeof(effectList[0]))
functionList effectList[] = {
  effect_fire1,
  effect_fire2,
  effect_fire3,
  effect_KR1,
  effect_KR2,
  effect_KR3,
  effect_particle1,
  effect_particle2,
  effect_particle3,
  effect_rainbow1,
  effect_rainbow2,
  effect_rainbow3,
  effect_rainbow4,
  effect_rainbow5,
  effect_random1,
  effect_random2,
  effect_random3,
  effect_random4,
  effect_sine1,
  effect_sine2,
  effect_sine3,
  effect_sound1,
  effect_sound2,
  effect_sound3,
  effect_sound4,
  effect_sound5,
  effect_sound6,
  effect_sound7,
  effect_sound8,
  effect_sound9,
  effect_sound10
};


#include "ModeButtonMgt.h"

#define SerialDebug

#ifdef SerialDebug
#include <Streaming.h>
#endif

// button stuff
#include <OneButton.h>

// setup button
//OneButton modeButton(MODEBUTTON_PIN,true);

void setup()
{
  delay(3000);  // wait for things to settle down...
  
  //FastLED library
  /* OctoWS2811
  if(NUM_LEDS > LEDSPERSTRIP) {
    FastLED.addLeds<WS2811, LED1_PIN, GRB>(leds, 0,LEDSPERSTRIP).setCorrection(TypicalLEDStrip).setDither(0);
    uint16_t theRest = NUM_LEDS-LEDSPERSTRIP;
    if(theRest > LEDSPERSTRIP) { theRest = LEDSPERSTRIP; }
    FastLED.addLeds<WS2811, LED2_PIN, GRB>(leds, LEDSPERSTRIP,theRest).setCorrection(TypicalLEDStrip).setDither(0);
  } else {
    FastLED.addLeds<WS2811, LED1_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip).setDither(0);
  }
  */
  FastLED.addLeds<OCTOWS2811>(leds, OCTO_LEDS_PER_STRIP);
  clearLeds(&leds[OCTO_OFFSET], NUM_LEDS);
  LEDS.show();  // push black
  
  //initialize FFT functions
  InitFFT();
  
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
  autoModeChange = 1;
  lastAutoModeChangeTime = 0;
  cnf.currMode = 0;  // first mode to run
  cnf.isModeInit = false;
  
  #ifdef SerialDebug
  Serial.begin(9600);
  Serial << "Setup done" << endl;
  //cnf.debug = 1;
  #endif
}

void loop() {
  
  // call effect loop
  effectList[cnf.currMode](); // run selected effect
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
  
  //if((soundForEveryone == 1) || (cnf.currMode <= 11/* sound */) || 
  //   (cnf.currMode == 21 /* kr */) || (cnf.currMode == 24/* fire */)) {
    GetFFT(&cnf);
  //}
  
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
    RF_SoundForEveryone();
  }
    
  // only check random mode change every currDelay*150 milliseconds, default 1050 ms (one second)
  if(autoModeChange == 1 && cnf.currFrame % 150 == 0) {
    CheckAutoModeChange();
  }
  //FastLED.delay(cnf.currDelay);
  delay(cnf.currDelay);
}


uint16_t XY( uint8_t x, uint8_t y)
{
  // offset x by width/4 pixels,
  //to have the center of the animation in the center of the first of two panels
  if(x < M_XOFFSET) {
    x = x+(M_WIDTH-M_XOFFSET);
  } else {
    x = x - M_XOFFSET;
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
  return ret + OCTO_OFFSET;
}

