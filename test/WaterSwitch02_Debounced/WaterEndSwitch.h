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
#include <Bounce2.h>

typedef void (*SwitchCallback)(bool);

class WaterEndSwitch {
  private:
    bool _currentState = false;  
    bool _inverted = false;
    uint8_t _pin = 0;
    Bounce2::Button _waterSwitch;

    bool readState(){ 
      _waterSwitch.update();
      bool state = _waterSwitch.read();
      return (_inverted? state : !state); // confusing but this negates the pullup ;) 
    }

  public:
    
    SwitchCallback _callback;
    WaterEndSwitch(uint8_t pin,SwitchCallback callback, bool inverted = false)
    : _pin (pin), _callback(callback), _inverted (inverted)
    {
      //_waterSwitch = Bounce2::Button();

    }


    void init() {

      _waterSwitch.attach(_pin, INPUT_PULLUP);
      _waterSwitch.interval(5);
      
      // get the current state
      _currentState = readState();   

      // do a callback once
      if(_callback){
        _callback(_currentState);
      }
    }


    void loop (){ 
      
      bool newState = readState();
      
      if(newState != getCurrentState() && _callback){
          _currentState =  newState;
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