#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#define AUDIO_IN_PIN A2
#define AUDIO_MAX_RESET_COUNTER 500

AudioInputAnalog   audioIn(AUDIO_IN_PIN);
AudioAnalyzeFFT256 fft256;
AudioConnection    patchCable(audioIn, fft256);

void InitFFT() {
  AudioMemory(23);
  fft256.windowFunction(AudioWindowHanning256);
}

void GetFFT(Config_t *_cnf) {
  static int audioResetCounter = AUDIO_MAX_RESET_COUNTER;
  static float maxValue;
  if(fft256.available()) {
    float thisBand[8];

    thisBand[0] = fft256.read( 2,  3);
    thisBand[1] = fft256.read( 4,  6);
    thisBand[2] = fft256.read( 7, 10);
    thisBand[3] = fft256.read(11, 19);
    thisBand[4] = fft256.read(20, 32);
    thisBand[5] = fft256.read(33, 52);
    thisBand[6] = fft256.read(53, 82);
    thisBand[7] = fft256.read(83,127);
      
    if(audioResetCounter == AUDIO_MAX_RESET_COUNTER) {
      maxValue = thisBand[0];
    }
    for(uint8_t i=0;i<8;i++) {
      if(thisBand[i] > maxValue) {
        maxValue = thisBand[i];
      }
    }
    if(maxValue < 1.0) { maxValue = 1.0; }
    float maxFactor = 255.0 / maxValue;
      
    for(uint8_t i=0;i<8;i++) {
      cnf.eq8Band[i] = thisBand[i] * maxFactor;
    }
    
    cnf.eqVol[0] = (cnf.eq8Band[0] + cnf.eq8Band[1] + cnf.eq8Band[2] + cnf.eq8Band[2]) / 4;  // low tones
    cnf.eqVol[1] = (cnf.eq8Band[3] + cnf.eq8Band[4]) / 2;                                        // mid tones
    cnf.eqVol[2] = (cnf.eq8Band[5] + cnf.eq8Band[6] + cnf.eq8Band[7]) / 3;                     // high tones
      
    audioResetCounter--;
    if(audioResetCounter == 0) {
      audioResetCounter = AUDIO_MAX_RESET_COUNTER;
    }
  }
}
