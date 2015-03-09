// V 0.5
// Calibrado de las posiciones de los servos
// Basado en http://learn.robotgeek.com/demo-code/120-arduino-linear-actuator-tutorial-incremental-joystick-for-small-linear-actuator.html

#include <Servo.h>
#include "controlServo.h"

#define nDOF 6

// Vamos a crear una estructura para almacenar una posicion completa
struct position
{
  char name[4];
  int pos[nDOF];
};

controlServo csHip(12,A0,"H",1320,false);  // Use potenciometer to control
controlServo csSoulder(11,A1,"S",1018);
controlServo csElbow(10,A2,"E",1600);
controlServo csWristP(9,A3,"WP",1100);
controlServo csWristR(8,A4,"WR",1023);
controlServo csGrip(7,A5,"G",1000);
controlServo servos[]={csHip,csSoulder,csElbow,csWristP,csWristR,csGrip};

void setup() 
{ 
  Serial.begin(9600);

  for(int i=0;i<nDOF;i++)
  {    servos[i].inicializa();  }

  csSoulder.setSigno(-1);
  csElbow.setSigno(-1);  
 /* csHip.inicializa();
  csSoulder.inicializa();
  csElbow.inicializa();
  csWristP.inicializa();
  csHip.inicializa();
  csGrip.inicializa();*/
} 

String strStatusOld="";
void loop() 
{ 
/*  csHip.checkControlSetServo();
  csSoulder.checkControlSetServo();
  csGrip.checkControlSetServo();
  csElbow.checkControlSetServo();
  csWristR.checkControlSetServo();
  csWristP.checkControlSetServo();*/
  
  String strStatus="";
  for(int i=0;i<nDOF;i++)
  {  strStatus+=servos[i].checkControlSetServo(); }
  if(strStatus!=strStatusOld)
  {
    Serial.println(strStatus);
    strStatusOld=strStatus;
  }
} 
