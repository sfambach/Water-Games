/** end switch for water 
* can also be used for other switches
* is not debounced
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
#include <Bounce2.h>

typedef void (*SwitchCallback)(bool);

class WaterEndSwitch {
  private:
    bool _currentState = false;  
    bool _inverted = false;
    uint8_t _pin = 0;
    

    bool readState(){ 
      bool state = digitalRead(_pin);
      return (_inverted?!state: state);
    }

  public:
    
    SwitchCallback _callback;
    WaterEndSwitch(uint8_t pin,SwitchCallback callback, bool inverted = false)
    : _pin (pin), _callback(callback), _inverted (inverted)
    {

    }


    void init() {
      // get the current state
      _currentState = readState();   

      // do a callback once
      if(_callback){
        _callback(_currentState);
      }
    }


    void loop (){ 
      bool oldState = _currentState;
      _currentState = readState();   
      if(oldState != getCurrentState() && _callback){
        _callback(_currentState);
      }   
    }

    bool getCurrentState(){ return _currentState;}
    bool getInverted(){return _inverted;}

    void setInverted(bool inv){
      _inverted = inv;
      init();
    }


};

#endif // WaterEndSwitch_h