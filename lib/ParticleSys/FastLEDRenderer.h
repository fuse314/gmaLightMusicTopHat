/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/* Adaptation for FastLED by Gottfried Mayer github.com/fuse314 */

/**
 * FastLEDRenderer.h renders a particle system to a FastLED RGB matrix
 */

#ifndef psys_fastled_renderer_h
#define psys_fastled_renderer_h

#include "ParticleSysConfig.h"
#include "Particle_Abstract.h"
#include <FastLED.h>

class FastLEDRenderer {
public:
    FastLEDRenderer(ParticleSysConfig *g);
	FastLEDRenderer(ParticleSysConfig *g, uint8_t left, uint8_t top, uint8_t width, uint8_t height);
	FastLEDRenderer(ParticleSysConfig *g, uint8_t left, uint8_t top, uint8_t width, uint8_t height, uint8_t crop_left, uint8_t crop_top);
    void render(ParticleSysConfig *g, Particle_Abstract particles[], byte numParticles, CRGB *_leds);
    void reset(CRGB *_leds);    //set each pixel to 0
    void fade(CRGB *_leds);     //divide each pixel by half
    void fadeBy(byte amount, CRGB *_leds); //substract amount from each pixel
    uint8_t globalBrightness;
private:
	uint8_t left,top,width,height,crop_left,crop_top;
	void init(ParticleSysConfig *g, uint8_t left, uint8_t top, uint8_t width, uint8_t height, uint8_t crop_left, uint8_t crop_top);
    void addColor(byte col, byte row, CRGB *rgb, byte value, CRGB *_leds);
    uint8_t calcTempVal(ParticleSysConfig *g, uint16_t dx, uint16_t dy, uint8_t ttl);
};

// we need to declare this function here, otherwise there are errors while compiling...
extern uint16_t XY(uint8_t x, uint8_t y);

#endif /* psys_fastled_renderer_h */