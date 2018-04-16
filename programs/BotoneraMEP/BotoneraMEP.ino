/**
   Botonera para concursos
   Ivan A. Zuniga Urena
   02-2017
*/

#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(28, 7, NEO_GRB + NEO_KHZ800);
byte state;
bool state_changed;

void setup() {
  for (int pin = 2; pin <= 6 ; pinMode(pin++, INPUT_PULLUP));
  for (int pin = 8; pin <= 13 ; pinMode(pin++, OUTPUT));
  strip.begin();
  colorFill(strip.Color(0, 0, 0), 0, 28);
  strip.show();
  PORTB = B11111;
  while (digitalRead(6)) blinkPin13();
}

void loop() {
  updateState();
  updateLeds();
  driveJewels();
  blinkPin13();
}

void updateState() {
  static byte old_state = 255;
  if (!digitalRead(6)) state = 0;
  if (!state) for (byte i = 2; i < 6; i++) if (!digitalRead(i)) state = 1 << i - 2;
  state_changed = state != old_state;
  old_state = state;
}

void driveJewels() {
  if (state_changed) colorFill(strip.Color(0, 0, 0), 0, 28);
  if (state) {
    byte s = state == 2 ? 7 : state == 4 ? 14 : state == 8 ? 21 : 0;
    rainbowCycleNoDelay(s, s + 6, 20, 3);
  } else {
    theaterChaseRandomColorNoDelay(0, 28, 75);
  }
}

void updateLeds() {
    if (state_changed) if (state) PORTB = state + 16; else PORTB = B1111;
}
