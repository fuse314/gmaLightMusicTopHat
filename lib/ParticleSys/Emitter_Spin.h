/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/*
 * Emitter_Spin.h - a spinning emitter
 * works well with 36 particles
 */

#ifndef emitter_spin_h
#define emitter_spin_h

#include "Emitter_Abstract.h"
#include <Arduino.h>

class Emitter_Spin : public Emitter_Abstract {
public:
    static byte maxTtl;
    uint16_t x;   //left
    uint16_t y;   //bottom
    uint16_t r;   //radius
    int16_t rv;  //radial velocity
    boolean oscilate; //whether to oscilate radial velocity
    unsigned int counter;
    Emitter_Spin(uint16_t x, uint16_t y, uint16_t r, int16_t rv);
    Emitter_Spin(ParticleSysConfig *g, uint16_t r, int16_t rv);
    void emit(Particle_Abstract *particle, ParticleSysConfig *g);
    void update(ParticleSysConfig *g);
private:
    int16_t vx;
    int16_t vy;
    int16_t tempRv;
};

#endif /* emitter_spin_h */
