short readPot(const byte pin){
  static short counter;
  static int reading;
  if(!(counter-- & 0X1FF))
    reading = analogRead(pin);
  return reading; 
}
void blink(byte const pin){
  static short counter;
  if(!counter--) digitalWrite(pin,!digitalRead(pin));
}

