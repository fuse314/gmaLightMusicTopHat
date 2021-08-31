// fire effect by Mark Kriegsman
// copied from http://pastebin.com/wmy3gt1P


//mode 1: fire 1
//mode 2: fire 2
//mode 3: sound fire

uint8_t fire_heat[M_HALFWIDTH][M_HEIGHT];
// _cooling defines how fast the fire "cools" off (higher value=shorter flames)
uint8_t fire_cooling;
// _sparking defines how often a spark is created at the bottom of the flame
uint8_t fire_sparking;

void effectFireCommon() {
  for (uint8_t row = 0; row < M_HEIGHT; row++) {
    // Step 1.  Cool down every cell a little
    for(uint8_t i = 0; i < M_HALFWIDTH; i++) {
      fire_heat[i][row] = qsub8( fire_heat[i][row],  random8(0, ((fire_cooling * 10) / M_HALFWIDTH) + 2));
    }
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for(uint8_t k= M_HALFWIDTH - 1; k > 1; k--) {
      fire_heat[k][row] = (fire_heat[k-1][row] + fire_heat[k-2][row] + fire_heat[k-2][row] ) / 3;
    }
    // step 2.5 Heat from each cell drifts 'left' and diffuses a little
    if(row < (M_HEIGHT-1)) {
      for(uint8_t m=M_HALFWIDTH-1; m > 0; m--) {
        fire_heat[m][row+1] = (fire_heat[m][row+1] + fire_heat[m][row+1] + fire_heat[m][row+1] + fire_heat[m][row] ) / 4;
      }
    }
    // Step 3.  Randomly ignite new 'sparks' of heat near the bottom
    if(random8() < fire_sparking ) {
      uint8_t y = random8(7);
      fire_heat[y][row] = qadd8( fire_heat[y][row], random8(150,255) );
    }
    // Step 4.  Map from heat cells to LED colors
    uint8_t palIndex;
    for(uint8_t j = 0; j < M_HALFWIDTH; j++) {
      palIndex = scale8(fire_heat[j][row], 240); // scale for better results with palette colors
      leds[XY(M_HALFWIDTH+j,row)] = leds[XY(M_HALFWIDTH-j-1,row)] = ColorFromPalette(currPalette, palIndex);
    }
  }
}

void eff_fire1() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_FIRE;
    cnf.currBright = NORMBRIGHT;
    fire_cooling = 45;
    fire_sparking = 120;
    currPalette = HeatColors_p;
    cnf.canShowText = 1;
    cnf.isModeInit = true;
  }
  effectFireCommon();
}

void eff_fire2() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_FIRE;
    cnf.currBright = NORMBRIGHT;
    fire_cooling = 70;
    fire_sparking = 170;
    cnf.canShowText = 1;
    cnf.isModeInit = true;
  }
  CRGB _darkcolor  = CHSV(cnf.currHue,255,192); // pure hue, three-quarters brightness
  CRGB _lightcolor = CHSV(cnf.currHue,128,255); // half 'whitened', full brightness
  currPalette = CRGBPalette16( CRGB::Black, _darkcolor, _lightcolor, CRGB::White);
  effectFireCommon();
}

void eff_soundFire() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_FIRE;
    cnf.currBright = NORMBRIGHT;
    currPalette = HeatColors_p;
    cnf.canShowText = 1;
    cnf.isModeInit = true;
  }
  fire_cooling = map(cnf.eqVol[1],0,255, 40,90);
  fire_sparking = map(cnf.eqVol[1],0,255, 32,100);
  effectFireCommon();
}

