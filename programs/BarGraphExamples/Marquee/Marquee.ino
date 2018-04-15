/*
   Marquee
   Demostrate several coding technics
   Author Ivan Zuniga
   November 2016

*/

const bool ledState = HIGH;
typedef  void (*funcPos_ptr_t)(byte &pos) ;
funcPos_ptr_t funcPos = &funcUp;

void setup() {
  for (byte ledPin = 2; ledPin <= 13; pinMode(ledPin++, OUTPUT));
}

void loop() {
  blink(13);
  if (timer100ms()) switchLeds();
  if (timer10s()) switchMode();
}

void switchLeds() {
  static byte ledPins[] = { 2, 5, 8};
  for (byte led = 0; led < 3; led++) {
    turnOffLed(ledPins[led]);
    funcPos(ledPins[led]);
    turnOnLed(ledPins[led]);
  }
}

void switchMode() {
  static funcPos_ptr_t funcs[] = { &funcUp, &funcDown};
  funcPos = funcs[random(0, 2)];
}

