/* 
 * Copyright (C) 2013 Gilad Dayagi.  All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 */

#include "ParticleSysConfig.h"

ParticleSysConfig::ParticleSysConfig(uint8_t width, uint8_t height) {
    this->width = width;
    this->height = height;
    this->res_x = 32;        // default resolution
    this->res_y = 32;
    calcValues();
}
ParticleSysConfig::ParticleSysConfig(uint8_t width, uint8_t height, uint8_t res_x, uint8_t res_y) {
    this->width = width;
    this->height = height;
    this->res_x = res_x;
    this->res_y = res_y;
    calcValues();
}

void ParticleSysConfig::calcValues(void) {
    this->res_area = this->res_x*this->res_y;
    this->max_x = (this->width * this->res_x - 1);
    this->max_y = (this->height * this->res_y - 1);
    this->center_x = (this->max_x/2)-(this->res_x/2);
    this->center_y = (this->max_y/2)-(this->res_y/2);
}
