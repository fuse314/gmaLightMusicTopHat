/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */
 
/*
 * Emitter_Fixed.h - emit a particle with the same parameters each time
 */

#ifndef emitter_fixed_h
#define emitter_fixed_h

#include "Emitter_Abstract.h"
#include <Arduino.h>

class Emitter_Fixed : public Emitter_Abstract {
public:
    unsigned int counter;
    uint16_t x;
    uint16_t y;
    int16_t vx;
    int16_t vy;
    byte ttl;

    Emitter_Fixed(uint16_t x, uint16_t y, int16_t vx, int16_t vy, byte ttl);
    void emit(Particle_Abstract *particle, ParticleSysConfig *g);
};

#endif /* emitter_fixed_h */
