/*
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/* 
 * ParticleSys.h - generic particle system class
 */

#ifndef p_system_h
#define p_system_h

#include "ParticleSysConfig.h"
#include "Particle_Abstract.h"
#include "Emitter_Abstract.h"

// use this as the main .h file, so we will include all the .h files of the project
#include "Particle_Attractor.h"
#include "Particle_Bounce.h"
#include "Particle_Fixed.h"
#include "Particle_Std.h"
#include "Emitter_Fire.h"
#include "Emitter_Fixed.h"
#include "Emitter_Fountain.h"
#include "Emitter_Side.h"
#include "Emitter_Spin.h"
#include "FastLEDRenderer.h"


class ParticleSys {
public:
    static byte perCycle;
    ParticleSysConfig *g;
    byte numParticles;
    Particle_Abstract *particles;
    Emitter_Abstract *emitter;

    ParticleSys(ParticleSysConfig *g, byte numParticles, Particle_Abstract particles[], Emitter_Abstract *emitter);
    void update();

private:
    byte cycleRemaining;
};

#endif /* p_system_h */
