#include "Arduino.h"
#include <stdlib.h>
#include "WaterEndSwitch.h"
#pragma once
#ifndef PUMP_H_
#define PUMP_H_

#include <Adafruit_MotorShield.h>
#define MAX_SPEED 255
#define DEBUG
#define NO_DELAY (-1)
class Pump {

private:
  long _startTS = 0;
  long _duration = 0;
  long _delay = NO_DELAY;
  long _delayDuration = 0;
  int16_t _delaySpeed = 0;
  bool _vesselFull = false;
  bool _vesselEmpty = false;
  bool _blocked = false;

public:
  Adafruit_DCMotor* _motor;

  int16_t _minSpeedForward = 50;
  int16_t _minSpeedBackward = -50;
  int16_t _maxSpeedForward = MAX_SPEED;
  int16_t _maxSpeedBackward = -MAX_SPEED;

  int16_t _curSpeed = 0;

  Pump(Adafruit_DCMotor* motor, int16_t minSpeedForward = 50, int16_t minSpeedBackward = -50)
    : _motor(motor), _minSpeedForward(minSpeedForward), _minSpeedBackward(minSpeedBackward) {
    if (!motor) {
      DEBUG_PRINTLN("Motor must be set!");
      exit(EXIT_FAILURE);
    }
  }

  void setSpeed(int16_t speed) {
    timerReset();
    _curSpeed = speed;

    if (speed > 0) {
      _motor->run(FORWARD);
      //DEBUG_PRINT("..FORWARD " +String(speed));
      // normalize speed start with the minimum value
      _motor->setSpeed(map(speed, 0, MAX_SPEED, 0 + _minSpeedForward, _maxSpeedForward));
    } else if (speed < 0) {
      //DEBUG_PRINT("..BACKWARD"+String(speed));
      _motor->run(BACKWARD);
      _motor->setSpeed(map(speed, 0, -MAX_SPEED, 0 + _minSpeedBackward * (-1), _maxSpeedBackward) * (-1));
    } else {
      //DEBUG_PRINT("..STOP");
      stop();
    }
  }

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
  void stop() {
    _curSpeed = 0;
    _motor->setSpeed(0);
    //_motor->run(RELEASE);
  }

  void timerReset() {
    _duration = 0;
    _delaySpeed = 0;
    _delayDuration = 0;
    _delay = 0;
  }

  /** init method  please call in setup function */
  void init() {
    _motor->setSpeed(0);
    _motor->run(FORWARD);
    _motor->run(RELEASE);
  }

  /** loop method please call in loop function */
  void loop() {

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

#ifdef DEBUG

  void simpleTest() {
    DEBUG_PRINT("..Start");
    for (int speedIndex = 0; speedIndex < MAX_SPEED; speedIndex++) {
      DEBUG_PRINT(speedIndex % 10 == 0 ? "." : "");
      setSpeed(speedIndex);
      delay(100);
    }
    DEBUG_PRINT("..Full speed forwards");
    delay(2000);
    stop();
    DEBUG_PRINTLN("..full stop");
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


#endif  // DEBUG
};

#endif  // PUMP_H_