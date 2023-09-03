/***********************************************
* Test the water end switches
* Licence: AGPL3
* Author: S. Fambach
* Website: http://www.fambach.net
************************************************/

#include <stdlib.h>
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// allow debug output
#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif

/** PCF8574.h *****************************************************************/
#include "PCF8574.h"
PCF8574 pcf(0x20);

/** Switches ******************************************************************/
#include "WaterEndSwitch.h"
#include "WaterEndSwitchPCF8574.h"

void callBack1(WaterEndSwitch* sw);

// switch indices

#define VESSEL_1_FULL  0
#define VESSEL_1_EMPTY 1

WaterEndSwitch *sw[] = {
  //new WaterEndSwitch(13, callBack1, false),
  new WaterEndSwitchPCF8574(0, &pcf, callBack1, false),
  new WaterEndSwitchPCF8574(1, &pcf, callBack1, true)
};

#define SWITCH_COUNT 2  // (sizeof(sw) / sizeof(sw[0]))

/** Main Program ************************************************************/

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN(F("Setup"));

  pcf.begin();
  delay(200);

  DEBUG_PRINT(F("Init Switches "));
  for (int i = 0; i < SWITCH_COUNT; i++) {
    sw[i]->init();
  }
  DEBUG_PRINTLN(F("... Success!"));
}

// run the program
void loop() {
  for (int i = 0; i < SWITCH_COUNT; i++) {
    sw[i]->loop();
  }

  delay(100);
}

/** Rest of implementations **************************************************/

void callBack1(WaterEndSwitch* csw) {

  for (int i = 0; i < SWITCH_COUNT; i++) {

    if (sw[i] == csw) {
        DEBUG_PRINTLN("Switch " + String(i) + ": " + String(csw->getCurrentState() ? "ON" : "OFF"));
    } 
  }

  if(sw[VESSEL_1_FULL] == csw){
    DEBUG_PRINT(F("Vessel 1 is"));
    if( csw && csw->getCurrentState()){
      DEBUG_PRINT(F("FULL"));
    } else {
      DEBUG_PRINT(F("NOT FULL"));
    }
//    DEBUG_PRINTLN(F("stop motor 1"));
  } else if(sw[VESSEL_1_EMPTY] == csw){
    DEBUG_PRINT(F("Vessel 1 is"));
    if( csw && csw->getCurrentState()){
      DEBUG_PRINT(F("EMPTY"));
    } else {
      DEBUG_PRINT(F("NOT EMPTY"));
    }
    
  }  
}