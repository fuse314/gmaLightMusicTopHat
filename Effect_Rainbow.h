//mode 1: rainbow all three rows the same
//mode 2: solid color rainbow all leds the same
//mode 3: rainbow through all leds, results in right-left-right run due to led configuration
//mode 4: horizontal rain
//mode 5: slanted bars

uint8_t rainbow_pos;

void effect_rainbow1() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_FAST;
    cnf.currBright = NORMBRIGHT;
    cnf.isModeInit = true;
  }
  for(uint8_t i=0;i<M_WIDTH;i++) {
    leds[XY(i,0)] = Wheel(cnf.currFrame); // fill_rainbow does not work with vertical matrix :(
  }
  copyRowToAll(leds);
}

void effect_rainbow2() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_FAST;
    cnf.currBright = NORMBRIGHT;
    cnf.isModeInit = true;
  }
  for(uint8_t i=0;i<M_WIDTH;i++) {
    leds[XY(i,0)] = Wheel(cnf.currFrame);
  }
  copyRowToAll(leds);
}

void effect_rainbow3() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_FAST;
    cnf.currBright = NORMBRIGHT;
    cnf.isModeInit = true;
  }
  fill_rainbow( &(leds[0]), NUM_LEDS, cnf.currFrame % 256);
}

void effect_rainbow4() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_KR;
    cnf.currBright = NORMBRIGHT;
    cnf.isModeInit = true;
  }
  shiftLeds(1, leds);
  for(uint8_t i=0;i<M_HEIGHT;i++) {
    leds[XY(M_WIDTH-1,i)] = CRGB::Black;
  }
  leds[XY(M_WIDTH-1,random8(M_HEIGHT))] = Wheel(cnf.currFrame);
}

void effect_rainbow5() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_FAST;
    cnf.currBright = NORMBRIGHT;
    cnf.isModeInit = true;
  }
  for(uint8_t i=0; i<M_WIDTH; i++) {
    for(uint8_t j=0; j<M_HEIGHT; j++) {
      leds[XY(i,j)] = CHSV(cnf.currHue,255,quadwave8((i*32)+(j*32)+rainbow_pos));
    }
  }
  rainbow_pos-=4;
}

