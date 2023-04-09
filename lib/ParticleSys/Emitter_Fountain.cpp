/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/*
 * Emitter_Fountain.cpp - a fountain of particles
 */

#include "Emitter_Fountain.h"

byte Emitter_Fountain::minLife = 50;
byte Emitter_Fountain::maxLife = 250;

Emitter_Fountain::Emitter_Fountain(int16_t vx, int16_t vy, byte var, Particle_Abstract *source)
{
    this->vx = vx;
    this->vy = vy;
    this->var = var;
    this->_hVar = (var>>1);
    this->source = source;
    _constVel = 0;
    counter = 0;
    
}
Emitter_Fountain::Emitter_Fountain(uint16_t constVel, Particle_Abstract *source)
{
    this->vx = 0;
    this->vy = 0;
    this->var = 0;
    if(constVel > 32767) { constVel = 32767; }
    _constVel = constVel;
    this->_hVar = (_constVel<<1);
    this->source = source;
    counter = 0;
}

void Emitter_Fountain::update(ParticleSysConfig *g)
{
    source->update(g);
}

void Emitter_Fountain::emit(Particle_Abstract *particle, ParticleSysConfig *g)
{
    counter++;
    source->update(g);

    particle->x = source->x;
    particle->y = source->y;
    if(_constVel > 0) {
        particle->vx = random(_hVar)-_constVel;
        particle->vy = sqrt(pow(_constVel,2)-pow(particle->vx,2));
        if(random(8)<3) { particle->vy=-particle->vy; }
    } else {
        particle->vx = vx + random(var)-_hVar;
        particle->vy = vy + random(var)-_hVar;
    }
    particle->ttl = random(minLife, maxLife);
    particle->hue = (counter/2)%255;
    particle->isAlive = true;
}
