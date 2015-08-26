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
#include <SerialFlash.h>
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
  eff_fire1,        // 0
  eff_fire2,        // 1
  eff_soundFire,    // 2
  eff_redKR,        // 3
  eff_rainbowKR,    // 4
  eff_soundKR,      // 5
  eff_starfield,    // 6
  eff_rainingUp,    // 7
  eff_rainingDown,  // 8
  eff_hRainbow,     // 9
  eff_weirdRainbow, //10
  eff_horizRain,    //11
  eff_slantedBars,  //12
  eff_colorSparks,  //13
  eff_whiteSparks,  //14
  eff_slowRNDLines, //15
  eff_quickRNDLines,//16
  eff_redwave,      //17
  eff_redgreenwave, //18
  eff_rainbowwave,  //19
  eff_eqColorSnd,   //20
  eff_rainbowSnd,   //22
  eff_blueRedSnd,   //23
  eff_greenBlueSnd, //24
  eff_policeSnd,    //25
  eff_redBrightSnd, //26
  eff_greenBlueBrightSnd //27
};


#include "ModeButtonMgt.h"

#define SerialDebug

#ifdef SerialDebug
#include <Streaming.h>
#endif

// button stuff
//#include <OneButton.h>

// setup button
//OneButton modeButton(MODEBUTTON_PIN,true);

void setup()
{
  delay(3000);  // wait for things to settle down...
  
  //FastLED library
  FastLED.addLeds<OCTOWS2811>(leds, OCTO_LEDS_PER_STRIP).setCorrection(TypicalLEDStrip);
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
  cnf.currMode = 14;  // first mode to run
  cnf.isModeInit = false;
  
  #ifdef SerialDebug
  Serial.begin(115200);
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
  
  EVERY_N_SECONDS( 1 ) { random16_add_entropy(cnf.eq8Band[3]); }  // re-initialize random numbers
  GetFFT(&cnf);
  
  // check if any buttons have been pressed
//  modeButton.tick();
  
  #ifdef SerialDebug
    EVERY_N_MILLISECONDS( 800 ) {
      Serial << "m=" << cnf.currMode << " d=" << cnf.currDelay << endl;
    }
  #endif
  
  //RF24 stuff
  RF_Read();
  
  if(soundForEveryone == 1) {
    RF_SoundForEveryone();
  }
  
  // only check random mode change every currDelay*150 milliseconds, default 1050 ms (one second)
  EVERY_N_SECONDS( 2 ) {
    if(autoModeChange == 1) {
      CheckAutoModeChange();
    }
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

