/***********************************************
* Test pumps connected to the motor shield v2
* Try a task lib
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
/** PUMPS END ************************************************************************************/

/** TASKS ****************************************************************************************/
#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_TIMEOUT
#include <TaskScheduler.h>
Scheduler ts;

void task1Callback();
void task1OnDisable();
void task2Callback();
void task2OnDisable();
void task0Callback();
void task0OnDisable();
void task3Callback();
void task3OnDisable();

Task t0(1 * TASK_SECOND, TASK_FOREVER, &task0Callback, &ts, false, NULL, &task0OnDisable);
Task t1(5 * TASK_SECOND, TASK_FOREVER, &task1Callback, &ts, false, NULL, &task1OnDisable);
Task t2(5 * TASK_SECOND, TASK_FOREVER, &task2Callback, &ts, false, NULL, &task2OnDisable);
Task t3(5 * TASK_SECOND, TASK_FOREVER, &task3Callback, &ts, false, NULL, &task3OnDisable);


/** Tasks END *************************************************************************************/

  void  setup() {
  Serial.begin(115200);
  DEBUG_PRINTLN("Setup");

  // init the pumps
  pumpsInit();


  t0.setTimeout(10 * TASK_SECOND);
  t1.setTimeout(15 * TASK_SECOND);
  t2.setTimeout(20 * TASK_SECOND);
  t3.setTimeout(25 * TASK_SECOND);


  // init tasks
  ts.enableAll();


}



// run the program
void loop() {

#ifdef DEBUG
  //pumpsTest();
#endif // DEBUG

 ts.execute();

}



void task0Callback() {

  pumpSetSpeed(pumps[0], 255); 
}
void task0OnDisable() {
  pumpSetSpeed(pumps[0], 0); 
  /*if (t1.timedOut()) {
    pumpSetSpeed(pumps[0], 0); 
  }
  else {
   // Serial.println("Task 1 has been disabled");
  }*/
}


void task1Callback() {
  pumpSetSpeed(pumps[1], 255); 
}
void task1OnDisable() {
  pumpSetSpeed(pumps[1], 0); 
}


void task2Callback() {

  pumpSetSpeed(pumps[2], 255); 
}
void task2OnDisable() {
  pumpSetSpeed(pumps[2], 0); 

}


void task3Callback() {

  pumpSetSpeed(pumps[3], 255); 
}
void task3OnDisable() {
  pumpSetSpeed(pumps[3], 0); 
}
