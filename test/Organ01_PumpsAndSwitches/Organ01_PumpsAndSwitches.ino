/***********************************************
* Test pumps with a water organ
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

#define MAX_PUMP_COUNT 4
// create 4 pumps
Pump pumps[] = { Pump(motorShield.getMotor(1)),
                 Pump(motorShield.getMotor(2)),
                 Pump(motorShield.getMotor(3)),
                 Pump(motorShield.getMotor(4)) };

/** init the pumps please call in setup functions 
*/
/** organ ****************************************************************************************/
#include "PumpOrgan.h";
PumpOrgan organ(pumps,MAX_PUMP_COUNT);

/** switches *************************************************************************************/
#include "WaterEndSwitch.h"
#define MAX_SWITCH_COUNT 1

WaterEndSwitch switches[] = { WaterEndSwitch( 13, listener1, false) };

/** Main program *********************************************************************************/
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

  // test switches
  for(int i = 0; i < MAX_SWITCH_COUNT; i++){
    switches[i].init();
  }



}

// run the program
void loop() {
  organ.loop();

  for(int i = 0; i < MAX_SWITCH_COUNT; i++){
    switches[i].loop();
  }

}
