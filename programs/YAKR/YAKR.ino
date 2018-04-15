/**
 * YANR (Yet Another Knight Rider). 
 * Ivan Zuniga. 2016 
 * 
 * Pulse Width Modulation generation example.
 * LEDS are driven by cycle-less a 32 pass (bright levels) PWM out generation function.
 * No interrupts are used so the function must be called frecuently to avoid glitches.
 * 
 */

const byte firstLed = 2, lastLed = 12, speedPot = A2, aliveLed = 13;

void setup() {
  for (byte pin = firstLed; pin < lastLed; pinMode(pin++, OUTPUT));
  pinMode(speedPot, INPUT);
}

void loop() {
  static byte currentLed = firstLed;
  if (isTime()){
    calcNextLed(currentLed);
  }
  driveLEDs(currentLed);
  doMoreStuff();
  blinkAliveLed();
}

bool isTime() {
  // Timer function
  short period = readPot() / 5 + 50;
  static unsigned long next = millis() + period;
  int timeLeft  = next - millis(); 
  return timeLeft < 1  && - timeLeft < period && ((next += period) | 1);
}

void calcNextLed(byte &led) {
  // Position function
  static byte d = 1;
  d =  ((led += d) >= lastLed) ? -1 : ((led <= firstLed) ? 1 : d);
}

void driveLEDs(const byte currentLed) { 
  // Non blocking 32 pass (bright levels) PWM out generation function
  static byte pass = 0, led = firstLed;
  digitalWrite(led, (brightness(led, currentLed) > pass ));
  if (++led > lastLed) {
    led = firstLed;
    ++pass &= B11111;
  }
}

inline byte brightness(const byte a, const byte b) { return (64 >> (abs(a - b) << 2)) | 1;}

short readPot() {
  // As analogRead is slow, we read the pot every just 0x3FF calls
  static short counter, reading;
  return (!(counter-- & 0x3FF)) ? reading = analogRead(speedPot) : reading;
}

void doMoreStuff() { 
  // do more stuff like scan buttons or some state change logic!
}

void blinkAliveLed() {
  // Toggle the alive LED once per counter overflow
  static short counter;
  if (!counter--) digitalWrite(aliveLed, !digitalRead(aliveLed));
}
