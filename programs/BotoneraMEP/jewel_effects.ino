// Modified effects form Adafruit NeoPixel example

// rainbow equally distributed throughout
void rainbowCycleNoDelay(byte s, byte e, int p, byte cs) {
  static byte j = 255, q = 2;
  static long next;

  long gap = millis() - next ;
  if (gap > 0 ) {
    next = millis() + p;
    j += cs;
    for (int i = s; i <= e; i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbowNoDelay(byte s, byte e, int p, byte cs) {
  static byte j = 255, q = 3;
  static long next;

  long gap = millis() - next ;
  if (gap > 0 ) {
    next = millis() + p;

    for (uint16_t i = s + q ; i <= e; i = i + 3) {
      strip.setPixelColor(i, Wheel( (byte)(i + j))); //turn every third pixel on
    }

    j += cs;
    if (!q--) {
      q = 2;
      
    }

    for (uint16_t i = s + q; i <= e; i = i + 3) {
      strip.setPixelColor(i, 0);      //turn every third pixel off
    }
    strip.show();
  }
}

//Theatre-style crawling lights with random color effect
void theaterChaseRandomColorNoDelay(byte s, byte e, int p) {
  static byte j = 255, q = 3;
  static long next;

  long gap = millis() - next ;
  if (gap > 0 ) {
    next = millis() + p;

    for (uint16_t i = s + q ; i <= e; i = i + 3) {
      j = random(0,255);
      strip.setPixelColor(i, Wheel( (byte)(i + j))); //turn every third pixel on
    }


    if (!q--) {
      q = 2;
     
    }

    for (uint16_t i = s + q; i <= e; i = i + 3) {
      strip.setPixelColor(i, 0);      //turn every third pixel off
    }
    strip.show();
  }
}



// Fill the dots one after the other with a color
void colorFill(uint32_t c, byte s, byte e) {
  //static byte timer;
  //if(--timer) return;
  for (uint16_t i = s; i <= e; i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}


// Fill the dots one after the other with a color
void colorWipe(uint32_t c, int wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


//Theatre-style crawling lights with rainbow effect
void theaterChaseNoDelay(uint32_t c, uint32_t p) {

  static byte q = 2;
  static int timer;

  timer--;
  timer &= 0xFFF;

  if (!timer) {
    if (!q--) {
      q = 2;
    }

    byte s = p * 7;
    byte e = s + 7;

    for (uint16_t i = s + q ; i < e; i = i + 3) {
      strip.setPixelColor(i, 0); //turn every third pixel on
    }

    strip.show();

    for (uint16_t i = s + q; i < e; i = i + 3) {
      strip.setPixelColor(i, c);      //turn every third pixel off
    }

  }

}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

void blinkPin13(){
  static int timer;
  timer = --timer & 0x7FFF;
  if(!timer)digitalWrite(13, !digitalRead(13));
}

