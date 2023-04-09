/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/*
 * Emitter_Fire.cpp - emit particles to simulate fire
 */

#include "Emitter_Fire.h"

uint8_t Emitter_Fire::baseHue = 128; //blues
uint8_t Emitter_Fire::maxTtl = 128;

Emitter_Fire::Emitter_Fire()
{
    counter = 0;
    cycleHue = false;
}

void Emitter_Fire::update(ParticleSysConfig *g)
{
}

void Emitter_Fire::emit(Particle_Abstract *particle, ParticleSysConfig *g)
{
    counter++;
    if (cycleHue) baseHue = (counter>>2)%240;

    if ((counter & 0x01) == 0) {
        particle->x = random(g->max_x/4, 3 * (g->max_x/4));
        switch (map(particle->x, 0, g->max_x, 0, 9)) {  // map value of x from full range to range of 0-8
        case 0:
        case 7:
            particle->ttl = random(1, 7);
            break;
        case 1:
        case 6:
            particle->ttl = random(5, 14);
            break;
        case 2:
        case 5:
            particle->ttl = random(15, 21);
            break;
        case 3:
        case 4:
            particle->ttl = random(25, 28);
            break;
        }
        particle->hue = baseHue+16;
    } else {
        particle->x = random(g->res_x,g->max_x-g->res_x);
        switch (map(particle->x, 0, g->max_x, 0, 9)) {  // map value of x from full range to range of 0-8
        case 0:
        case 7:
            particle->ttl = random(1, 20);
            break;
        case 1:
        case 6:
            particle->ttl = random(5, 40);
            break;
        case 2:
        case 5:
            particle->ttl = random(20, 70);
            break;
        case 3:
        case 4:
            particle->ttl = random(40, 100);
            break;
        }
        particle->hue = baseHue;
    }

    particle->y = g->max_y-1;

    particle->vx = 0;
    particle->vy = 0;


    particle->isAlive = true;
}
