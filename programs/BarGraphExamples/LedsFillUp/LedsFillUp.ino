
unsigned long previousMillis = 0;        // will store last time LED was updated
const long interval = 100;           // interval at which to blink (milliseconds)
bool ledState = HIGH;             // ledState used to set the LED
      
void setup() {
  for(byte ledPin = 2; ledPin <= 11; pinMode(ledPin++, OUTPUT));
}

void loop() {
  static int ledPin =  2;
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if(ledPin == 11) turnOffAllLeds();
    ledPin = funcPos(ledPin);   
    turnOnLed(ledPin);
  }
  analogRead(A2);
  blink(13);
}

void turnOnLed(byte ledPin){
  //if(ledPin>=2 && ledPin<=12)
    digitalWrite(ledPin, ledState);
}

void turnOffLed(byte ledPin){
  //if(ledPin>=2 && ledPin<=12)  
    digitalWrite(ledPin, !ledState);
}

void turnOffAllLeds() {
  for(byte pin = 2; pin <= 11; pin++)//;
    digitalWrite(pin,!ledState);
}

int funcPos(int pos){
  pos+= 1;
  //pos+= -1;
  
  if(pos > 11) pos = 2;
  if(pos < 2) pos = 11;
  return pos;
}

void blink(byte const pin){
  static short counter;
  if(!counter--) digitalWrite(pin,!digitalRead(pin));
}

