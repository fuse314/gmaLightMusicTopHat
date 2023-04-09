/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/*
 * Particle_Std.cpp - standard particle, dies when out of bounds
 */

#include "Particle_Std.h"

int16_t Particle_Std::ax = 0;
int16_t Particle_Std::ay = 0;

Particle_Std::Particle_Std()
{
    isAlive = 0;
}

void Particle_Std::update(ParticleSysConfig *g)
{
    //age
    ttl--;

    //apply acceleration
    vx = min(vx+ax, g->max_x);
    vy = min(vy+ay, g->max_y);

    //apply velocity
    uint16_t newX, newY;
    newX = x + vx;
    newY = y + vy;
    if(ttl == 0 || newX < 0 || newX > g->max_x || newY < 0 || newY > g->max_y) {
        isAlive = 0;
    } else {
        x = newX;
        y = newY;
    }
}

