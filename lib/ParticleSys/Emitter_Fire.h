/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/*
 * Emitter_Fire.h - emit particles to simulate fire
 */

#ifndef emitter_fire_h
#define emitter_fire_h

#include "Emitter_Abstract.h"
#include <Arduino.h>

class Emitter_Fire : public Emitter_Abstract {
public:
    static uint8_t baseHue;
    static uint8_t maxTtl;
    uint16_t counter;
    uint8_t cycleHue;

    Emitter_Fire();
    void emit(Particle_Abstract *particle, ParticleSysConfig *g);
    void update(ParticleSysConfig *g);
};

#endif /* emitter_fire_h */
