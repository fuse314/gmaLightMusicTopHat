/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

/*
 * Particle_Std.h - standard particle, dies when out of bounds
 */

#ifndef particle_std_h
#define particle_std_h

#include "Particle_Abstract.h"

class Particle_Std : public Particle_Abstract {
public:
    static int16_t ax; //horizontal acceleration
    static int16_t ay; //vertical acceleration

    Particle_Std();
    void update(ParticleSysConfig *g);
};

#endif /* particle_std_h */
