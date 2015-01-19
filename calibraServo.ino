// Calibrado de las posiciones de los servos
// Basado en http://learn.robotgeek.com/demo-code/120-arduino-linear-actuator-tutorial-incremental-joystick-for-small-linear-actuator.html

#include <Servo.h>

//Defines
#define ServoPinX 11         // Servo del eje Y
#define ServoPinY 10         // Servo del eje X

#define JOY_PIN_X 0              // Joystick X Analog Pin
#define JOY_PIN_Y 1              // Joystick Y Analog Pin

//generic deadband limits - not all joystics will center at 512, so these limits remove 'drift' from joysticks that are off-center.
#define DEADBANDLOW 482   //decrease this value if drift occurs, increase it to increase sensitivity around the center position
#define DEADBANDHIGH 542  //increase this value if drift occurs, decrease it to increase sensitivity around the center position

//max/min puse values in microseconds to send to the servo
#define POS_MIN_X      75  //fully retracted
#define POS_MAX_X      3200 //fully extended

#define POS_MIN_Y      75  //fully retracted
#define POS_MAX_Y      3200 //fully extended


Servo servoX;    // servo X
Servo servoY;    // servo Y

int JSValueX;             // valor X del joystick. Estará entre 0 and 1023
int JSValueY;             // valor Y del joystick. Estará entre 0 and 1023

int JSValueMappedX;        // Se convierte el valor X leido en el rango del servo
int JSValueMappedY;        // Se convierte el valor Y leido en el rango del servo

int servoValueX = (POS_MAX_X+POS_MIN_X)/2;   // posicion X actual (empezamos con el valor medio)

int servoValueY = (POS_MAX_Y+POS_MIN_Y)/2;   // posicion Y actual (empezamos con el valor medio)

int speed = 5;        // velocidad a la que cambiamos la posición. Para hacerlo fino usar 1

controlServo csCadera(12,A0);
controlServo csHombro(11,A1);
controlServo csCodo(10,A2);
controlServo csMunecaX(9,A3);
controlServo csMunecaY(8,A4);
controlServo csPinza(7,A5);


void setup() 
{ 
  Serial.begin(9600);
} 

void loop() 
{ 
  csCadera.checkControlSetServo();
  csHombro.checkControlSetServo();
  csPinza.checkControlSetServo();
  csCodo.checkControlSetServo();
  csMunecaY.checkControlSetServo();
  csMunecaX.checkControlSetServo();
  
} 
