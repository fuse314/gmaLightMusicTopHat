/*
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/*
 * Emitter_Spin.cpp - a spinning emitter
 */

#include "Emitter_Spin.h"

byte Emitter_Spin::maxTtl = 100;

Emitter_Spin::Emitter_Spin(uint16_t x, uint16_t y, uint16_t r, int16_t rv)
{
    this->x = x;
    this->y = y;
    this->r = r;
    this->rv = tempRv = rv;
    oscilate = false;
    counter = 0;
}
Emitter_Spin::Emitter_Spin(ParticleSysConfig *g, uint16_t r, int16_t rv) {
    this->x = g->center_x;  // default position at center of particle system
    this->y = g->center_y;
    this->r = r;
    this->rv = tempRv = rv;
    oscilate = false;
    counter = 0;
}

void Emitter_Spin::update(ParticleSysConfig *g)
{
    static signed char direction = -1;
    float radAngle;
    counter++;

    //calculate velocity vector
    if (oscilate && (counter%20 == 0)){
        tempRv += direction;
        if (abs(tempRv) > rv){
            direction = -direction;
        }
    }

    // Conver from Degree -> Rad
    if (counter%2 == 0) {
        radAngle = -counter*tempRv*(PI/180) ;
    } else {
        radAngle = 180-counter*tempRv*(PI/180) ;
    }
    // Convert Polar -> Cartesian
    vx = (int16_t)(r * cos(radAngle));
    vy = (int16_t)(r * sin(radAngle));
}

void Emitter_Spin::emit(Particle_Abstract *particle, ParticleSysConfig *g)
{
    particle->x = this->x;
    particle->y = this->y;

    particle->vx = vx;
    particle->vy = vy;

    particle->ttl = random(20, maxTtl);
    particle->hue = (counter>>1)%255;
    particle->isAlive = true;
}
