/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/* Adaptation for FastLED by Gottfried Mayer github.com/fuse314 */

/*
 * FastLEDRenderer.cpp renders a particle system to an RGB matrix
 * Params:
 * left/top: origin point on LED matrix to start rendering the particle system
 * width/height: width and height of "window" to particle system to render
 * crop_left/crop_top: origin point in particle system to start rendering
 *
 * see example CroppedPainterFastLED
 */

#include "FastLEDRenderer.h"

FastLEDRenderer::FastLEDRenderer(ParticleSysConfig *g) {
	init(g, 0, 0, g->width, g->height, 0, 0);
}
FastLEDRenderer::FastLEDRenderer(ParticleSysConfig *g, uint8_t left, uint8_t top, uint8_t width, uint8_t height) {
	init(g, left, top, width, height, 0, 0);
}
FastLEDRenderer::FastLEDRenderer(ParticleSysConfig *g, uint8_t left, uint8_t top, uint8_t width, uint8_t height, uint8_t crop_left, uint8_t crop_top) {
	init(g, left, top, width, height, crop_left, crop_top);
}

void FastLEDRenderer::init(ParticleSysConfig *g, uint8_t left, uint8_t top, uint8_t width, uint8_t height, uint8_t crop_left, uint8_t crop_top) {
	this->left = left;
	this->top = top;
	if(width > g->width || width == 0) { width = g->width; }  // sanity check for width
	if(height > g->height || height == 0) { height = g->height; }  // sanity check for height
	if(width + crop_left > g->width) { crop_left = 0; }  // sanity check for crop_left
	if(height + crop_top > g->height) { crop_top = 0; }  // sanity check for crop_top
	this->width = width;
	this->height = height;
	this->crop_left = crop_left;
	this->crop_top = crop_top;
    this->globalBrightness = 255;
}

/* GMA hier - change below ########################################################## */

void FastLEDRenderer::render(ParticleSysConfig *g, Particle_Abstract particles[], byte numParticles, CRGB *_leds) {
    byte row, col;
    uint16_t dx, dy;
    uint8_t tempVal;
    CRGB baseRGB;

    //go over particles and update matrix cells on the way
    for(int i = 0; i<numParticles; i++) {
        if (! particles[i].isAlive) {  // only render if particle is alive
            continue;
        }
        if(crop_left > 0 && crop_left * g->res_x > particles[i].x) {  // only render if x-position is inside cropped window
            continue;
        }
        if(crop_top > 0 && crop_top * g->res_y > particles[i].y) {  // only render if y-position is inside cropped window
            continue;
        }
        uint16_t part_x = particles[i].x - (crop_left * g->res_x);
        uint16_t part_y = particles[i].y - (crop_top * g->res_y);
        //generate RGB values for particle
        baseRGB = CHSV(particles[i].hue, 255,255);

        dx = g->res_x - (part_x % g->res_x);
        dy = g->res_y - (part_y % g->res_y);

        //bottom left
        col = part_x / g->res_x;
        row = part_y / g->res_y;
        tempVal = calcTempVal(g,dx,dy,particles[i].ttl);
        addColor(col, row, &baseRGB, tempVal, _leds);

        //bottom right;
        col++;
        if (col < g->width) {
            tempVal = calcTempVal(g,(g->res_x-dx),dy,particles[i].ttl);
            addColor(col, row, &baseRGB, tempVal, _leds);
        }

        //top right
        row++;
        if (col < g->width && row < g->height) {
            tempVal = calcTempVal(g,(g->res_x-dx),(g->res_y-dy),particles[i].ttl);
            addColor(col, row, &baseRGB, tempVal, _leds);
        }

        //top left
        col--;
        if (row < g->height) {
            tempVal = calcTempVal(g,dx,(g->res_y-dy),particles[i].ttl);
            addColor(col, row, &baseRGB, tempVal, _leds);
        }
    }
}

uint8_t FastLEDRenderer::calcTempVal(ParticleSysConfig *g, uint16_t dx, uint16_t dy, uint8_t ttl) {
    uint8_t _ttl = ttl;
    if(globalBrightness < 255) {
        _ttl = scale8(_ttl,globalBrightness);
    }
    unsigned long r = ((unsigned long)dx*dy*_ttl)/g->res_area;
    if(r > 255)
        return 255;
    return r;
}

void FastLEDRenderer::addColor(byte col, byte row, CRGB *colorRGB, byte value, CRGB *_leds) {
    if(col >= width || row >= height) // check if pixel is outside of the render area
      return;
    // add colorRGB with intensity of value at position (col, row) to the existing RGB value
    CRGB newColor = colorRGB[0];
    newColor.fadeToBlackBy(255-value);
    _leds[XY(left+col,top+row)] += newColor;
}

void FastLEDRenderer::reset(CRGB *_leds) {
    //init all pixels to black
    for(byte y=top; y<top+height; y++) {
        for(byte x=left; x<left+width; x++) {
            _leds[XY(x,y)] = CRGB(0,0,0);
        }
    }
}

void FastLEDRenderer::fade(CRGB *_leds) {
    //fade all pixels
    for (byte y=top; y<top+height; y++) {
        for(byte x=left; x<left+width; x++) {
            _leds[XY(x,y)].fadeToBlackBy(128);
        }
    }
}

void FastLEDRenderer::fadeBy(byte amount, CRGB *_leds) {
    //fade all pixels
    for (byte y=top; y<top+height; y++) {
        for(byte x=left; x<left+width; x++) {
            _leds[XY(x,y)].fadeToBlackBy(amount);
        }
    }
}
