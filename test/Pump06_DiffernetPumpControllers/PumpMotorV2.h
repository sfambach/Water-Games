#pragma once
#ifndef PUMP_MOTOR_V2_H_
#define PUMP_MOTOR_V2_H_

#include "Arduino.h"
#include <stdlib.h>
#include "AbstractPump.h"



#include <Adafruit_MotorShield.h>
#define MAX_SPEED 255

class PumpMotorV2 : public AbstractPump{


private:
 Adafruit_DCMotor* _motor;
public:


  PumpMotorV2(Adafruit_DCMotor* motor, int16_t minSpeedForward = 50, int16_t minSpeedBackward = -50)
    : _motor(motor), AbstractPump(minSpeedForward,minSpeedBackward) {
    if (!motor) {
      DEBUG_PRINTLN("Motor must be set!");
      exit(EXIT_FAILURE);
    }
  }

  virtual void setSpeed(int16_t speed) override {
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
  
  /** stop the pump */
  virtual void stop() override {
    _curSpeed = 0;
    _motor->setSpeed(0);
    //_motor->run(RELEASE);
  }

  
  /** init method  please call in setup function */
  virtual void init() override {
    _motor->setSpeed(0);
    _motor->run(FORWARD);
    _motor->run(RELEASE);
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

#endif  // PUMP_MOTOR_V2_H_