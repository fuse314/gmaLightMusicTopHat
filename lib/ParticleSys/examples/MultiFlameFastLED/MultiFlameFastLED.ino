/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

 /*
  * An example for the Arduino particle system library
  * example with multiple particle systems, creates multiple flames
  */

#include <FastLED.h>

#define LED_WIDTH 8
#define LED_HEIGHT 8

// set ledSerpentineLayout to true if your matrix looks wrong ;) - see Example "XYMatrix" in FastLED library.
const bool ledSerpentineLayout = false;  
// translates from x, y into an index into the LED array
uint16_t XY( uint8_t x, uint8_t y) {
  if(y >= LED_HEIGHT) { y = LED_HEIGHT - 1; }
  if(x >= LED_WIDTH) { x = LED_WIDTH - 1; }
  uint16_t ret;
  if(ledSerpentineLayout == false) {
    ret = (y * LED_WIDTH) + x;
  } else {
    if( y & 0x01) {
      // Odd rows run backwards
      uint8_t revX = (LED_WIDTH - 1) - x;
      ret = (y * LED_WIDTH) + revX;
    } else {
      // Even rows run forwards
      ret = (y * LED_WIDTH) + x;
    }
  }
  return ret;
}

// Particle System

#include <ParticleSys.h>

#define NUM_LEDS    (LED_WIDTH * LED_HEIGHT)
#define LED_PIN     7
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define BRIGHTNESS  32
CRGB leds[ NUM_LEDS ];

// particle system 1
const byte numParticles = 60;

ParticleSysConfig g(LED_WIDTH, LED_HEIGHT);
Particle_Std particles[numParticles];
Particle_Fixed source;
Emitter_Fountain emitter(0, 0, 5, &source);
ParticleSys pSys(&g, numParticles, particles, &emitter);

// particle system 2, we can use the same ParticleSysConfig as in Particle system 1
const byte numParticles2 = 25;

Particle_Std particles2[numParticles2];
Particle_Fixed source2;
Emitter_Fountain emitter2(0,0,5, &source2);
ParticleSys pSys2(&g, numParticles2, particles2, &emitter2);

// we only need one renderer.
FastLEDRenderer renderer(&g);


void setup() {
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness( BRIGHTNESS );

  randomSeed(analogRead(0));
  
  renderer.reset(leds);
    
  Particle_Std::ay = -1;  // this affects all particles.
  
  pSys.perCycle = 10;  // particles emitted every cycle
  emitter.minLife = 20;
  emitter.maxLife = 80;
  source.x = g.center_x+(g.res_x/2); // center and 1/2 pixel to the right
  source.y = g.max_y-(g.res_y/2);  // lowest pixel

  
  pSys2.perCycle = 7;  // particles emitted every cycle
  emitter2.minLife = 20;
  emitter2.maxLife = 70;
  source2.x = g.center_x-(g.res_x/2); // center and 1/2 pixel to the left
  source2.y = g.max_y-(g.res_y/2)-(g.res_y*3); // lowest pixel and three pixels up
}

void loop() {
    pSys.update();
    pSys2.update();
    renderer.reset(leds);
    renderer.render(&g, particles, numParticles, leds);  // render first particle system
    renderer.render(&g, particles2, numParticles2, leds);  // render second particle system
    FastLED.show();
    delay(30);
}

