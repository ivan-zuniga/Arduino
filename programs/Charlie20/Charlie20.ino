/***
 * Charlieplexing 20 LEDs adding PWM
 * Ivan Zuniga
 * 2016
 * Charlieplexing is a technique for driving a multiplexed display
 * in which relatively few I/O pins on a microcontroller are used to drive an array of LEDs.
 * The method uses the tri-state logic capabilities of microcontrollers in order to gain
 * efficiency over traditional multiplexing. (Wikipedia)
 * The LEDs can have 32 bright levels each using pulse witdh modulation.
 * This code writes to port B configuration and data registers directly for increased speed.
 * Also it make use of masked oveflowing counters for timing.
 * Display data is stored on flash and copied to a buffer to reduce RAM usage.
 * 
 * 
 * Circuit
 *                       o-----|>|---o--------|>|---o--------|>|---o--0-----|>|---o--------|>|------o
 *                       |           |              |              |              |                 |
 *                       o-----|<|---o--------|<|---o--------|<|---o--0-----|<|---o--------|<|------o
 *          100 Ohms     |           |              |              |              |                 |
 *   D12 ----\/\/\/\-----|-----------|--------------o--------------|--------------|--o              |
 *   D11 ----\/\/\/\-----|-----------o-----------------------------|--o           |  |              |
 *   D10 ----\/\/\/\-----|-----------------------------o-----------|--|-----------o  |              |
 *   D9  ----\/\/\/\-----|--------------o--------------|-----------o  |              |              |
 *   D8  ----\/\/\/\-----o--------------|--------------|--------------|--------------|--------------o
 *                       |              |              |              |              |              |
 *                       o-----|>|------o-----|>|------o-----|>|------o-----|>|------o-----|>|------o
 *                       |              |              |              |              |              |
 *                       o-----|<|------o-----|<|------o-----|<|------o-----|<|------o-----|<|------o
 *
 */

const byte firstLed = 0, lastLed = 19, speedPot = A2, aliveLed = 13;
const byte pinsModes[] = {3, 3, 5, 5, 6, 6, 20, 20, 12, 12, 18, 18, 24, 24, 10, 10, 17, 17, 9, 9};
const byte pinHigh[] = {1, 2, 1, 4, 2, 4, 4, 16, 4, 8, 16, 2, 8, 16, 2, 8, 16, 1, 8, 1};

const byte pics[160] PROGMEM  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // All off
                                 32, 32, 32, 32, 32, 32, 32, 32,  32, 32, 32, 32,  32, 32, 32, 32, 32, 32, 32, 32, // All on
                                 32, 32, 32, 32, 32, 0, 0, 32,  32, 0, 0, 32,  32, 0, 0, 32, 32, 32, 32, 32, // Outher square
                                 0, 0, 0, 0, 0, 32, 32, 0, 0, 32, 32, 0, 0, 32, 32, 0, 0, 0, 0, 0, // Inner square
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Central two
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Central two fade half
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Central two fade quarter
                                 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Central two fade lowest
                                };
byte leds[20];

void setup() {
  pinMode(speedPot, INPUT);
  memcpy_P(leds, pics, 20);
}

void loop() {
  static byte pic;
  if (timer())  memcpy_P(leds, pics + (++pic &= B111) * 20, 20);  ; // Cycle 8 pics
  driveLEDs();
}

bool timer() {
  static unsigned long next = 0;
  short period = readPot() / 5 + 50;
  return millis() > next && (next += period);
}

void driveLEDs() {
  static byte led, pass;
  PORTB = 0;
  DDRB = 255;
  if (leds[led] > pass) {
    DDRB = pinsModes[led];
    PORTB = pinHigh[led];
  }
  if (++led > lastLed ) {
    led = firstLed;
    ++pass &= B11111; // Cycle from 0 to 32
  }
}

short readPot() {
  static short c, r; //counter, reading
  return (!(c-- & 0X3FF)) ? r = analogRead(speedPot) : r;// Read pot every other 1024th call
}




