#include <avr/pgmspace.h>
#define STRINGF(s) (reinterpret_cast<const __FlashStringHelper *> (s))
typedef byte Event;
typedef int8_t Output;
typedef int8_t State;
enum :Output {ONON = 0};
enum :State {SNON = -1};
typedef  struct fsmState {
  Output out;
  State nextState[INPUTS];
} fsmState_t;

Output fsm(Event ev, const fsmState_t *fsmTable, const char stateNames[][5]) {
  static State state = 0;
  static State prevState = -1;
  fsmState_t fsmState;
  memcpy_P(&fsmState, &fsmTable[state], sizeof(fsmState_t));
  Output out = ONON;
  if(state != prevState) out = fsmState.out;
  State nextState = fsmState.nextState[ev];

 if (ev == 1) {
    PRINT(millis());
    PRINT(" Prev "); PRINT(STRINGF(stateNames[prevState + 1]));
    PRINT(" Curr "); PRINT(state); PRINT(" "); PRINT(STRINGF(stateNames[state+1]));
    PRINT(" Next "); PRINT(STRINGF(stateNames[nextState + 1]));
    PRINT(" Out ");  PRINT(out);
    PRINT(" Event "); PRINT(ev);
    PRINTLN();
 }
  prevState = state;
  if (nextState != SNON){
    state = nextState;
  }
  return out;
}

char * readStateName(char *fstr){
  static char str[] = "1234";
  memcpy_P(str, fstr, 5);
  return str;
}


