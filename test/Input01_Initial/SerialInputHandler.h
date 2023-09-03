/** Serial input handler, 
* it uses the serial event function of the arduino environment, 
* please also have a look at at examples.
*/

#ifndef SerialInputHandler_H
#define SerialInputHandler_H

#define MAX_ARGS 5
extern void runCommand(char argv[MAX_ARGS][16], uint8_t argc);



class SerialInputHandler {

private:
  Stream *_serial;
  bool _stringComplete;
  String _serialInput;
  
  
  char _argv[MAX_ARGS][16]; // könnte problem geben weil _maxArgs nicht const ist
  
  uint8_t _curArg = 0;
  uint8_t _curIndex = 0;


public:

  SerialInputHandler() {
    _serialInput.reserve(40);
  }

  void init(Stream *serial) {
    _serial = serial;
  }

  void loop() {
    
  }

  /* Clear the current command parameters */
  void resetCommand() {

    // init argv strings
    for(uint8_t i = 0; i < MAX_ARGS ; i++){
      memset(_argv[i], '\0', sizeof(_argv[i]));
    }
    _curArg = 0;
    _curIndex = 0;
  }



  void serialEvent() {
    char received;

    if (Serial.available()) {
      received = (char)Serial.read();

      // check if command is complete
      if (received == '\n') {
        DEBUG_PRINTLN("Command end");
        // close string 
        _argv[_curArg][_curIndex]= '\0';

        runCommand(_argv, _curArg+1);
        resetCommand();

        return;
      }

      // arguments are divided by spaces
      if(received == ' '){
          DEBUG_PRINTLN("Argument end");
          // close last string 
          _argv[_curArg][_curIndex]= '\0';

          // ready for next argument
          _curArg ++;

          // reset index
          _curIndex = 0;

        return;
      }     

      // just read the content
      _argv[_curArg][_curIndex] = received;
      _curIndex ++;
    }
  }





};


#endif  // SerialInputHandler_H