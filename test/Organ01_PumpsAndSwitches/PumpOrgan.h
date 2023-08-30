#include <stdlib.h>
#include "Arduino.h"
#ifndef PUMP_ORGAM_H
#define PUMP_ORGAM_H

#define USE_PROGEMEM
#define INCLUDE_DEFAULT_PLAYLISTS


#ifdef INCLUDE_DEFAULT_PLAYLISTS
#include "PumpOrganDefaultPlaylists.h"
#endif
#include "Pump.h"


class PumpOrgan {

private:
  uint16_t _currentStep = 0;
  OrganProgram* _currentProgram;

  Pump* _pumps;
  uint8_t _pumpCount;
  long _stepDuration = 1000;  // default one sec
  long _stepStartTS = 0;

public:

  /** default constructor 
  */
  PumpOrgan(Pump* pumps, uint8_t pumpCount) {
    _pumps = pumps;
    _pumpCount = pumpCount;
    DEBUG_PRINTLN("setup size of pumps " + String(_pumpCount));
  }

  /** define how long a step should be played, 
  * if the duration is 4000 = 4 sec then each step will take 4 secs.
  */
  void setStepDuration(long duration) {
    _stepDuration = duration;
  }

  /** set a new programm */
  void setCurrentProgram(OrganProgram* program) {
    _currentProgram = program;
  }

  /** reset the current program 
  * restart again if a program is set
  */
  void reset() {
    _currentStep = 0;
    _stepStartTS = millis();
    playStep(_currentStep);
  }

  /** play a step */
  void playStep(uint16_t step) {
    if (_currentProgram) {

      if (step < 0 || step >= _currentProgram->_stepCount) {
        DEBUG_PRINTLN("Wrong step counter" + String(_currentProgram->_stepCount));
        _currentStep = step = 0;
      }

      DEBUG_PRINT("Step" + String(step) + " :  [");

      for (int pumpIdx = 0; pumpIdx < _pumpCount; pumpIdx++) {
        int16_t currentPumpSpeed;
        
        // do nothing while the pump is blocked 
        if(_pumps[pumpIdx].isBlocked()){
          continue;
        }

#ifdef USE_PROGEMEM
        currentPumpSpeed = pgm_read_word_near(_currentProgram->_content + (step * _pumpCount) + pumpIdx);
#else
        currentPumpSpeed = _currentProgram->_content[f3 + (step * _pumpCount) + pumpIdx];
#endif
        


        _pumps[pumpIdx].setSpeed(currentPumpSpeed);


        DEBUG_PRINT(String(currentPumpSpeed) + ",");
      }
      DEBUG_PRINTLN("]");
    }
  }

  /** call in loop to make the steps run
  */
  void loop() {
    // determin step

    long duration = millis() - _stepStartTS;
    if (duration > _stepDuration) {
      _currentStep++;
      _stepStartTS = millis();
      playStep(_currentStep);
    }
  }

  /** call during setup to init the pumps */
  void init() {
    // init the pumps
    for (int i = 0; i < sizeof(_pumpCount); i++) {
      _pumps[i].init();
    }
  }
};
#endif  // PUMP_ORGAM_H