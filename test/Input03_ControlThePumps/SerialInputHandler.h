#include <stdlib.h>
/** stream input handler, 
* it uses the stream event function of the arduino environment, 
* please also have a look at at examples.
*/

#ifndef SerialInputHandler_H
#define SerialInputHandler_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define MAX_ARGS 6
extern void runCommand(char argv[MAX_ARGS][16], uint8_t argc);



class SerialInputHandler {

private:
  Stream *_stream;
  bool _inputCompleted;

  char _argv[MAX_ARGS][16];
  uint8_t _argc = 0;


  uint8_t _curArg = 0;
  uint8_t _curIndex = 0;


public:

  SerialInputHandler() {
  }

  void init(Stream *stream) {
    _stream = stream;
  }

  void loop() {

    if (_stream->available()) {

      char c = _stream->read();
          
       if(c == '\n'){ // command finished
          _argv[_curArg][_curIndex] = NULL; // terminate string
          _argc = _curArg+1;
          //DEBUG_PRINTLN("Command complete");
          runCommand(_argv, _argc);

          // clear argv
          for(int i =0 ; i > MAX_ARGS; i++){
             memset(_argv[i], 0, sizeof(_argv[i]));
          }
          _curArg = 0;
          _curIndex = 0;
        } else if (c == ' ') { // argument finished
        
          _argv[_curArg][_curIndex] = NULL; // terminate string
          _curArg++;
          _curIndex = 0;

        } else {
          //DEBUG_PRINTLN("Command complete");
          _argv[_curArg][_curIndex] = c;
          _curIndex++;
        }
      }
  }

};


#endif  // SerialInputHandler_H