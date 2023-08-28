/***********************************************
* Test pumps connected to the motor shield v2
*
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

// create/init the shield and pumps
#include <Adafruit_MotorShield.h>
Adafruit_MotorShield motorShield = Adafruit_MotorShield();
#define PUMPS_COUNT_MAX 4
#define PUMPS_SPEED_MAX 255
#define PUMPS_SPEED_MIN (-255)
#define PUMPS_SPEED_MAX_START 50 // Minimum value for the pump to start
#define PUMPS_SPEED_MIN_START -50 // Minimum value for the pump to start

Adafruit_DCMotor *pumps[PUMPS_COUNT_MAX];

/** init the pumps please call in setup functions 
*/
void pumpsInit() {

  DEBUG_PRINT("Init Pumps: ");

  if (!motorShield.begin()) {
    DEBUG_PRINTLN("ERROR: Could not find Motor Shield. Check wiring.  Program will stop here!");
    while (1)
      ;
  }
  DEBUG_PRINTLN("Success!");


  for (int8_t i = 0; i < PUMPS_COUNT_MAX; i++) {
    DEBUG_PRINTLN("Init Pump " + String(i + 1));
    pumps[i] = motorShield.getMotor(i + 1);
    pumps[i]->setSpeed(0);
    pumps[i]->run(FORWARD);
    pumps[i]->run(RELEASE);
  }
}

// set speed for a single pump
void pumpSetSpeed(Adafruit_DCMotor* pump, int speed){
  if (speed > 0){
    pump->run(FORWARD); 
    // normalize speed start with the minimum value  
    pump->setSpeed(map(speed,0,255, 0+PUMPS_SPEED_MAX_START, 255));  
  }else if (speed < 0){
    pump->run(BACKWARD);  
    pump->setSpeed(map(speed,0,-255, 0+PUMPS_SPEED_MIN_START*(-1), 255));  
  }else {
    pump->setSpeed(speed);  
    //pump->run(RELEASE);  
  }
}

#ifdef DEBUG
/** test the pumps only in debug mode */
void pumpsTest()
{
  for(int pumpIdx = 0; pumpIdx < PUMPS_COUNT_MAX; pumpIdx++  ){
  //int pumpIdx = 1;
      DEBUG_PRINT("Test Pump forward " + String(pumpIdx+ 1));
      int speedIndex = 0;
      for(; speedIndex < PUMPS_SPEED_MAX; speedIndex++){
        DEBUG_PRINT(speedIndex%10 == 0 ? "." : "") ;
        pumpSetSpeed(pumps[pumpIdx], speedIndex);   
        delay(100);
      }
      DEBUG_PRINTLN("Full speed forwards");
      delay(2000);
      pumpSetSpeed(pumps[pumpIdx], 0);   
      
   /*   DEBUG_PRINT("Test Pump backward " + String(pumpIdx+ 1));
      speedIndex = 0;
      for(; speedIndex > PUMPS_SPEED_MIN; speedIndex--){
        DEBUG_PRINT(speedIndex%10 == 0 ? "." : "") ;
        pumpSetSpeed(pumps[pumpIdx], speedIndex);   
        delay (100);
      }
      DEBUG_PRINTLN("Full speed backwards");
      delay(2000);
      pumpSetSpeed(pumps[pumpIdx], 0);   */
  }


}
#endif // DEBUG 
  void  setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  // init the pumps
  pumpsInit();
}



// run the program
void loop() {

#ifdef DEBUG
  pumpsTest();
#endif // DEBUG

  // do nothing
  delay(1000);
}
