/* ClickClackFSM
   Implemtacion de minijuego Click Clack
   FSM naive
   Ivan Zuniga
   2018

*/
#if 1
#define PRINT(a) Serial.println(a);
#define PRINTDEBUG() debug();
#else
#define PRINT(a) 
#define PRINTDEBUG()
#endif

byte button;
unsigned long timerDot = 0;
unsigned long timerBeep = 0;
unsigned long timerGame = 0;

unsigned int interval = 500;
unsigned long gameTime = 1000L * 90;
char dir = 1;
byte hits = 0;
enum states {STANDBY, GAMEOVER, HOTS, CLICKS, CLACKS, DOT1, DOT2, DOT3, DOT4, DOT5, DOT6, DOT7, DOT8, DOT9, DOT10};
byte state = STANDBY;

int dot;

void loop() {
  // Entrada
  readBtn();
  // Logica 
  fsm();
  // Salida
  setDot(); 
  beep(0);
  alive();
}

void readBtn(){
  button = buttonRead();
}

void setDot() {
  byte d = dot + 2;
  static int ledPin = 2;
  if (ledPin != d) {
    turnOffLed(ledPin);
    ledPin = d;
    turnOnLed(ledPin);
  }
}

