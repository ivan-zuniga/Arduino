/**
 * Simple buttons for trivia game
 * Ivan Zuniga, 2017
 * 
 */

const int set = 1000, preset = 0, reset =  2000; // constantes logica debounce botones
int button[5]; // contadores para debounce de los botones
byte ligth[4][5][3]; // Buffer para neopixels
byte selected; // [0,5] Equipo que toco primero , cero indica que se esta jugado

void setup() {
  for (int i = 2; i <= 6; pinMode(i++, INPUT), pinMode(i + 6, OUTPUT));
  //TODO Neo Pixel Setup
}

void loop() {
  scanButtons();
  processButtons();
  driveLeds();
  driveNeoPixels();
}

void scanButtons() {
    for (byte pin = 2,  index = 0; pin <= 6; pin++, index++) if (digitalRead(pin)) debouceButton(index); else  button[index] = preset;
}

void processButtons() {
  if (selected && oneShotButton(4)) selected = 0;
  else for (selected = 4; selected != 0 && !oneShotButton(selected - 1); selected--);
}

void driveLeds() {
  if (selected) digitalWrite(selected + 8, HIGH); else PORTB = 0;
}

void driveNeoPixels() {
  if (selected) { // encender neo pixel del equipo
  } else { // jugar con neo pixels
  }
}

void debouceButton(int index) {
  int& b = button[index];
  if (b > 10 && b <= set )b = set; else b++;
}

bool oneShotButton(int index) {
  int& b = button[index];
  if (b == set) return (b = reset);
  return false;
}

