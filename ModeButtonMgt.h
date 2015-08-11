uint8_t autoModeChange;
uint32_t lastAutoModeChangeTime;
uint8_t soundForEveryone;

void ChangeMode(uint8_t _modeUp) {
  // change mode up or down, never go to mode 0 (find me), has its own button
  if(_modeUp == 0) {
    if(--cnf.currMode >= numEffects) cnf.currMode = numEffects-1;
  } else {
    if(++cnf.currMode >= numEffects) cnf.currMode = 0;
  }
  //currFrame = 0;
  cnf.isModeInit = false;
}

void ModeButton_Click() {
  #ifndef ALWAYSAUTO
  if(autoModeChange == 1) {  // exit auto mode change on button press
    autoModeChange = 0;
  }
  #endif
  ChangeMode(1);
}

void ModeButton_DoubleClick() {
  #ifndef ALWAYSAUTO
  if(autoModeChange == 1) {  // exit auto mode change on button press
    autoModeChange = 0;
  }
  #endif
  ChangeMode(0);
}

void ModeButton_Hold() {
  if(autoModeChange) {
    autoModeChange = 0;
    LEDS.showColor(CRGB::Red);
    delay(150);
  } else {
    autoModeChange = 1;
    LEDS.showColor(CRGB::Green);
    delay(150);
  }
}

void CheckAutoModeChange() {
  // auto mode change every AUTOMODE_CHANGE milliseconds, choose random mode
  if(millis() > AUTOMODE_CHANGE && millis() - lastAutoModeChangeTime > AUTOMODE_CHANGE) {
    lastAutoModeChangeTime = millis();
    cnf.currMode = random8(numEffects-1); // random number including 0, excluding MAX_MODE
    cnf.isModeInit = false;
  }
}

