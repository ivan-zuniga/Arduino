void fsm(){
    PRINTDEBUG();
  switch (state) {
    case STANDBY:
      standBy();
      break;
    case GAMEOVER:
      gameOver();
      break;
    case HOTS:
      hots();
      break;
    case CLACKS:
      clacks();
      break;
    case CLICKS:
      clicks();
      checkForGameOver();
      break;
    default:
      dots();
  }
  //if(state>GAMEOVER) checkForGameOver();
}

void dots() {
  PRINT("coldDots");
  dot = state - DOT1;
  if (dotTimer()) {
    beep(1);
    state += dir;
    if (state == DOT1 || state == DOT10) state = HOTS;
    debug();
  }
}

void hots() {
  PRINT("hotDots");
  dot = dir > 0 ? 9 : 0;
  state = button ? CLACKS : CLICKS;
  checkForGameOver();
}

void clacks() {
  PRINT("clacks");
  if (dotTimer()) {
    state = (dir == 1) ? DOT1 : DOT10;
  }
}
void clicks() {
  if (dotTimer()) {
    state = (dir == 1) ? DOT1 : DOT10;
  }
  if (button) { // player clicked! (hit the dot)
    dir *= -1;
    hits++;
    beep(2);
    timerDot = millis() + interval; // reset time for next dot
    interval -= interval / 4;
    state = dir > 0 ? DOT2 : DOT9;
  }
}

void checkForGameOver() {
  if (millis() >= timerGame) {
    turnOffAllLeds();
    turnOnLed(2);
    for (byte ledPin = 3; ledPin <= hits / 5; digitalWrite(ledPin++, HIGH));
    beep(4);
    state = GAMEOVER;
  }
}

void standBy() {
  PRINT("standBy");
  if (button) { // Reset all
    turnOffAllLeds();
    hits = 0;
    beep(3);
    interval = 600 - readPot()/2;
    dir = random(2)? 1: -1;
    timerDot = millis() + interval;
    timerGame = millis() + gameTime;
    state = DOT6;
  }
}

void gameOver() {
  PRINT("gameOver");
  if (button) {
    turnOffAllLeds();
    beep(3);
    state = STANDBY;
  }
}
bool dotTimer() {
  if (millis() >= timerDot) {
    timerDot += interval; return true;
  }
  return false;
}

