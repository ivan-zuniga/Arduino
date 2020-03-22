const int alivePin = 13;
const int buttonPin = A1;
const int buzzerPin = 12;
const int potPin = A2;

void setup() {
  for (byte ledPin = 2; ledPin <= 11; pinMode(ledPin++, OUTPUT));
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
  randomSeed(analogRead(0));
}

bool buttonRead() {
  return !digitalRead(buttonPin);
}

void turnOnLed(byte ledPin) {
  digitalWrite(ledPin, HIGH);
}

void turnOffLed(byte ledPin) {
  digitalWrite(ledPin, LOW);
}

void turnOffAllLeds() {
  for (byte pin = 2; pin <= 11; pin++) //;
    digitalWrite(pin, LOW);
}
void timers() {
  if (millis() >= timerBeep) {
    noTone(buzzerPin);
  }
}

void beep(byte mode) {
  switch (mode) {
    case 1:
      if(timerBeep > millis()) return;
      tone(buzzerPin, 1000);
      timerBeep = millis() + 25;
      break;
    case 2:
      tone(buzzerPin, 3000);
      timerBeep = millis() + 25;
      break;
    case 3:
      tone(buzzerPin, 3000, 100);
      delay(500);
      break;
    case 4:
      tone(buzzerPin, 500, 100);
      delay(500);
      break;
  }
}

short readPot() {
 return analogRead(potPin);
}

void alive() {
  static short counter;
  if (!counter--) digitalWrite(alivePin, !digitalRead(alivePin));
}
