/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#ifndef PS_GLOBALS_T
#define PS_GLOBALS_T
#include <stdint.h>

class ParticleSysConfig {
public:
    uint8_t width;
    uint8_t height;
    uint8_t res_x;
    uint8_t res_y;
    uint16_t res_area;
    uint16_t max_x;
    uint16_t max_y;
    uint16_t center_x;
    uint16_t center_y;
    ParticleSysConfig(uint8_t width, uint8_t height);
    ParticleSysConfig(uint8_t width, uint8_t height, uint8_t res_x, uint8_t res_y);
private:
    void calcValues(void);
};

#endif
