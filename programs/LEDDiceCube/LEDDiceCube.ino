/* LED Dice Cube
 *  
 */
#define ON 1
#define OFF 0

const byte diceLEDPin[] = {2,3,4,5,6,7,8};
const byte buttonPin = A1;
const byte buzzerPin = 12;

void setup()
{
  randomSeed(analogRead(0)); // seed a random number generator
  byte led = 7;
  while(led) /* is not zero */ pinMode(diceLEDPin[ --led ], OUTPUT); 
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop()
{
  rollDice(); // then 
  while(buttonIsUp()) chime(ON);
  chime(OFF);
}

void rollDice()
{
  int turns = 40;
  int waitTime = 20;
  digitalWrite(13, LOW);
  while( turns-- )
  { 
    int number = turnDice();
    waitTime += waitTime/10;
    tone(buzzerPin, number * 100 + 500);    
    delay(waitTime);
  }

  digitalWrite(13, HIGH);
  noTone(buzzerPin);
  tone(buzzerPin,262); delay(500);
  tone(buzzerPin,330); delay(500);
  tone(buzzerPin,392); delay(500);
  noTone(buzzerPin);
  delay(1000);
}

unsigned short turnDice()
{
  static unsigned short number; 
  number = random(1,7); // get a random number from 1-6
  driveDiceLeds(number);
  return number;
}

void driveDiceLeds(byte number){
  static byte patterns[] = {B00000001,
                            B00010010,
                            B00011001,
                            B01011010,
                            B01011011,
                            B01111110,
                           };
  for(byte pin = 8; pin >= 2; pin--)
    digitalWrite(pin, LOW);
  
  byte pattern = patterns[number-1];
  for(byte pin = 8; pin >= 2; pin--)
    digitalWrite(pin, ((pattern <<=1) & B10000000));
}


bool buttonIsUp(){
  return digitalRead(buttonPin);
}

void chime(bool On)
{
  static long counter = 0;  
  static long ticks = 100000;
  static int frec = 1000;
  if(!On){
    counter = 0;
    ticks = 100000;
    frec = 500;
    noTone(buzzerPin);
    return;
  }
  
  if(counter == 1) tone(buzzerPin, frec); 
  if(counter > 10000) noTone(buzzerPin);

  if(counter >= ticks) { 
    counter = 0; 
    ticks -= 2000;
    frec += 5;
   }else{
    counter++;
   }
}  
  
