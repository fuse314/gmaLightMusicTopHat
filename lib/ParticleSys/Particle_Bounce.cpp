/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/*
 * particle.cpp - a particle that bounces off the "box" walls
 */

#include "Particle_Bounce.h"

int16_t Particle_Bounce::ax = 0;
int16_t Particle_Bounce::ay = 0;

Particle_Bounce::Particle_Bounce()
{
    isAlive = 0;
}

void Particle_Bounce::update(ParticleSysConfig *g)
{
    //age
    ttl--;

    //apply acceleration
    vx = min(vx + ax, g->max_x);
    vy = min(vy + ay, g->max_y);

    //apply velocity
    if (y == 0 || y >= g->max_y) {
        vy = -1 * vy;
    }
    if (x == 0 || x >= g->max_x) {
        vx = -1 * vx;
    }
    if (ttl == 0 || (vx == 0 && vy == 0)) {
        isAlive = 0;
    } else {
        x = min(max(x + vx, 0), g->max_x);
        y = min(max(y + vy, 0), g->max_y);
    }
}

