// Particle system effects
// mode 1: starfield
// mode 2: side emitter (bottom)
// mode 3: side emitter (top)

#include <ParticleSys.h>

const byte numParticles = 140;
ParticleSysConfig g(M_WIDTH, M_HEIGHT, 32, 92);
Particle_Std particles[numParticles];
Particle_Fixed particle_source(g.center_x, g.center_y);
Emitter_Fountain particle_emitterFountn(5,&particle_source);
Emitter_Side particle_emitterSide('b',1,8);
ParticleSys pSys(&g, numParticles, particles, &particle_emitterFountn);
FastLEDRenderer pRenderer(&g, 0, 0, M_WIDTH, M_HEIGHT);

void eff_starfield() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_SLOW;
    cnf.currBright = NORMBRIGHT;
	pSys.emitter = &particle_emitterFountn;
    cnf.isModeInit = true;
  }
  pSys.update();
  pRenderer.fade(leds);
  pRenderer.render(&g, particles, numParticles, leds);
}

void eff_rainingUp() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_SLOW;
    cnf.currBright = NORMBRIGHT;
    particle_emitterSide.side = 'b';
	pSys.emitter = &particle_emitterSide;
    cnf.isModeInit = true;
  }
  particle_emitterSide.baseHue = cnf.currHue;
  pSys.update();
  pRenderer.fade(leds);
  pRenderer.render(&g, particles, numParticles, leds);
}

void eff_rainingDown() {
  if(!cnf.isModeInit) {
    cnf.currDelay = DELAY_SLOW;
    cnf.currBright = NORMBRIGHT;
    particle_emitterSide.side = 't';
	pSys.emitter = &particle_emitterSide;
    cnf.isModeInit = true;
  }
  particle_emitterSide.baseHue = cnf.currHue;
  pSys.update();
  pRenderer.fade(leds);
  pRenderer.render(&g, particles, numParticles, leds);
}


