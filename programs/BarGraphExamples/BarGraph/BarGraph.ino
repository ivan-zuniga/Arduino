//
//
// Modificado de https://blog.blinkenlight.net/experiments/basic-effects/knight-rider/
// Ivan Zuniga

const byte firstLed = 2, lastLed = 12, speedPot = A2, aliveLed = 13, button = A1;

byte single[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte focus[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 32, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0};
byte standard[] = {1, 1, 1, 1, 1, 1, 1, 2, 6, 16, 32, 16, 6, 2, 1, 1, 1, 1, 1, 1, 1};

byte* brigthLevels[] = {standard, focus, single, single};
byte (*nextLedFunc[])(int period) = {&calcNextLedUpDown, &calcNextLedUpDown, &calcNextLedUp, &calcNextLedRnd};

byte* brigthLevel = *brigthLevels;
byte (*calcNextLed)(int period) = *nextLedFunc;

void setup() {
  for (byte pin = firstLed; pin < lastLed; pinMode(pin++, OUTPUT));
  pinMode(speedPot, INPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  selectMode();
  short period = readPot(speedPot) * 3 + 1000;
  byte currentLed = calcNextLed(period);
  driveLEDs(currentLed);
  blink(aliveLed);
}

byte calcNextLedUpDown(const int period) {
  static uint8_t led = firstLed;
  static byte dir = 1;
  static int counter = 0;
  if (++counter > period) {
    counter = 0;
    led += dir;
    if (led >= lastLed || led <= firstLed) dir *= -1;
  }
  return led;
}

byte calcNextLedUp(const int period) {
  static uint8_t led = firstLed;
  static byte dir = 1;
  static int counter = 0;
  if (++counter > period) {
    counter = 0;
    led += dir;
    if (led > lastLed) led = firstLed;
  }
  return led;
}

byte calcNextLedRnd(const int period) {
  static byte led = random(firstLed, lastLed + 1);
  static int counter = 0;
  if (++counter > period) {
    counter = 0;
    led = random(firstLed, lastLed + 1);
  }
  return led;
}

inline byte brightness(const byte led, const byte pos) {
  return *(brigthLevel + led - pos + 10);
}

void driveLEDs(const uint8_t pos) {
  static uint8_t pass = 0;
  static int8_t led = firstLed;
  digitalWrite(led, (brightness(led, pos) > pass ));
  if (led < lastLed) {
    ++led;
  } else {
    led = firstLed;
    pass++;
    pass &= B11111;
  }
}

void selectMode() {
  static int b1;
  static byte mode;
  if (buttonPress(button, b1)) {
    if (++mode > 3) mode = 0;
    for (byte pin = firstLed; pin < lastLed; digitalWrite(pin++, LOW));
    brigthLevel = brigthLevels[mode];
    calcNextLed = nextLedFunc[mode];
  }
}

