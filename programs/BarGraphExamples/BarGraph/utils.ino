short readPot(const byte pin){
  static short counter;
  static int reading;
  return (!(counter-- & 0X1FF)) ? reading = analogRead(pin) : reading; 
}
void blink(byte const pin){
  static short counter;
  if(!counter--) digitalWrite(pin,!digitalRead(pin));
}

bool buttonPress(byte pin, int &bstate){
  if(digitalRead(pin) == LOW){
    bstate++;
  }else{
    if(bstate > 5){
       bstate = 0;
       return HIGH;
    }else{ 
      bstate = 0;
      return LOW;
    }
  }
 }

