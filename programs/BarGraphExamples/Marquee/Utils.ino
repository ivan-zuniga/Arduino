bool timer100ms() {
  static unsigned long next = 0;
  unsigned long current = millis();
  if (current > next) {
    next = current + 100;
    return true;
  } else {
    return false;
  }
}

bool timer10s() {
  static unsigned long next = 0;
  unsigned long current = millis();
  return current > next && (next = current + 10000);
}

void turnOnLed(byte ledPin) {
  if (ledPin >= 2 && ledPin <= 11) digitalWrite(ledPin, ledState);
}

void turnOffLed(byte ledPin) {
  if (ledPin >= 2 && ledPin <= 11) digitalWrite(ledPin, !ledState);
}

void blink(byte const pin) {
  static short counter;
  if (!counter--) digitalWrite(pin, !digitalRead(pin));
}




