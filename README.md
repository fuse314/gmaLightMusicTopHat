# LightMusicTopHat
© 2014-2018 by Gottfried Mayer https://gma.name

## Overview
Arduino project with LED Matrix, 8 pixels high and 61 pixels wide, each with a built-in WS2812b controller chip.
Sound input with a ADMP401 microphone connected to the Teensy3.1 for fft frequency analysis using pcr

## Schematic
copied top part of https://hackadaycom.files.wordpress.com/2012/09/discoplanetschematic.png

## Hardware
  8 x 61 LED matrix with WS2812b controller chip built in
 The LED matrix is mounted around a top hat. They are wired in a serpentine pattern:  
 row 2: ==>  76 77 78 . . . 111 112 113   
 row 1: <==  75 74 73 . . .  40  39  38   
 row 0: ==>   0  1  2 . . .  35  36  37   
 scrolling horizontally poses a programming problem in this configuration, because in rows 0 and 2 the index increases, but in row 1 the index decreases.

## Prerequisites
Uses FastLED for controlling the LEDs
https://github.com/FastLED/FastLED
http://fastled.io/


## Credits
Inspiration from
http://www.macetech.com/blog/node/118

Mic/MSGEQ7 schematic and code partially copied and modified from
http://hackaday.com/2012/09/11/disco-planet-a-massive-rgbw-led-array-in-a-6-globe/

Fire Mode copied in parts from Mark Kriegsman
https://plus.google.com/112916219338292742137/posts/BZhXE4cqEN4
