/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/* 
 * ParticleSys.cpp - generic particle system class
 */

#include "ParticleSys.h"

byte ParticleSys::perCycle = 1;

ParticleSys::ParticleSys(ParticleSysConfig *g, byte numParticles, Particle_Abstract particles[], Emitter_Abstract *emitter)
{
    this->g = g;
    this->numParticles = numParticles;
    this->particles = particles;
    this->emitter = emitter;
}

void ParticleSys::update()
{
    cycleRemaining = perCycle;
    emitter->update(this->g);
    for(byte i=0; i<numParticles; i++) {
        if (!particles[i].isAlive && cycleRemaining > 0) {
            emitter->emit(&particles[i], this->g);
            cycleRemaining--;
        }
        if (particles[i].isAlive){
            particles[i].update(this->g);
        }
    }
}

