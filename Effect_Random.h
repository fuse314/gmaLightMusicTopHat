//mode 1: random pixels effect
//mode 2: random white "stars" effect
//mode 3: random color lines (quick fade in, slow fade out)
//mode 4: random color lines (slow fade in, slow fade out)

#define RANDOM_NUM_LINES 9  // number of random lines (mode x)
uint8_t random_dimspeed;
struct rndline_t {
  uint16_t start;       // start index
  uint8_t  length;      // length
  uint8_t  hue;         // hue
  uint8_t  anim_idx;    // animation index (brightness)
  uint8_t  anim_speed;  // animation speed
};
rndline_t random_rndLines[RANDOM_NUM_LINES];  // array of random line variables

void rnd_initLine(rndline_t *_line) {  // initialize line object
  _line->start = random16(NUM_LEDS-1);
  _line->length = random8(M_WIDTH/3);
  if(_line->start+_line->length >= NUM_LEDS) {
    _line->length = NUM_LEDS-_line->start-1;
  }
  _line->hue = random8();
  _line->anim_idx = 0;
  _line->anim_speed = 1+random8(4);
}

void rnd_stepLine(rndline_t *_line) {  // advance animation one step
  _line->anim_idx = qadd8(_line->anim_idx,_line->anim_speed);
  if(_line->anim_idx == 255) {
    rnd_initLine(_line);
  }
}

void effect_random1() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_SLOW;
    cnf.currBright = NORMBRIGHT;
    random_dimspeed = 8;
    currColor = Wheel(random16(768));  // start with random color
    cnf.isModeInit = true;
  }
  dimLeds(random_dimspeed,leds,1);
  if(random8() < 96) {  // the bigger the number (up to 255) the better the chances of placing a pixel
    leds[random16(NUM_LEDS)] = Wheel(random16(768));
  }
}

void effect_random2() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_SLOW;
    cnf.currBright = NORMBRIGHT;
    random_dimspeed = 16;
    cnf.isModeInit = true;
  }
  dimLeds(random_dimspeed,leds,1);
  if(random8() < 160) {  // see comment above
    leds[random16(NUM_LEDS)] = CRGB::White;
  }
}

void effect_random3() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_SLOW;
    cnf.currBright = NORMBRIGHT;
    random_dimspeed = 16;
    currColor = Wheel(random16(768));  // start with random color
    for(uint8_t i=0; i<RANDOM_NUM_LINES; i++) {
      rnd_initLine(&random_rndLines[i]);      
    }
    cnf.isModeInit = true;
  }
  clearLeds(leds, NUM_LEDS);
  for(uint8_t i=0; i<RANDOM_NUM_LINES; i++) {
    rnd_stepLine(&random_rndLines[i]);
    currColor = CHSV(random_rndLines[i].hue,255,255-random_rndLines[i].anim_idx);
    for(uint16_t j=random_rndLines[i].start; j<(random_rndLines[i].start+random_rndLines[i].length); j++) {
      leds[XY(j % M_WIDTH,j / M_WIDTH)] += currColor;
    }
  }
}

void effect_random4() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_SLOW;
    cnf.currBright = NORMBRIGHT;
    random_dimspeed = 16;
    currColor = Wheel(random16(768));  // start with random color
    for(uint8_t i=0; i<RANDOM_NUM_LINES; i++) {
      rnd_initLine(&random_rndLines[i]);      
    }
    cnf.isModeInit = true;
  }
  clearLeds(leds, NUM_LEDS);
  for(uint8_t i=0; i<RANDOM_NUM_LINES; i++) {
    rnd_stepLine(&random_rndLines[i]);
    currColor = CHSV(random_rndLines[i].hue,255,quadwave8(random_rndLines[i].anim_idx));
    for(uint16_t j=random_rndLines[i].start; j<(random_rndLines[i].start+random_rndLines[i].length); j++) {
      leds[XY(j % M_WIDTH,j / M_WIDTH)] += currColor;
    }
  }
}

