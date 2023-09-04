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
// #include "Pump.h"
#include "AbstractPump.h"
#include "PumpMotorV2.h"
#include "PumpMotorV1.h"
#include "PumpRelay.h"

// create/init the shield and pumps



// create 4 pumps
/*AbstractPump* pumps[] = { new PumpMotorV2(motorShield.getMotor(1)),
                 new PumpMotorV2(motorShield.getMotor(2)),
                 new PumpMotorV2(motorShield.getMotor(3)),
                 new PumpMotorV2(motorShield.getMotor(4)) };*/


AbstractPump* pumps[] = { new PumpRelay(7),
 new PumpRelay(8),
 new PumpRelay(13),
 new PumpMotorV1(1),
 new PumpMotorV2(1)
};
/** init the pumps please call in setup functions 



/** Organ ****************************************************************************************/
#include "PumpOrgan.h";
PumpOrgan organ(pumps,4);

void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  /*DEBUG_PRINT("Init Pumps: ");
 */

  organ.init();
  DEBUG_PRINTLN("Success!");

  organ.setCurrentProgram(&fauntain2);
}

// run the program
void loop() {
  organ.loop();
}
