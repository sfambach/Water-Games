/***********************************************
* Test pumps with a water organ and water end switches
* Licence: AGPL3
* Author: S. Fambach
* Website: http://Fambach.net
************************************************/
// allow debug output
#define DEBUG
#ifdef DEBUG
#define DEBUG_PRINTLN(x) Serial.println(x)
#define DEBUG_PRINT(x) Serial.print(x)
#else
#define DEBUG_PRINTLN(x)
#define DEBUG_PRINT(x)
#endif

/** PUMPS ****************************************************************************************/
#include "Pump.h"
// create/init the shield and pumps
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield motorShield = Adafruit_MotorShield();

// create 4 pumps
Pump pumps[] = { Pump(motorShield.getMotor(1)),
                 Pump(motorShield.getMotor(2)),
                 Pump(motorShield.getMotor(3)),
                 Pump(motorShield.getMotor(4)) };

/** init the pumps please call in setup functions 



/** Organ ****************************************************************************************/
#include "PumpOrgan.h";
PumpOrgan organ(pumps,4);

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  DEBUG_PRINT("Init Pumps: ");
  if (!motorShield.begin()) {
    DEBUG_PRINTLN("ERROR: Could not find Motor Shield. Check wiring.  Program will stop here!");
    while (1)
      ;
  }

  organ.init();
  DEBUG_PRINTLN("Success!");

  organ.setCurrentProgram(&fauntain2);
}

// run the program
void loop() {
  organ.loop();
}
