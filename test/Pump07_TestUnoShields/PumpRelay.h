#ifndef PUMP_RELAY_H_
#define PUMP_RELAY_H_

#include "Arduino.h"
#include <stdlib.h>
#include "AbstractPump.h"

class PumpRelay : public AbstractPump{


private:
 uint8_t _pin;


public:


  PumpRelay(uint8_t pin, int16_t minSpeedForward = 1, int16_t minSpeedBackward = -1)
    : _pin(pin), AbstractPump(minSpeedForward,minSpeedBackward) {
 
  }

  virtual void setSpeed(int16_t speed) override {
    timerReset();

    if(isBlocked()){
      return;
    }

    _curSpeed = speed;

    if (speed != 0) {
      digitalWrite(_pin, HIGH);
    } else {
      //DEBUG_PRINT("..STOP");
      stop();
    }
  }
  
  /** stop the pump */
  virtual void stop() override {
    _curSpeed = 0;
     digitalWrite(_pin, LOW);
  }

  
  /** init method  please call in setup function */
  virtual void init() override {
    pinMode(_pin, OUTPUT);
  }

   
};

#endif  // PUMP_RELAY_H_