#ifndef TEENSYFFT_H
#define TEENSYFFT_H

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <FastLED.h>
#include "zGlobals.h"
#include "LEDColorMgt.h"

#define AUDIO_IN_PIN A2

AudioInputAnalog   audioIn(AUDIO_IN_PIN);
AudioAnalyzeFFT256 fft256;
AudioConnection    patchCable(audioIn, fft256);

class TeensyFFTMgt {
  //private:
  //static LEDColorMgt cmgt;
  public:
  static void InitFFT() {
    AudioMemory(6);
    fft256.windowFunction(AudioWindowHanning256);
  }

  static void GetFFT(Config_t *_cnf) {
    if(fft256.available()) {
      // 8 bands
      _cnf->eq8Band[0] = fft256.read( 2,  3) * 256.0;
      _cnf->eq8Band[1] = fft256.read( 4,  6) * 256.0;
      _cnf->eq8Band[2] = fft256.read( 7, 10) * 256.0;
      _cnf->eq8Band[3] = fft256.read(11, 19) * 256.0;
      _cnf->eq8Band[4] = fft256.read(20, 32) * 256.0;
      _cnf->eq8Band[5] = fft256.read(33, 52) * 256.0;
      _cnf->eq8Band[6] = fft256.read(53, 82) * 256.0;
      _cnf->eq8Band[7] = fft256.read(83,127) * 256.0;
    
      _cnf->eqVol[0] = (_cnf->eq8Band[0] + _cnf->eq8Band[1] + _cnf->eq8Band[2] + _cnf->eq8Band[2]) / 4;  // low tones
      _cnf->eqVol[1] = (_cnf->eq8Band[3] + _cnf->eq8Band[4]) / 2;                                        // mid tones
      _cnf->eqVol[2] = (_cnf->eq8Band[5] + _cnf->eq8Band[6] + _cnf->eq8Band[7]) / 3;                     // high tones
    }
  }
};
#endif

