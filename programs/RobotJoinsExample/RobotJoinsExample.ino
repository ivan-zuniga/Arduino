/*
 * Ivan Zuniga 2019
 * Programita ejemplo para mover poco a poco las articulaciones de un animalito robotico
 * Las articulaciones estan conformadas por servos
 * No lo he probado todavia
 */
#include <Servo.h>

const int SERVOS = 12;
volatile unsigned long nextMillis = 0;

Servo servo_motor[SERVOS];

enum body_join {LEFT_ARM_1, LEFT_ARM_2, LEFT_ARM_3, RIGHT_ARM_1, RIGHT_ARM_2, RIGHT_ARM_3}; // completar para los nombres de los 12 servos
enum parameter {CURRENT_POS, NEXT_POS, VELOCITY}; // nombres de los datos necesarios para mover un servo poco a poco
volatile int servo_data[SERVOS][3];
volatile boolean move_enabled = false;
void setup()
{
  move_enabled = false;
  int servo_pins[SERVOS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; //asignar poines a los servos
  for (int i = 0; i < SERVOS; i++) {
    servo_motor[i].attach(servo_pins[i]);
  }

  // Timer0 is already used for millis() - we'll just interrupt somewhere
  // in the middle and call the "Compare A" function below

  OCR0A = 0xAF;
  TIMSK0 |= _BV(OCIE0A);
  nextMillis = millis();
}

SIGNAL(TIMER0_COMPA_vect)
{
  // entra aqui cada ms
  // entra en cuerpo la interrupcion cada 20ms, esto da una velocidad minima de 50 grados/segundo
  // hay varias maneras de lograr una velocidad minima menor, lo veremos luego
  // una es usar posiciones en punto flotante, no recomendado. Mejor usar punto fijo.
  // los valores se dividen y mutiplican digamos por 8 (usando shifts x >> 3, x << 3) asi velocity = 1 es 1/256 de grado  
  // tiene un glitch a los 26 dias de encendido, se puede arreglar facil pero te lo dejo de tarea
  if ( millis() < nextMillis) return;
  nextMillis += 20;

  if ( ! move_enabled) return; // pero si esta habilitado el moverse sique

  for (int i = 0; i < SERVOS; i++)
  {
    if ( servo_data[i][VELOCITY] == 0) continue; // no hay velocidad ..ya esta en la pos final
    
    servo_data[i][CURRENT_POS] += servo_data[i][VELOCITY]; // calcula la nueva poscion intermedia
    
    if (  (servo_data[i][VELOCITY] > 0 && servo_data[i][CURRENT_POS] >= servo_data[i][NEXT_POS]) || // articulacion hacia 'adelante' o 
          (servo_data[i][VELOCITY] > 0 && servo_data[i][CURRENT_POS] <= servo_data[i][NEXT_POS]))    // articulacion hacia 'atras'
    {
      servo_data[i][CURRENT_POS] = servo_data[i][NEXT_POS];
      servo_data[i][VELOCITY] = 0;
    }

    servo_motor[i].write(servo_data[i][CURRENT_POS]);
  }
}

inline void next_position(int join, int angle, int velocity) {
  // el param de entrada velocity es positivo pero se inverte en la funcion el signo si el angulo (posicion angular va a decrecer)
  servo_data[join][VELOCITY] = angle - servo_data[join][CURRENT_POS] > 0 ? velocity : velocity * -1;
  servo_data[join][NEXT_POS] = angle;
}

void left_arm_forward(){
  next_position(LEFT_ARM_1, 30, 1);
  next_position(LEFT_ARM_2, 40, 1);
  next_position(LEFT_ARM_3, 90, 1);
}

void left_arm_back(){
  next_position(LEFT_ARM_1, 0, 1);
  next_position(LEFT_ARM_2, 0, 1);
  next_position(LEFT_ARM_3, 0, 1);
}

void loop() {
  // aqui la logica para mover las articulaciones a una dada posicion
  // adelante
  left_arm_forward();
  move_enabled = true;
  delay(2000); // yo no uso delay() en mis programas, pero es mas facil para el ejemplo
  move_enabled = false;

  //atras
  left_arm_back();
  move_enabled = true;
  delay(2000);
  move_enabled = false;
}
