//mode 0: red kr effect
//mode 1: rainbow kr effect
//mode 2: sound reactive kr effect (hue shift)

#include "zEffectClass.h"
#include "LEDColorMgt.h"

#define KR_WIDTH 12   // width of KR-band
#define KR_BORDER KR_WIDTH/4
#define KR_DIMSPEED 23
#define KR_BPM 90

class EffectKR : public EffectClass {

  public:
  EffectKR(uint8_t _mode, Config_t *_cnf) : EffectClass(_mode, _cnf) {
    _cnf->currDelay = DELAY_KR;
    _cnf->currBright = NORMBRIGHT;
    switch(_effectMode) {
      case 0:
        _currColor = CRGB(192,6,0); // red
      break;
    }
  }
  
  void step(Config_t *_cnf, CRGB* _leds) {
    dimLeds(KR_DIMSPEED , _leds, 1);
    switch(_effectMode) {
      case 1:
        _currColor = CHSV(_cnf->currHue,255,255);
      break;
      case 2:
        _currColor = Wheel(520 + _cnf->eqVol[1]);
        _currColor.fadeToBlackBy(128-(_cnf->eqVol[1]/2));
      break;
    }
    
    uint8_t startPos = beatsin8(KR_BPM,0,M_WIDTH-KR_WIDTH);
    uint8_t top, bottom;
    if(M_HEIGHT > 4) {
      bottom = M_HEIGHT/4;
      top = M_HEIGHT-(M_HEIGHT/4);
    } else {
      bottom = 0;
      top = M_HEIGHT;
    }
    for(uint8_t i=bottom; i<top; i++) {
      for(uint8_t j=startPos;j<startPos+KR_WIDTH;j++) {
      	_leds[XY(j,i)] += _currColor;
      	// fade out edges of square. -- idea: fade out in a circle or oval to get more of a HAL-9000 look...
        if((j<startPos+KR_BORDER) || (j>(startPos+KR_WIDTH-1-KR_BORDER))) {
          _leds[XY(j,i)].fadeToBlackBy(64);
        }
      	if(i==bottom || i==(top-1)) {
      	  _leds[XY(j,i)].fadeToBlackBy(128);
          if(j==startPos || j==(startPos+KR_WIDTH-1)) {
            _leds[XY(j,i)].fadeToBlackBy(128);
          }
      	}
      }
    }
  }
};

