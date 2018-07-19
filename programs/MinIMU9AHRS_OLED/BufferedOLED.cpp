/* BufferedOLED.cpp
 * Implementa un buffer para el OLED
 * Hace mejor uso del I2C permitiendo a otros dispositivos operar en el mismo bus sin mayor interferencia
 * Ivan Zuniga
 * 2018
 */
#include "BufferedOLED.h"

void BufferedOLED::putString(const char *str) {
  strcpy(screen + pos, str);
  pos += strlen(str);
}

unsigned char BufferedOLED::putNumber(long long_num) {
  ltoa(long_num, screen + pos, 10);
  byte f = strlen(screen + pos);
  pos += f;
  return f;
}

unsigned char BufferedOLED::putFloat(float floatNumber) {
  putFloat(floatNumber, 2);
}

unsigned char BufferedOLED::putFloat(float floatNumber, unsigned char decimal) {
  dtostrf(floatNumber, 10, decimal, screen + pos );
  pos += 10;
}

void BufferedOLED::setTextXY(unsigned char Row, unsigned char Column) {
  pos = Row * 16 + Column ;
}

void BufferedOLED::updateDisplay() {
  static byte pos = 95;

  byte ppos = pos;
  do {
    pos++;
    if (pos >= 96) pos = 0;
  } while (!screen[pos]);

  if ((pos - ppos) != 1 || ~(pos & 0xF)) {
    SeeedOLED::setTextXY(pos >> 4, pos & 0xF);
  }

  SeeedOLED::putChar(screen[pos]);

  if (pos) screen[pos] = 0;
  //else  if (screen[0] != '*') screen[0] = '*'; else screen[0] = ' '; // blinker en la pantalla
}
