// sine interference effect

//mode 1: sine 1 (red)
//mode 2: sine 2 (multi color)
//mode 3: sine 3 (variable color)

uint8_t  sine_dist[M_WIDTH][M_HALFWIDTH];
int8_t   sine_xoffset;
int8_t   sine_yoffset;
uint16_t sine_freq;
uint16_t sine_speed;
uint8_t  sine_color;
uint16_t sine_var;

void sine_init_common() {
  uint8_t mlt256 = 256 / (M_HALFWIDTH + M_HEIGHT);
  for(uint8_t y=0; y<M_HEIGHT; y++) {
    for(uint8_t x=0; x<M_HALFWIDTH; x++) {
      sine_dist[x][y] = sqrt((x+sine_xoffset)*(x+sine_xoffset) +
        (y+sine_yoffset)*(y+sine_yoffset)) * mlt256;
    }
  }
}

void sine_step_common() {
  for(uint8_t y=0; y<M_HEIGHT; y++) {
    for(uint8_t x=0; x<M_HALFWIDTH; x++) {
      leds[XY(M_HALFWIDTH+x,y)] = leds[XY(M_HALFWIDTH-x-1,y)] = 
        ColorMap(quadwave8(((sine_dist[x][y] * sine_freq) - (cnf.currFrame * sine_speed)%256)),sine_color,sine_var);
    }
  }
}

void effect_sine1() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_NORMAL;
    cnf.currBright = NORMBRIGHT;
    sine_xoffset = 1;
    sine_yoffset = -4;
    sine_freq = 5;
    sine_speed = 2;
    sine_color = 1;
    sine_var = 0;
    sine_init_common();
    cnf.isModeInit = true;
  }
  sine_step_common();
}

void effect_sine2() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_NORMAL;
    cnf.currBright = NORMBRIGHT;
    sine_xoffset = 1;
    sine_yoffset = -5;
    sine_freq = 6;
    sine_speed = 2;
    sine_color = 4;
    sine_var = 550;
    sine_init_common();
    cnf.isModeInit = true;
  }
  sine_step_common();
}

void effect_sine3() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_NORMAL;
    cnf.currBright = NORMBRIGHT;
    sine_xoffset = -8;
    sine_yoffset = 6;
    sine_freq = 7;
    sine_speed = 2;
    sine_color = 4;
    sine_var = 0;
    sine_init_common();
    cnf.isModeInit = true;
  }
  sine_var = cnf.currFrame;
  sine_step_common();
}

