#ifndef PumpOrganDefaultPlaylists_h
#define PumpOrganDefaultPlaylists_h

#include <avr/pgmspace.h>

class OrganProgram {
public:
  OrganProgram(uint8_t stepCount, uint8_t pumpCount, int16_t *content)
    : _stepCount(stepCount), _pumpCount(pumpCount), _content(content) {}

  uint8_t _stepCount;
  uint8_t _pumpCount;
  int16_t *_content;
};

#ifdef USE_PROGEMEM
static const PROGMEM int16_t f1[] = {
#else
static const int16_t f1[] = {
#endif
  0, 0, 0, 0,
  255, 255, 0, 0,
  0, 255, 255, 0,
  0, 0, 255, 255,
  0, 0, 0, 0
};
OrganProgram fauntain1(5, 4, f1);


#ifdef USE_PROGEMEM
static const PROGMEM int16_t f2[]  = {
#else
static const int16_t f2[] = {
#endif
  255, 0,0, 0,
  0,255, 0, 0,
  0, 0, 255, 0,
  0, 0, 0, 255,
  0, 0, 255, 0,
  0, 255, 0, 0,
  255, 0, 0, 0,
  0, 0, 0, 0,
  255, 0, 0, 0,
  255, 255, 0, 0,
  255, 255, 255, 0,
  255, 255, 255, 255,
  255, 255, 255, 0,
  255, 255, 0, 0,
  255, 0, 0, 0,
  0, 0, 0, 0,
};
OrganProgram fauntain2(16, 4, f2);

#ifdef USE_PROGEMEM
const static PROGMEM int16_t f3[] = {
#else
const static int16_t f3[] = {
#endif
  0, 0, 0, 0,
  70, 0, 0, 0,
  100, 0, 0, 0,
  150, 0, 0, 0,
  200, 0, 0, 0,
  0, 0, 0, 0,
  0, 70, 0, 0,
  0, 100, 0, 0,
  0, 150, 0, 0,
  0, 200, 0, 0,
  0, 0, 0, 0,
  0, 0, 70, 0,
  0, 0, 100, 0,
  0, 0, 150, 0,
  0, 0, 200, 0,
  0, 0, 0, 0,
  0, 0, 0, 70,
  0, 0, 0, 100,
  0, 0, 0, 150,
  0, 0, 0, 200,
  100, 200, 200, 100,
  200, 100, 100, 200,
  100, 200, 200, 100,
  200, 100, 100, 200,
  100, 200, 200, 100,
  200, 100, 100, 200,
  70, 150, 150, 70,
  0, 100, 100, 0,
  0, 0, 0, 0
};
OrganProgram fauntain3(29, 4, f3);



#endif  // PumpOrganDefaultPlaylists_h
