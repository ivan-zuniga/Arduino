/* BufferedOLED.cpp
 * Implementa un buffer para el OLED
 * Hace mejor uso del I2C permitiendo a otros dispositivos operar en el mismo bus sin mayor interferencia
 * Ivan Zuniga
 * 2018
 */
#include "BufferedOLED.h"

BufferedOLED boled;

void setupOLED() {
  boled.init();                  // Inicializa el OLED display
  boled.clearDisplay();          // Clear the screen and set start position to top left corner
  boled.setNormalDisplay();      // Set display to normal mode (i.e non-inverse mode)
  boled.setPageMode();           // Set addressing mode to Page Mode
}

void showInit(){
  boled.clearDisplay();
  boled.setTextXY(0,0); boled.putString("Buffered OLED");
  boled.setTextXY(2,0); boled.putString("Pololu MinIMU-9");
  boled.setTextXY(3,0); boled.putString("Arduino AHRS");
  boled.setTextXY(5,0); boled.putString("Ivan Zuniga");

  byte refresh = 16 * 5; 
  while(refresh--) boled.updateDisplay();
  
}

void showLabels(){
  boled.clearDisplay();
  boled.setTextXY(0,0); boled.putString("Buffered OLED");
  boled.setTextXY(1,0); boled.putString("Roll");
  boled.setTextXY(2,0); boled.putString("Pitch");
  boled.setTextXY(3,0); boled.putString("Yaw");
  boled.setTextXY(4, 0); boled.putString("Rnd");
  boled.setTextXY(5, 0); boled.putString("Time");
}

void driveOLED(){
  long tms = millis();
  long static next = 0;
  if(tms >= next){
    next = next + 333; // Cada 1/3 de segundo
    boled.setTextXY(4,5); boled.putNumber(random());
    boled.setTextXY(1,5); boled.putFloat(ToDeg(roll), 1);
    boled.setTextXY(2,5); boled.putFloat(ToDeg(pitch), 1);
    boled.setTextXY(3,5); boled.putFloat(ToDeg(yaw), 1); 
 }

  boled.setTextXY(5,5);  
  boled.putFloat(tms/1000.0, 3); // Cada vez que se llama la funcion

  boled.updateDisplay();
}

void blinkLED(byte mask){ // Siempre la uso para indicar que esta procesando y que tan cargado
  static byte timer = 0;
  if(!(timer++ & mask)) digitalWrite(STATUS_LED,!digitalRead(STATUS_LED));     
}

void delayBlink(int mils){ // Un delay con led parpadeante
  int next = millis() + mils;
  while(millis() < next) {delay(1); blinkLED(0x7F);} 
}

