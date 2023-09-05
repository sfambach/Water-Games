#pragma once
#ifndef PUMP_H_
#define PUMP_H_

#include "Arduino.h"
#include <stdlib.h>
#include "AbstractPump.h"



#include <AFMotor.h>
#define MAX_SPEED 255

class PumpMotorV1 : public AbstractPump {


private:
  AF_DCMotor &_motor;
  uint8_t _motorNumber;
public:


  PumpMotorV1(uint8_t motorNumber, int16_t minSpeedForward = 50, int16_t minSpeedBackward = -50)
    : _motorNumber(motorNumber), AbstractPump(minSpeedForward, minSpeedBackward) {
    if (motorNumber < 1 || motorNumber > 4) {
      DEBUG_PRINTLN("Motor number must be between 1 and 4!");
      exit(EXIT_FAILURE);
    }
    _motor = AF_DCMotor(motorNumber);
  }

  virtual void setSpeed(int16_t speed) override {
    timerReset();
    _curSpeed = speed;

    if (speed > 0) {
      _motor.run(FORWARD);
      //DEBUG_PRINT("..FORWARD " +String(speed));
      // normalize speed start with the minimum value
      _motor.setSpeed(map(speed, 0, MAX_SPEED, 0 + _minSpeedForward, _maxSpeedForward));
    } else if (speed < 0) {
      //DEBUG_PRINT("..BACKWARD"+String(speed));
      _motor.run(BACKWARD);
      _motor.setSpeed(map(speed, 0, -MAX_SPEED, 0 + _minSpeedBackward * (-1), _maxSpeedBackward) * (-1));
    } else {
      //DEBUG_PRINT("..STOP");
      stop();
    }
  }

  /** stop the pump */
  virtual void stop() override {
    _curSpeed = 0;
    _motor.setSpeed(0);
    //_motor->run(RELEASE);
  }


  /** init method  please call in setup function */
  virtual void init() override {
    _motor.setSpeed(0);
    _motor.run(FORWARD);
    _motor.run(RELEASE);
  }

  /** loop method please call in loop function */
  /*virtual void loop() override{

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
  }*/
};

#endif  // PUMP_H_