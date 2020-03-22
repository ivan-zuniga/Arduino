/* ClickClackFSM
   Implemtacion de minijuego Click Clack
   FSM simple
   Ivan Zuniga
   2018

*/
#if 1
#define PRINT(a) Serial.print(a);
#define PRINTLN(a) Serial.println(a);
#define PRINTDEBUG() debug();
#else
#define PRINT(a)
#define PRINTDEBUG()
#endif

byte button;
unsigned long timerDot = 0;
unsigned long timerBeep = 0;
unsigned long timerGame = 0;
unsigned int interval = 2000;
unsigned long gameTime = 1000L * 90;
int dir = -1;
bool play = false;
byte hits = 0;
int dot;

#define INPUTS 5
#include "FSM.h"
enum :Event {ENON , EBUTTON, ETIMERUP, ETIMERDW, EGAMEOVER};
enum :State {SSB, STA, SGV, SH1, SH10, SI1, SI10, SX1, SX10, SA1, SA10, SD1, SD2, SD3, SD4, SD5, SD6, SD7, SD8, SD9, SD10};
enum :Output {WAIT = -4, OVER = -3, START = -2, CLICK = -1, DOT1 = 1, DOT2, DOT3, DOT4, DOT5, DOT6, DOT7, DOT8, DOT9, DOT10};
const PROGMEM 
char stateNames[][5] = {"SNON", "SSB", "STA", "SGV", "SH1", "SH10", "SI1", "SI10", "SX1", "SX10", "SA1", "SA10", "SD1", "SD2", "SD3", "SD4", "SD5", "SD6", "SD7", "SD8", "SD9", "SD10"};

// Output, Event/State {ENONE , EBUTTON, ETIMERUP, ETIMERDW, EGAMEOVER}
const PROGMEM fsmState_t fsmTable[SD10 + 1] = {
  {WAIT, {SNON, STA,  SNON, SNON, SNON}}, // STANDBY
  {START,{SD6,  SD6,  SNON, SNON, SNON}}, // START
  {OVER, {SNON, SSB,  SNON, SNON, SNON}}, // GAMEOVER
  {DOT1, {SI1,  SA1,  SNON, SNON, SGV }}, // SH1

  {DOT10, {SI10, SA10, SNON, SNON, SGV }}, // SH10
  {DOT1, {SNON, SX1,  SNON, SD10, SNON}}, // SI1
  {DOT10,{SNON, SX10, SD1,  SNON, SGV }}, // SI10
  {CLICK,{SD2,  SD2,  SNON, SNON, SNON}}, // SX1

  {CLICK,{SD9,  SD9,  SNON, SNON, SGV }}, // SX10
  {DOT1, {SNON, SNON, SNON, SD10, SGV }}, // SA1
  {DOT10,{SNON, SNON, SD1,  SNON, SGV }}, // SA10
  {DOT1, {SNON, SNON, SD2,  SNON, SGV }}, // SD1

  {DOT2, {SNON, SNON, SD3,  SH1,  SGV }}, // SD2
  {DOT3, {SNON, SNON, SD4,  SD2,  SGV }}, // SD3
  {DOT4, {SNON, SNON, SD5,  SD3,  SGV }}, // SD4
  {DOT5, {SNON, SNON, SD6,  SD4,  SGV }}, // SD5

  {DOT6, {SNON, SNON, SD7,  SD5,  SGV }}, // SD6
  {DOT7, {SNON, SNON, SD8,  SD6,  SGV }}, // SD7
  {DOT8, {SNON, SNON, SD9,  SD7,  SGV }}, // SD8
  {DOT9, {SNON, SNON, SH10, SD8,  SGV }}, // SD9

  {DOT10,{SNON, SNON, SNON, SD9,  SGV }}  //SD10
}; 

void loop() {
  alive();
  timers();
  Output out = fsm(input(), fsmTable, stateNames);
  output(out);
}
Event input() {
  Event currEv = ENON;
  if(millis() >= timerGame)  currEv =  EGAMEOVER;
  button = buttonRead();
  if (button){currEv = EBUTTON;}
  if (dotTimer()) currEv =  dir > 0 ? ETIMERUP : ETIMERDW;
  return currEv ;
}

void output(Output out) {
    PRINTLN(out);
    switch (out) {
      case ONON: 
        break;
      case WAIT: 
        timerGame = 0 - 1;
        turnOffAllLeds(); 
        break;
      case CLICK:
        dir *= -1;
        hits++;
        interval -= interval / 8;
        beep(2); break;
      case START:
        start(); break;
      case OVER:
        over(); break;
      default:
        dot = out;
        setDot();
        beep(1);
    }

}

void start() {
  turnOffAllLeds();
  hits = 0;
  beep(3);
  interval = 1000 - readPot() / 2;
  dir = random(2) ? 1 : -1;
  timerDot = millis() + interval;
  timerGame = millis() + gameTime;
  play = true;
}

bool dotTimer() {
  if (millis() >= timerDot) { timerDot += interval; return true; }
  return false;
}

void setDot() {
  static int ledPin = 2;
  turnOffLed(ledPin);
  ledPin =  dot + 1;
  turnOnLed(ledPin);
}

void over() {
    if(play){
      play = false;
      turnOffAllLeds();
      for (byte ledPin = 3; ledPin <= hits / 5; digitalWrite(ledPin++, HIGH));
      beep(4);
    }
}

void debug() {
    PRINT(" button "); PRINT(button);
    PRINT(" dot ");    PRINT(dot);
    PRINT("  dir ");   PRINT(dir);
}


