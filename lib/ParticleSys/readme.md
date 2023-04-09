About
-----
A particle system library for arduino for arbitrary matrix sizes
Based on code by Gilad Dayagi ( https://github.com/giladaya/arduino-particle-sys )
Mainly intended to be used with low-resolution displays (like an 8x8 RGB matrix).  

Installation
------------
Clone the repo into the arduino libraries directory

Dependencies
------------
The FastLEDRenderer.cpp and .h depend on the FastLED library ( http://fastled.io )

RAM Usage
---------
This version of the Particle System can be used for an arbitrary size of matrix (up to 256x256 Pixels)
The particle coordinates and other values use 16-bit integers to hold the relevant values.
If you have a LED Matrix of 8x8 Pixels or smaller on hardware with limited RAM (i.E. atmega328 with 2kb of RAM), I recommend to use the original Particle System: https://github.com/giladaya/arduino-particle-sys


Hardware
--------
Any Arduino compatible hardware, but due to RAM usage I recommend something beefy, like a teensy ( http://pjrc.com/teensy/ )

Examples
--------
The following examples are included in the library:

- FlameFastLED: https://youtu.be/pmHItuRvXjg
- GreenFireFastLED: https://youtu.be/ukAbi08XwAk
- MultiFlameFastLED: https://youtu.be/iJiRIr-yuUg
- PainterFastLED: https://youtu.be/3tO_BpcsZSA
- SmokerFastLED: https://youtu.be/Hw3fQnBcnMI
- SpinFastLED: https://youtu.be/XBxegSs1yZs

Notes
-----
If you are working with a narrow LED Matrix (for example 8 x 32 pixels), the Particle_Attractor tends to suck the source right in his center.
This can be corrected using one of several ways:

1. use a higher res_y in the ParticleSysConfig class (in the above example use res_x = 32 (default) and res_y = 128 (4 x default)). The particle system then is calculated as a square, but painted in a squished form.
2. lower the attractor force of the Particle_Attractor (atf - property, the default value is 4)
3. change the attractor force constantly in the loop, for example: ( source.atf = map(beatsin8(50),0,255,-2,3); // this varies the attractor force between -2 (pushing away) and 3 (attracting) 50 times per minute - see FastLED library for the use of the beatsin8 function...)

I used the first approach in the right side of this video: https://youtu.be/osnOcP0NfYc
