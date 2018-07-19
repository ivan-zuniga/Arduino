/* BufferedOLED.h
 * Implementa un buffer para el OLED
 * Hace mejor uso del I2C permitiendo a otros dispositivos operar en el mismo bus sin mayor interferencia
 * Ivan Zuniga
 * 2018
 */
 
#include <SeeedOLED.h> // https://github.com/Seeed-Studio/OLED_Display_128X64

class BufferedOLED : public SeeedOLED // Reimplenta los metodos agregando el buffer
{
  public:
    void updateDisplay();
    void setTextXY(unsigned char Row, unsigned char Column);
    void putString(const char *String);
    unsigned char putNumber(long n);
    unsigned char putFloat(float floatNumber);
    unsigned char putFloat(float floatNumber,unsigned char decimal);
    
  private:
    byte pos;
    unsigned char screen[16 * 6] = {0}; // Buffer para la pantalla.
};

