/***********************************************
* Test pumps connected to the motor shield v2
* Tasks 2 do it my way
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
// create/init the shield and pumps
#include <Adafruit_MotorShield.h>
#include "Pump.h"
Adafruit_MotorShield motorShield = Adafruit_MotorShield();
#define PUMPS_COUNT_MAX 4
#define PUMPS_SPEED_MAX 255
#define PUMPS_SPEED_MIN (-255)
#define PUMPS_SPEED_MAX_START 50   // Minimum value for the pump to start
#define PUMPS_SPEED_MIN_START -50  // Minimum value for the pump to start

// create 4 pumps
Pump pumps[] = { Pump(motorShield.getMotor(1)),
                 Pump(motorShield.getMotor(2)),
                 Pump(motorShield.getMotor(3)),
                 Pump(motorShield.getMotor(4)) };

/** init the pumps please call in setup functions 
*/

#ifdef DEBUG
/** test the pumps only in debug mode */
void pumpsDurationTest() {
  for (int pumpIdx = 0; pumpIdx < PUMPS_COUNT_MAX; pumpIdx++) {
    DEBUG_PRINT("Test Pump " + String(pumpIdx + 1));
    pumps[pumpIdx].setSpeed(200, 10000);  // 200 speed for 10 seconds
    delay(3000);
  }
}



void pumpsDelayDurationTest() {
  //for (int pumpIdx = 0; pumpIdx < PUMPS_COUNT_MAX; pumpIdx++) {
    pumps[0].setSpeed(200, 20000 , 0);  // 200 speed for 5 seconds delay 0
    pumps[1].setSpeed(200, 16000, 2000);  // 200 speed for 16 seconds delay 2 sec
    pumps[2].setSpeed(200, 12000, 4000);  // 200 speed for 12 seconds delay 4 sec
    pumps[3].setSpeed(200, 8000, 6000 );  // 200 speed for 8 seconds delay 6 sec
    
    
  //}
}
#endif  // DEBUG
        /** PUMPS END ************************************************************************************/


void setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  DEBUG_PRINT("Init Pumps: ");
  if (!motorShield.begin()) {
    DEBUG_PRINTLN("ERROR: Could not find Motor Shield. Check wiring.  Program will stop here!");
    while (1)
      ;
  }

  // init the pumps
  for (int i = 0; i < PUMPS_COUNT_MAX; i++) {
    pumps[i].init();
  }
  DEBUG_PRINTLN("Success!");

#ifdef DEBUG
  pumpsDelayDurationTest();
#endif  // DEBUG
}



// run the program
void loop() {
  for (int i = 0; i < PUMPS_COUNT_MAX; i++) {
    //DEBUG_PRINT("Pump"+ String(i));
    pumps[i].loop();
  }
}
