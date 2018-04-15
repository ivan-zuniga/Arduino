
const bool ledState = HIGH;             // ledState used to set the LED

int (*funcPos)(int pos) = &funcUpDown;

void setup() {
  for (byte ledPin = 2; ledPin <= 12; pinMode(ledPin++, OUTPUT));
}

void loop() {
  static int ledPin =  2;

  blink(13);

  if (timer()) { // commment { and compile!!!

    turnOffLed(ledPin);

    ledPin = funcPos(ledPin);

    turnOnLed(ledPin);
  }

  if (timer5s()) {
    int (*funcs[])(int pos) = {&funcUpDown, &funcUp, &funcDown};
    funcPos = funcs[random(0, 3)];
  }
}

bool timer() {
  static unsigned long previousMillis = 0;        // will store last time LED was updated
  const long interval = 100;           // interval at which to change led (milliseconds)
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    return true;
  } else {
    return false;
  }
}

bool timer5s() {
  static unsigned long next = 0;
  unsigned long current = millis();
  if (current > next) {
    next = current + 5000;
    return true;
  } else {
    return false;
  }
}


void turnOnLed(byte ledPin) {
  if (ledPin >= 2 && ledPin <= 11)
    digitalWrite(ledPin, ledState);
}

void turnOffLed(byte ledPin) {
  if (ledPin >= 2 && ledPin <= 11)
    digitalWrite(ledPin, !ledState);
}

void blink(byte const pin) {
  static short counter;
  if (!counter--) digitalWrite(pin, !digitalRead(pin));
}

