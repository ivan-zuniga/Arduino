const int alivePin = 13;
const int buttonPin = A1;
const int buzzerPin = 12;
const int potPin = A2;

void debug() {
  Serial.print(" state ");
  Serial.print(state);
  Serial.print("  button ");
  Serial.print(button);
  Serial.print("  dot ");
  Serial.print(dot);
  Serial.println();
}

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

void ballPos(int &pos) {
  pos += dir;
  if (pos > 11) pos = 2;
  if (pos < 2) pos = 11;
}

void beep(byte mode) {
  switch (mode) {
    case 0:
      if (millis() >= timerBeep) {
        noTone(buzzerPin);
      }
      break;
    case 1:
      tone(buzzerPin, 1000);
      timerBeep = millis() + 100;
      break;
    case 2:
      tone(buzzerPin, 3000);
      timerBeep = millis() + 100;
      break;
    case 3:
      tone(buzzerPin, 3000, 100);
      delay(500);
      break;
    case 4:
      tone(buzzerPin, 500, 500);
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
