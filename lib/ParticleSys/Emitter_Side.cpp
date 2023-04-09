/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/*
 * Emitter_Side.cpp - emit particles from one side of the box
 */

#include "Emitter_Side.h"

byte Emitter_Side::baseHue = 128; //blues
byte Emitter_Side::maxTtl = 128;

Emitter_Side::Emitter_Side(char side)
{
    counter = 0;
    this->side = side;
    this->minVelocity = 1;
    this->maxVelocity = 4;
}
Emitter_Side::Emitter_Side(char side, uint8_t minVelocity, uint8_t maxVelocity) {
    counter = 0;
    this->side = side;
    this->minVelocity = minVelocity;
    this->maxVelocity = maxVelocity;
}

void Emitter_Side::emit(Particle_Abstract *particle, ParticleSysConfig *g)
{
    counter++;

    switch(side) {
    case 'b':
        particle->x = random(g->max_x);
        particle->y = g->max_y-g->res_y;
        particle->vx = 0;
        particle->vy = random(-maxVelocity,(-minVelocity)+1);
        break;
    case 'r':
        particle->x = g->max_x-g->res_x;
        particle->y = random(g->max_y);
        particle->vx = random(-maxVelocity,(-minVelocity)+1);
        particle->vy = 0;
        break;
    case 't':
        particle->x = random(g->max_x);
        particle->y = 1;
        particle->vx = 0;
        particle->vy = random(minVelocity,maxVelocity+1);
        break;
    case 'l':
        particle->x = 1;
        particle->y = random(g->max_y);
        particle->vx = random(minVelocity,maxVelocity+1);
        particle->vy = 0;
        break;
    }

    particle->ttl = random(1, maxTtl);
    particle->hue = baseHue;
    particle->isAlive = true;
}
