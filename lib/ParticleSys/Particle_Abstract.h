/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/*
 * particle.h - abstract particle class
 */

#ifndef particle_abstract_h
#define particle_abstract_h

#include "ParticleSysConfig.h"
#include <Arduino.h>

class Particle_Abstract {
public:
    uint16_t x;   //left
    uint16_t y;   //bottom
    int16_t  vx;  //horizontal velocity
    int16_t  vy;  //vertical velocity
    uint8_t ttl; //time to live
    uint8_t hue; //hue
    uint8_t isAlive; //is alive?

    virtual void update(ParticleSysConfig *g);
};

#endif /* particle_abstract_h */
