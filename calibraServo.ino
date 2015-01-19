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

void setup() 
{ 
  //initialize servos
  servoX.attach(ServoPinX, POS_MIN_X, POS_MAX_X);  // conectamos el servo en este pin
  servoY.attach(ServoPinY, POS_MIN_Y, POS_MAX_Y);  // conectamos el servo en este pin

  //use the writeMicroseconds to set the linear actuator to a default centered position
  servoX.writeMicroseconds(servoValueX); 
  servoY.writeMicroseconds(servoValueY); 

  Serial.begin(9600);
} 

void loop() 
{ 

  /**************Servo Positions *******************************/
  // leemos los valores del joystick
   JSValueX = analogRead(JOY_PIN_X);
   JSValueY = analogRead(JOY_PIN_Y);
 
   // solo actualizamos si estamos por encima de la zona central (para evitar vibraciones)
   if(JSValueX > DEADBANDHIGH || JSValueX < DEADBANDLOW)
   {
     JSValueMappedX = map(JSValueX, 0, 1023, -speed, speed); //Mapeamos el valor del joystick (0 to 1023) a (-speed to speed)
     int newValueX= servoValueX + JSValueMappedX; //add mapped joystick value to present Value
     if((newValueX>POS_MIN_X) && (newValueX<POS_MAX_X))
     {
       if(newValueX!=servoValueX) // Solo actualizamos si es distinto. Si hay vibraciones podemos hacer un filtrado
       {
           servoValueX=newValueX;
           //usamos writeMicroseconds para hacerlo más preciso
           servoX.writeMicroseconds(servoValueX); 
    
           delay(10); // waits for the servo to get to they're position before continuing 
           Serial.print("x:");
           Serial.println(servoValueX);
       }
     }
   }
    
  if(JSValueY > DEADBANDHIGH || JSValueY < DEADBANDLOW)
   {
     JSValueMappedY = map(JSValueY, 0, 1023, -speed, speed); //Mapeamos el valor del joystick (0 to 1023) a (-speed to speed)
     int newValueY= servoValueY + JSValueMappedY; //add mapped joystick value to present Value
     if((newValueY>POS_MIN_Y) && (newValueY<POS_MAX_Y))
     {
       if(newValueY!=servoValueY) // Solo actualizamos si es distinto. Si hay vibraciones podemos hacer un filtrado
       {
           servoValueY=newValueY;
           //usamos writeMicroseconds para hacerlo más preciso
           servoY.writeMicroseconds(servoValueY); 
    
           delay(10); // waits for the servo to get to they're position before continuing 
           Serial.print("y:");
           Serial.println(servoValueY);
       }
     }
   }  
} 
