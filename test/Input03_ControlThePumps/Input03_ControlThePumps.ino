/***********************************************
* Test serial input handler controls the pumps
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

/** Pumps ********************************************************/
// create/init the shield and pumps
#include <Adafruit_MotorShield.h>
#include "Pump.h"
Adafruit_MotorShield motorShield = Adafruit_MotorShield();
#define PUMPS_COUNT_MAX 4

// create 4 pumps
Pump pumps[] = { Pump(motorShield.getMotor(1)),
                 Pump(motorShield.getMotor(2)),
                 Pump(motorShield.getMotor(3)),
                 Pump(motorShield.getMotor(4)) };


/** Event handling ***********************************************/

#define MAX_RUN 5000  // maximum pump run 5 secs
#include "SerialInputHandler.h"
#include "commands.h"
SerialInputHandler handler;

void runCommand(char argv[MAX_ARGS][16], uint8_t argc) {
  char command = argv[0][0];

  for (int8_t i = 0; i < argc; i++) {
    DEBUG_PRINTLN(argv[i]);
  }

  DEBUG_PRINTLN("argc = " + String(argc));

  switch (command) {

    case ALL_PUMPS_STOP:
      for (int i = 0; i < PUMPS_COUNT_MAX; i++) {
        pumps[i].stop();
      }
      DEBUG_PRINTLN("OK");
      break;
    case SET_PUMP_SPEED:

      if (argc == 3) {
        uint8_t pump = atoi(argv[1]);
        uint8_t speed = atoi(argv[2]);

#ifdef MAX_RUN
        pumps[pump - 1].setSpeed(speed, MAX_RUN);
#else
        pumps[pump - 1].setSpeed(speed);
#endif

        DEBUG_PRINTLN("OK " + String(pump) + " " + String(speed));
      } else {
        DEBUG_PRINT("OK2");
        for (int i = 0; i < PUMPS_COUNT_MAX && (i + 1) < argc; i++) {
          uint8_t speed = atoi(argv[i + 1]);
#ifdef MAX_RUN
          pumps[i].setSpeed(speed, MAX_RUN);
#else
          pumps[i].setSpeed(speed);
#endif
          DEBUG_PRINT(" " + String(speed));
        }
        DEBUG_PRINTLN("");
      }
      break;
    default: DEBUG_PRINTLN("NOK"); break;
  };


  return;
}


/** rest *********************************************************/

void setup() {

  Serial.begin(115200);
  //handler.init(&Serial);
  delay(199);

  DEBUG_PRINTLN("STARTED");
  // init the pumps
  motorShield.begin();
  for (int i = 0; i < PUMPS_COUNT_MAX; i++) {
    pumps[i].init();
  }

  handler.init((Stream*)&Serial);
}


void loop() {
  handler.loop();
  for (int i = 0; i < PUMPS_COUNT_MAX; i++) {
    //DEBUG_PRINT("Pump"+ String(i));
    pumps[i].loop();
  }q^2z
}
