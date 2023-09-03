/** end switch for water 
* can also be used for other switches
* Licence: AGPL3
* Author: S. Fambach
* Website: http://www.fambach.net
*/

#ifndef WaterEndSwitch_h
#define WaterEndSwitch_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


// #define USE_DEBOUNCE_2
#ifdef USE_DEBOUNCE_2
#include <Bounce2.h>
#endif  // USE_DEBOUNCE_2
typedef void (*SwitchCallback)(void*);

class WaterEndSwitch {
protected:
  bool _currentState = false;
  bool _inverted = false;
  uint8_t _pin = 0;


#ifdef USE_DEBOUNCE_2
  Bounce2::Button _waterSwitch;
#endif  // USE_DEBOUNCE_2

  /** tead the state of the io port */
  virtual bool readState() {
    //DEBUG_PRINT(".. Normal");
    bool state = false;
#ifdef USE_DEBOUNCE_2
    _waterSwitch.update();
    state = _waterSwitch.read();
#else
    state = digitalRead(_pin);
#endif                                    // USE_DEBOUNCE_2
    return (_inverted ? state : !state);  // confusing but this negates the pullup ;)
  }

public:

  SwitchCallback _callback;
  WaterEndSwitch(uint8_t pin, SwitchCallback callback, bool inverted = false)
    : _pin(pin), _callback(callback), _inverted(inverted) {
  }


  virtual void init() {

#ifdef USE_DEBOUNCE_2
    _waterSwitch.attach(_pin, INPUT_PULLUP);
    _waterSwitch.interval(5);

#else 
    pinMode(_pin, INPUT_PULLUP);
#endif  // USE_DEBOUNCE_2

    // get the current state
    _currentState = readState();

    // do a callback once
    if (_callback) {
      _callback(this);
    }
  }


  virtual void loop() {

    bool newState = readState();

    if (newState != getCurrentState() && _callback) {
      _currentState = newState;
      _callback(this);
    }

    //DEBUG_PRINTLN(String(WaterEndSwitch::_currentState ? ".. ON" : ".. OFF"));
  }

  bool getCurrentState() {
    return _currentState;
  }
  bool getInverted() {
    return _inverted;
  }

  void setInverted(bool inv) {
    _inverted = inv;
    init();
  }
};

#endif  // WaterEndSwitch_h