#include <FastLED.h>
#include <FastLED_GFX.h>
#include "fonts/Ubuntu_Regular5pt7b.h"
#include "zGlobals.h"

// Font stuff
GFXcanvas fontcanvas(M_TXTWIDTH, M_HEIGHT);
uint8_t hpos = M_HALFWIDTH - 1;
uint8_t showText = 1;
uint8_t prevText = 0;
#define TEXT_1 "OASG"
#define TEXT_2 "TREFFPUNKT"
#define TEXT_3 "BIER"
#define TEXT_4 "2023"
#define TEXT_5 "ROCK ON"

void initText()
{
  fontcanvas.setFont(&Ubuntu_Regular5pt7b);
  fontcanvas.setTextWrap(false);
  fontcanvas.setTextColor(CRGB(230, 250, 230)); // CHSV(cnf.currHue,255,230));
}

void drawText(uint8_t showText, uint8_t canShowText)
{
  if (canShowText == 0)
  {
    return;
  }

  if (showText > 0 && canShowText == 1)
  {
    if (prevText != showText)
    {
      fontcanvas.fillScreen(CRGB(0, 0, 0));
      fontcanvas.setCursor(1, 7);
      if (showText == 1)
      {
        fontcanvas.print(TEXT_1);
      }
      if (showText == 2)
      {
        fontcanvas.print(TEXT_2);
      }
      if (showText == 3)
      {
        fontcanvas.print(TEXT_3);
      }
      if (showText == 4)
      {
        fontcanvas.print(TEXT_4);
      }
      if (showText == 5)
      {
        fontcanvas.print(TEXT_5);
      }
      prevText = showText;
    }

    uint16_t text_end = abs(min(fontcanvas.getCursorX() + 7, fontcanvas.width()));
    EVERY_N_MILLISECONDS(100)
    {
      hpos += 1;
      if (hpos >= text_end)
      {
        hpos = 0;
      }
    }

    // transfer gfx buffer to LEDs
    CRGB *fontBuffer = fontcanvas.getBuffer();
    for (uint8_t copyy = 0; copyy < M_HEIGHT; copyy++)
    {
      for (int16_t x = 0; x < M_WIDTH; x++)
      {
        int16_t copyx = x - hpos;
        // make sure copyx is within 0 and text_end: wrap around on both sides.
        while (copyx < 0)
        {
          copyx += text_end;
        }
        if (copyx >= text_end)
        {
          copyx %= text_end;
        }
        if (fontBuffer[(copyy * fontcanvas.width()) + copyx]) // make sure pixel is not black
        {
          leds[XY(copyx, copyy)] = fontBuffer[(copyy * fontcanvas.width()) + copyx];
        }
      }
    }
  }

  // hide text or show different text every 40 seconds.
  EVERY_N_SECONDS(40)
  {
    if (showText > 0)
    {
      showText = 0;
    }
    else
    {
      showText = random8(6); // random number 0 - 5
    }
  }
}