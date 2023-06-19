// mode 1: red kr effect
// mode 2: rainbow kr effect
// mode 3: sound reactive kr effect (hue shift)

#define KR_WIDTH 12 // width of KR-band
#define KR_BORDER (KR_WIDTH / 4)
#define KR_DIMSPEED 23
#define KR_BPM 20

void effectKRCommon()
{
  dimLeds(KR_DIMSPEED, &leds[OCTO_OFFSET], 1);

  uint8_t startPos = beatsin8(KR_BPM, 0, M_WIDTH - KR_WIDTH);
  uint8_t top, bottom;
  if (M_HEIGHT > 4)
  {
    bottom = M_HEIGHT / 4;
    top = M_HEIGHT - (M_HEIGHT / 4);
  }
  else
  {
    bottom = 0;
    top = M_HEIGHT;
  }
  for (uint8_t i = bottom; i < top; i++)
  {
    for (uint8_t j = startPos; j < startPos + KR_WIDTH; j++)
    {
      leds[XY(j, i)] += currColor;
      // fade out edges of square. -- idea: fade out in a circle or oval to get more of a HAL-9000 look...
      if ((j < startPos + KR_BORDER) || (j > (startPos + KR_WIDTH - 1 - KR_BORDER)))
      {
        leds[XY(j, i)].fadeToBlackBy(64);
      }
      if (i == bottom || i == (top - 1))
      {
        leds[XY(j, i)].fadeToBlackBy(128);
        if (j == startPos || j == (startPos + KR_WIDTH - 1))
        {
          leds[XY(j, i)].fadeToBlackBy(128);
        }
      }
    }
  }
}

void eff_redKR()
{
  if (!cnf.isModeInit)
  {
    cnf.currDelay = DELAY_KR;
    cnf.currBright = NORMBRIGHT;
    currColor = CRGB(192, 6, 0); // red
    cnf.canShowText = 0;
    cnf.isModeInit = true;
  }
  effectKRCommon();
}

void eff_rainbowKR()
{
  if (!cnf.isModeInit)
  {
    cnf.currDelay = DELAY_KR;
    cnf.currBright = NORMBRIGHT;
    cnf.canShowText = 0;
    cnf.isModeInit = true;
  }
  currColor = CHSV(cnf.currHue, 255, 255);
  effectKRCommon();
}

void eff_soundKR()
{
  if (!cnf.isModeInit)
  {
    cnf.currDelay = DELAY_KR;
    cnf.currBright = NORMBRIGHT;
    cnf.canShowText = 0;
    cnf.isModeInit = true;
  }
  currColor = Wheel(520 + cnf.eqVol[1]);
  currColor.fadeToBlackBy(128 - (cnf.eqVol[1] / 2));
  effectKRCommon();
}
