//
// 
// Modificado de https://blog.blinkenlight.net/experiments/basic-effects/knight-rider/
// Ivan Zuniga

const byte firstLed = 2, lastLed = 12, speedPot = A2, aliveLed = 13;
const byte brigthLevel[] = {0,0,1,1,1,1,2,4,8,16,32,0,0,0,0,0,0,0,0,0,0};

void setup() { 
    for (byte pin = firstLed; pin < lastLed; pinMode(pin++, OUTPUT));
    pinMode(speedPot, INPUT);
}

void loop() {
  short period = readPot(speedPot)/5 + 50;
  byte currentLed = calcNextLed(period);
  driveLEDs(currentLed);
  blink(aliveLed);
}

byte calcNextLed(const int period) {
  static uint8_t led = firstLed;
  static uint32_t timer = millis() + period;
  if(timer < millis()){
    timer += period ;
    led += random(0,3)-1;
    if(led > lastLed) led = lastLed;
    if(led < firstLed) led = firstLed;
  }
  return led;
}
 
void driveLEDs(const uint8_t currentLed) {
  static uint8_t cycleStep = 0;
  static int8_t led = firstLed;
  digitalWrite(led, (brightness(led, currentLed) > cycleStep ));
  if(led < lastLed) {++led;} else { led = firstLed; ++cycleStep &= B11111;}
}

inline byte brightness(const byte a, const byte b) {    
    return brigthLevel[a - b + 10];
}

