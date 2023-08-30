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

/** End switch ***********************************************************************************/
#include "WaterEndSwitch.h"

void callBack1(bool b);

WaterEndSwitch sw1(13,callBack1, false);

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  DEBUG_PRINT("Init Switches ");
  sw1.init();
  
  DEBUG_PRINTLN("Success!");
 
}

// run the program
void loop() {
  sw1.loop();
}


void callBack1(bool b){
  DEBUG_PRINTLN ("Switch 1 " + String(b?"ON": "OFF"));
}