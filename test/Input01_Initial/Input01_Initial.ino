/***********************************************
* Test serial input handler
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

#include "SerialInputHandler.h"
SerialInputHandler handler;

void runCommand(char _argv[5][16] , uint8_t argc){
  char command = _argv[0][0];

  int16_t arg1 = atoi(_argv[1]);
  int16_t arg2 = atoi(_argv[2]);

  for(int8_t i; i < argc ; i++){
    DEBUG_PRINTLN( _argv[i]);
  }

}

void setup() {
  Serial.begin(115200);
  handler.init(&Serial);
}


void loop() {
  handler.loop();
}

void serialEvent(){
  //DEBUG_PRINTLN("Serial Event");
  handler.serialEvent();
}