

const int alivePin = 13;
const int buttonPin = A1;
const int buzzerPin = 12;
const int potPin = A2;
int ledPin =  2;
int ledPinPrev;

unsigned long timerDot = 0;
unsigned long timerBeep = 0;
unsigned long timerGame = 0;

unsigned int interval = 500;
unsigned int gameTime = 1000 * 30;

char dir = 1;
byte clicks = 0;
byte clack = 0;
enum states {STANDBY, PLAY, GAMEOVER};
byte state = STANDBY;

void setup() {
  for (byte ledPin = 2; ledPin <= 11; pinMode(ledPin++, OUTPUT));
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(115200);
}

void debug() {
  Serial.print(" ledPin ");
  Serial.print(ledPin);
  Serial.print(" state ");
  Serial.print(state);
  Serial.print("  button ");
  Serial.print(buttonPressed());
  Serial.print(" ");
  Serial.println();
}


void loop() {
  switch (state) {
    case STANDBY:
      standBy();
      break;
    case PLAY:
      play();
      break;
    case GAMEOVER:
      gameOver();
      break;
  }
  //debug();
  beep(0);
  blink();
}

bool buttonPressed() {
  return !digitalRead(buttonPin);
}

void play() {
  // Next dot
  if (millis() >= timerDot) {
    timerDot += interval;
    turnOffLed(ledPin);
    ledPinPrev = ledPin;
    ballPos(ledPin);
    turnOnLed(ledPin);
    beep(1);
  }

  // Click. Hit the dot
  if (!clack && ((ledPin == 2 && ledPinPrev == 3) || (ledPin == 11 && ledPinPrev == 10))) {
    if (buttonPressed()) { // player clicked! (hit the dot)
      dir *= -1;
      clicks++;
      timerDot = millis(); // go to next dot
      interval -= interval / 4;
      beep(2);
    }
  }

  // Clack before dot
  if ((ledPin == 3 && ledPinPrev == 4) || (ledPin == 10 && ledPinPrev == 9)) {
    if (!clack && buttonPressed()) { // dont allow to click (missed the dot)
      clack = 1;
      beep(3);
    }
  }

  // Clean clack
  if(clack && (ledPin > 3 && ledPin < 10)) {
    clack = 0;
  }

  // Game over
  if (millis() >= timerGame) {
    turnOffAllLeds();
    for (byte ledPin = 2; ledPin <= clicks / 5; digitalWrite(ledPin++, HIGH));
    beep(4);
    state = GAMEOVER;
  }
}

void standBy() {
  if (buttonPressed()) { // Reset all
    turnOffAllLeds();
    ledPin = 6;
    turnOnLed(ledPin);
    clicks = 0;
    clack = 0;
    beep(3);
    interval = 600 - readPot()/2;
    timerDot = millis() + interval;
    timerGame = millis() + gameTime;
    state = PLAY;
  }

}

void gameOver() {
  if (buttonPressed()) {
    turnOffAllLeds();
    beep(3);
    state = STANDBY;
  }
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
      tone(buzzerPin, 500, 100);
      timerBeep = millis() + 100;
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

void blink() {
  static short counter;
  if (!counter--) digitalWrite(alivePin, !digitalRead(alivePin));
}
