// Calibrado de las posiciones de los servos
// Basado en http://learn.robotgeek.com/demo-code/120-arduino-linear-actuator-tutorial-incremental-joystick-for-small-linear-actuator.html

#include <Servo.h>
#include "controlServo.h"

controlServo csCadera(12,A0);
controlServo csHombro(11,A1);
controlServo csCodo(10,A2);
controlServo csMunecaX(9,A3);
//controlServo csMunecaY(8,A4);
//controlServo csPinza(7,A5);


void setup() 
{ 
  Serial.begin(9600);
} 

void loop() 
{ 
  csCadera.checkControlSetServo();
  csHombro.checkControlSetServo();
  //csPinza.checkControlSetServo();
  csCodo.checkControlSetServo();
  //csMunecaY.checkControlSetServo();
  csMunecaX.checkControlSetServo();
  
} 
