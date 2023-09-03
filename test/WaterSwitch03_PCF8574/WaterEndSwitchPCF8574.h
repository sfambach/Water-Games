/** end switch for water 
* can also be used for other switches
* Licence: AGPL3
* Author: S. Fambach
* Website: http://www.fambach.net
*/

#ifndef WaterEndSwitchPCF8574_h
#define WaterEndSwitchPCF8574_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <PCF8574.h>

class WaterEndSwitchPCF8574 : public WaterEndSwitch {
  protected:
    PCF8574* _pcf;

    virtual bool readState(){ 
      //DEBUG_PRINT(".. PCF");
      bool state = _pcf->readButton(_pin);
      return (_inverted? state : !state); // output is inverted 
    }

  public:
    
    SwitchCallback _callback;

    WaterEndSwitchPCF8574(uint8_t pin, PCF8574* pcf,  SwitchCallback callback, bool inverted = false)
    : WaterEndSwitch(pin, callback, inverted), _pcf(pcf) 
    {
      
    }

    virtual void init() override {
      Serial.print("... PCF ");
      // get the current state
      _currentState = this->readState();   

      // do a callback once
      if(_callback){
        _callback(this);
      }
    }

   /* virtual void loop() override {
      WaterEndSwitch::loop();
     
   
    }*/
};

#endif // WaterEndSwitch_h