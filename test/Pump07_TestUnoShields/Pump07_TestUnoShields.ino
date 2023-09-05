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

// select your uno shield 
#define MOTOR_SHIELD_V1
//#define MOTOR_SHIELD_V2
//#define RELAIS_SHIELD
 
#ifdef MOTOR_SHIELD_V1
#include "PumpMotorV1.h"
AbstractPump* pumps[] = {  
 new PumpMotorV1(1),
 new PumpMotorV1(2),
 new PumpMotorV1(3),
 new PumpMotorV1(4),
};

#endif // MOTOR_SHIELD_V1

#ifdef MOTOR_SHIELD_V2
#include "PumpMotorV2.h"
AbstractPump* pumps[] = {  
 new PumpMotorV2(1),
 new PumpMotorV2(2),
 new PumpMotorV2(3),
 new PumpMotorV2(4),
};
#endif // MOTOR_SHIELD_V2

#ifdef RELAIS_SHIELD
#include "PumpRelay.h"
AbstractPump* pumps[] = {  
 new PumpRelay(7),
 new PumpRelay(6),
 new PumpRelay(5),
 new PumpRelay(4),
};

#endif // RELAIS_SHIELD

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
