// noise effect (from FastLED example NoisePlusPalette)

static uint16_t n_x;
static uint16_t n_y;
static uint16_t n_z;
uint16_t n_speed = 20;
uint16_t n_scale = 30;
uint8_t noise[MAXDIM][MAXDIM];
uint8_t n_colorLoop = 1;

// Fill the x/y array of 8-bit noise values using the inoise8 function.
void fillnoise8() {
  // If we're runing at a low "speed", some 8-bit artifacts become visible
  // from frame-to-frame.  In order to reduce this, we can do some fast data-smoothing.
  // The amount of data smoothing we're doing depends on "speed".
  uint8_t dataSmoothing = 0;
  if( n_speed < 50) {
    dataSmoothing = 200 - (n_speed * 4);
  }
  
  for(int i = 0; i < MAXDIM; i++) {
    int ioffset = n_scale * i;
    for(int j = 0; j < MAXDIM; j++) {
      int joffset = n_scale * j;
      
      uint8_t data = inoise8(n_x + ioffset,n_y + joffset,n_z);

      // The range of the inoise8 function is roughly 16-238.
      // These two operations expand those values out to roughly 0..255
      // You can comment them out if you want the raw noise data.
      data = qsub8(data,16);
      data = qadd8(data,scale8(data,39));

      if( dataSmoothing ) {
        uint8_t olddata = noise[i][j];
        uint8_t newdata = scale8( olddata, dataSmoothing) + scale8( data, 256 - dataSmoothing);
        data = newdata;
      }
      
      noise[i][j] = data;
    }
  }
  
  n_z += n_speed;
  
  // apply slow drift to X and Y, just for visual variation.
  n_x += n_speed / 8;
  n_y -= n_speed / 16;
}

void mapNoiseToLEDsUsingPalette()
{
  static uint8_t ihue=0;
  
  for(int i = 0; i < M_WIDTH; i++) {
    for(int j = 0; j < M_HEIGHT; j++) {
      // We use the value at the (i,j) coordinate in the noise
      // array for our brightness, and the flipped value from (j,i)
      // for our pixel's index into the color palette.

      uint8_t index = noise[j][i];
      uint8_t bri =   noise[i][j];

      // if this palette is a 'loop', add a slowly-changing base value
      if( n_colorLoop) { 
        index += ihue;
      }

      // brighten up, as the color palette itself often contains the 
      // light/dark dynamic range desired
      if( bri > 127 ) {
        bri = 255;
      } else {
        bri = dim8_raw( bri * 2);
      }

      CRGB color = ColorFromPalette( currPalette, index, bri);
      leds[XY(i,j)] = color;
    }
  }
  
  ihue+=1;
}



void effectNoiseCommon() {
  fillnoise8();
  mapNoiseToLEDsUsingPalette();
}

void eff_noiseParty() {
  if(!cnf.isModeInit) {
    currPalette = PartyColors_p;
    n_colorLoop = 1;
    n_speed = 15;
    n_scale = 30;
    n_x = random16();
    n_y = random16();
    n_z = random16();
    cnf.currDelay = DELAY_SLOW;
    cnf.currBright = LOWBRIGHT;
    cnf.canShowText = 1;
    cnf.isModeInit = true;
  }
  effectNoiseCommon();
}

void eff_noiseOcean() {
  if(!cnf.isModeInit) {
    currPalette = OceanColors_p;
    n_colorLoop = 0;
    n_speed = 20;
    n_scale = 90;
    n_x = random16();
    n_y = random16();
    n_z = random16();
    cnf.currDelay = DELAY_SLOW;
    cnf.currBright = NORMBRIGHT;
    cnf.canShowText = 1;
    cnf.isModeInit = true;
  }
  effectNoiseCommon();
}

void eff_noiseGreen() {
  if(!cnf.isModeInit) {
    fill_solid( currPalette, 16, CRGB::Black);
    currPalette[0] = CRGB::Green;
    currPalette[4] = CRGB::Green;
    currPalette[8] = CRGB::Green;
    currPalette[12] = CRGB::Green;
    n_colorLoop = 1;
    n_speed = 10;
    n_scale = 40;
    n_x = random16();
    n_y = random16();
    n_z = random16();
    cnf.currDelay = DELAY_SLOW;
    cnf.currBright = NORMBRIGHT;
    cnf.canShowText = 1;
    cnf.isModeInit = true;
  }
  effectNoiseCommon();
}

void eff_noiseOASG() {
  if(!cnf.isModeInit) {
    fill_solid( currPalette, 16, CRGB::Black);
    currPalette[0] = CRGB(102,102,224); // blau
    currPalette[4] = CRGB(255,102,102); // rot
    currPalette[8] = CRGB(102,102,224); // blau
    currPalette[12] = CRGB(255,102,102); // rot
    n_colorLoop = 1;
    n_speed = 10;
    n_scale = 20;
    n_x = random16();
    n_y = random16();
    n_z = random16();
    cnf.currDelay = DELAY_SLOW;
    cnf.currBright = NORMBRIGHT;
    cnf.canShowText = 1;
    cnf.isModeInit = true;
  }

  effectNoiseCommon();
}
