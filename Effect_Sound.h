//mode 1: volume dependent width, eqColor bars
//mode 2: volume dependent width, rainbow bars
//mode 6: volume dependent width, volume dependent color blue to red bars
//mode 7: volume dependent width, volume dependent color green to blue bars
//mode 8: volume dependent width, red bars with blue background
//mode 9: volume dependent brightness, red solid color per row
//mode 10: volume dependent brightness, volume dependent color green to blue per row

void eff_eqColorSnd() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_NORMAL;
    cnf.currBright = NORMBRIGHT;
    cnf.isModeInit = true;
  }
  clearLeds(&leds[OCTO_OFFSET], NUM_LEDS);
  currColor = GetEQColor(&cnf);
  for(uint8_t i=0; i<M_HEIGHT; i++) {
    if(cnf.eq8Band[i] > 0) {
      uint8_t soundlvl = map(cnf.eq8Band[i], 1, 255, 1, M_HALFWIDTH);
      for(uint8_t j=0; j<soundlvl; j++) {
        leds[XY(M_HALFWIDTH-j-1,i)] = currColor;
        leds[XY(M_HALFWIDTH+j,i)] = currColor;
      }
    }
  }
}

void eff_rainbowSnd() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_NORMAL;
    cnf.currBright = NORMBRIGHT;
    cnf.isModeInit = true;
  }
  clearLeds(&leds[OCTO_OFFSET], NUM_LEDS);
  currColor = CHSV(cnf.currHue,255,255);
  for(uint8_t i=0; i<M_HEIGHT; i++) {
    if(cnf.eq8Band[i] > 0) {
      uint8_t soundlvl = map(cnf.eq8Band[i], 1, 255, 1, M_HALFWIDTH);
      for(uint8_t j=0; j<soundlvl; j++) {
        leds[XY(M_HALFWIDTH-j-1,i)] = currColor;
        leds[XY(M_HALFWIDTH+j,i)] = currColor;
      }
    }
  }
}

void eff_blueRedSnd() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_NORMAL;
    cnf.currBright = NORMBRIGHT;
    currPalette = CRGBPalette16(CRGB::Blue, CRGB::Red);
    cnf.isModeInit = true;
  }
  clearLeds(&leds[OCTO_OFFSET], NUM_LEDS);
  for(uint8_t i=0; i<M_HEIGHT; i++) {
    if(cnf.eq8Band[i] > 0) {
      currColor = ColorFromPalette(currPalette, cnf.eq8Band[i]);
      uint8_t soundlvl = map(cnf.eq8Band[i], 1, 255, 1, M_HALFWIDTH);
      for(uint8_t j=0; j<soundlvl; j++) {
        leds[XY(M_HALFWIDTH-j-1,i)] = currColor;
        leds[XY(M_HALFWIDTH+j,i)] = currColor;
      }
    }
  }
}

void eff_greenBlueSnd() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_NORMAL;
    cnf.currBright = NORMBRIGHT;
    currPalette = CRGBPalette16(CRGB::Green, CRGB::Blue);
    cnf.isModeInit = true;
  }
  clearLeds(leds, NUM_LEDS);
  for(uint8_t i=0; i<M_HEIGHT; i++) {
    if(cnf.eq8Band[i] > 0) {
      currColor = ColorFromPalette(currPalette, cnf.eq8Band[i]);
      uint8_t soundlvl = map(cnf.eq8Band[i], 1, 255, 1, M_HALFWIDTH);
      for(uint8_t j=0; j<soundlvl; j++) {
        leds[XY(M_HALFWIDTH-j-1,i)] = currColor;
        leds[XY(M_HALFWIDTH+j,i)] = currColor;
      }
    }
  }
}

void eff_policeSnd() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_NORMAL;
    cnf.currBright = LOWBRIGHT;
    cnf.isModeInit = true;
  }
  setColor(CRGB(0,0,80),&leds[OCTO_OFFSET],NUM_LEDS); // blue base color
  currColor = CRGB(255,0,0); // red bar
  for(uint8_t i=0; i<M_HEIGHT; i++) {
    if(cnf.eq8Band[i] > 0) {
      uint8_t soundlvl = map(cnf.eq8Band[i], 1, 255, 1, M_HALFWIDTH);
      for(uint8_t j=0; j<soundlvl; j++) {
        leds[XY(M_HALFWIDTH-j-1,i)] = currColor;
        leds[XY(M_HALFWIDTH+j,i)] = currColor;
      }
    }
  }
}

void eff_redBrightSnd() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_NORMAL;
    cnf.currBright = LOWBRIGHT;
    cnf.isModeInit = true;
  }
  for(uint8_t i=0; i<M_HEIGHT; i++) {
    if(cnf.eq8Band[i] > 0) {
      currColor = CRGB(cnf.eq8Band[i],0,0);  // red, dependent on volume
    } else {
      currColor = CRGB(0,0,0);
    }
    for(uint8_t j=0; j<M_WIDTH; j++) {
      leds[XY(j,i)] = currColor;
    }
  }
}

void eff_greenBlueBrightSnd() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_NORMAL;
    cnf.currBright = NORMBRIGHT;
    currPalette = CRGBPalette16(CRGB::Blue, CRGB::Green);
    cnf.isModeInit = true;
  }
  for(uint8_t i=0; i<M_HEIGHT; i++) {
    if(cnf.eq8Band[i] > 0) {
      //      from green(256) to blue(511)  , dim from 0-255 depending on volume
      currColor = ColorFromPalette(currPalette,cnf.eq8Band[i]).nscale8(cnf.eq8Band[i]);
    } else {
      currColor = CRGB(0,0,0);
    }
    for(uint8_t j=0; j<M_WIDTH; j++) {
      leds[XY(j,i)] = currColor;
    }
  }
}

