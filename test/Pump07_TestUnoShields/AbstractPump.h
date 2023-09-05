#ifndef ABSTRACT_PUMP_H
#define ABSTRACT_PUMP_H


#include "Arduino.h"
#include <stdlib.h>

#define DEBUG
#define NO_DELAY (-1)

class AbstractPump {

protected:
  long _startTS = 0;
  long _duration = 0;
  long _delay = NO_DELAY;
  long _delayDuration = 0;
  int16_t _delaySpeed = 0;
  bool _vesselFull = false;
  bool _vesselEmpty = false;
  bool _blocked = false;
  int16_t _minSpeedForward = 50;
  int16_t _minSpeedBackward = -50;
  uint8_t _maxSpeedGeneral = 255;
  int16_t _maxSpeedForward = _maxSpeedGeneral;
  int16_t _maxSpeedBackward = -_maxSpeedGeneral;
  int16_t _curSpeed = 0;
 

public:
  

  AbstractPump( int16_t minSpeedForward = 50, int16_t minSpeedBackward = -50)
    : _minSpeedForward(minSpeedForward), _minSpeedBackward(minSpeedBackward) {
    
  }

  virtual void setSpeed(int16_t speed) = 0;

  /** run the pump for a while in ms */
  void setSpeed(int16_t speed, long duration) {

    setSpeed(speed);
    _duration = duration;
    _startTS = millis();
    _delay = NO_DELAY;
  }

  /** run the pump after a while for a while */
  void setSpeed(int16_t speed, long duration, long delay) {

    // no delay set
    if (delay < 1) {
      setSpeed(speed, duration);

    } else {
      timerReset();
      _delay = delay;
      _delayDuration = duration;
      _delaySpeed = speed;
      _startTS = millis();
    }
  }
  /** stop the pump */
  virtual void stop() {
    _curSpeed = 0;
  }

  void timerReset() {
    _duration = 0;
    _delaySpeed = 0;
    _delayDuration = 0;
    _delay = 0;
  }

  /** init method  please call in setup function */
  virtual void init() {
  }

  /** loop method please call in loop function */
  virtual void loop() {

    // do nothing if the pump is blocked
    if (isBlocked()) {
      stop();
      return;
    }

    if (_delay > 0) {
      DEBUG_PRINTLN("delayed");
      long ellapsed = millis() - _startTS;

      if (ellapsed > _delay) {
        setSpeed(_delaySpeed, _delayDuration);
      }

    } else if (_duration > 0) {
      //DEBUG_PRINTLN ("!delayed");
      // check the time stamp if the duration is finished stop the pump
      long ellapsed = millis() - _startTS;
      // DEBUG_PRINTLN (ellapsed);

      if (ellapsed > _duration) {
        stop();
      }
    }
  }


  boolean isRunning() {
    return _curSpeed != 0;
  }


  /** DEFAULT callback function for vessek full option */
  void defaultCallbackFull( bool b) {
    _vesselFull = b;
    if(_vesselEmpty || _vesselFull){
      setBlocked(true);
    } else {
      setBlocked(false);
    }
    
  }
  
  void defaultCallbackEmpty(bool b) {
    _vesselEmpty = b;
    if(_vesselEmpty || _vesselFull){
      setBlocked(true);
    } else {
      setBlocked(false);
    }
  }

  void setBlocked(bool b) {
    _blocked = b;
  }

  bool isBlocked() {
    return _blocked;
  }

#ifdef DEBUG

  void simpleTest() {
    DEBUG_PRINT("..Start");
    for (int speedIndex = 0; speedIndex < _maxSpeedGeneral; speedIndex++) {
      DEBUG_PRINT(speedIndex % 10 == 0 ? "." : "");
      setSpeed(speedIndex);
      delay(100);
    }
    DEBUG_PRINT("..Full speed forwards");
    delay(2000);
    stop();
    DEBUG_PRINTLN("..full stop");
  }

#endif  // DEBUG

};

#endif  // ABSTRACT_PUMP_H_
