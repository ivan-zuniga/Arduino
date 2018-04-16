/**
 * RC controlled two motor car
 * Ivan Zuniga, 2017
 * Over the night PWM remote motor controller 
 * pulseIn() was not god enough, so 
 * ISR on pins is used to read the servo signals
 * from the RC reciever
 * https://www.youtube.com/watch?v=I2RqW_Sa_8w
 * https://www.youtube.com/watch?v=5iSzSycAKR0
 */

#include <PinChangeInt.h>

volatile int pwm_value1 = 0;
volatile int prev_time1 = 0;
volatile int pwm_value2 = 0;
volatile int prev_time2 = 0;
volatile byte last12, last13;
uint8_t latest_interrupted_pin;

int maxpwm1 = 2000, maxpwm2 = 2000;
int minpwm1 = 1000, minpwm2 = 1000;
int cenpwm1 = 1516, cenpwm2 = 1516;
//int cenpwm1 = 1488, cenpwm2= 1484;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  digitalWrite(6, LOW);
  digitalWrite(5, LOW);

  pinMode(12, INPUT);
  pinMode(13, INPUT);

  Serial.begin(57600);

  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  PCintPort::attachInterrupt(12, &pinChange, CHANGE);
  PCintPort::attachInterrupt(13, &pinChange, CHANGE);

  delay(200);
}

/**
 * Read RC reciever servo signals
 */
void pinChange()
{
  if (!last12 && digitalRead(12)) {
    last12 = HIGH;
    prev_time1 = micros();
  }
  if (last12 && !digitalRead(12)) {
    last12 = LOW;
    pwm_value1 = micros() - prev_time1;
  }

  if (!last13 && digitalRead(13)) {
    last13 = HIGH;
    prev_time2 = micros();
  }
  if (last13 && !digitalRead(13)) {
    last13 = LOW;
    pwm_value2 = micros() - prev_time2;
  }

}


void loop() {

  int avance = ((pwm_value1 - cenpwm1) / 4) * - 1;
  int giro = ((pwm_value2 - cenpwm2) / 3) * -1;

  if (pwm_value1 < 500 || pwm_value2 < 500) {
    avance = 0;
    giro = 0;
  }

  int motor1 = avance + giro;
  int motor2 = avance - giro;

  if (motor2 < -255) motor2 = -255;

  if (motor1 > 15) {
    if (motor1 >= 255)
      digitalWrite(10, HIGH);
    else
      analogWrite(10, motor1);
    digitalWrite(9, LOW);
  } else if (motor1 < -10) {
    if (motor1 <= -255)
      digitalWrite(9, HIGH);
    else
      analogWrite(9, - motor1);
    digitalWrite(10, LOW);
  } else {
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
  }

  if (motor2 > 15) {
    if (motor2 >= 255)
      digitalWrite(6, HIGH);
    else
      analogWrite(6, motor2);
    digitalWrite(5, LOW);
  } else if (motor2 < -10) {
    if (motor2 <= -255)
      digitalWrite(5, HIGH);
    else
      analogWrite(5, - motor2);
    digitalWrite(6, LOW);
  } else {
    digitalWrite(6, LOW);
    digitalWrite(5, LOW);
  }
  //Serial.print(motor1); Serial.print("            ");
  //Serial.print(motor2); Serial.println();

  Serial.print(pwm_value1); Serial.print("            ");
  Serial.print(pwm_value2); Serial.println();

  pwm_value1 = 0;
  pwm_value2 = 0;

  delay(50);
}
