// Calibrado de las posiciones de los servos
// Basado en http://learn.robotgeek.com/demo-code/120-arduino-linear-actuator-tutorial-incremental-joystick-for-small-linear-actuator.html



#include <Servo.h>

//Defines
#define ServoPinX 12         // Servo del eje Y
#define ServoPinY 11         // Servo del eje X

#define JOY_PIN_X 0              // Joystick X Analog Pin
#define JOY_PIN_Y 0              // Joystick Y Analog Pin

//generic deadband limits - not all joystics will center at 512, so these limits remove 'drift' from joysticks that are off-center.
#define DEADBANDLOW 482   //decrease this value if drift occurs, increase it to increase sensitivity around the center position
#define DEADBANDHIGH 542  //increase this value if drift occurs, decrease it to increase sensitivity around the center position

//max/min puse values in microseconds to send to the servo
#define POS_MIN_X      575  //fully retracted
#define POS_MAX_X      2200 //fully extended

#define POS_MIN_Y      575  //fully retracted
#define POS_MAX_Y      2200 //fully extended


Servo servoX;    // servo X
Servo servoY;    // servo Y

int JSValueX;             // valor X del joystick. Estará entre 0 and 1023
int JSValueY;             // valor Y del joystick. Estará entre 0 and 1023

int JSValueMappedX;        // Se convierte el valor X leido en el rango del servo
int JSValueMappedY;        // Se convierte el valor Y leido en el rango del servo

int LinearValueX = (POS_MAX_X+POS_MIN_X)/2;   // posicion X actual (empezamos con el valor medio)

int LinearValueY = (POS_MAX_Y+POS_MIN_Y)/2;   // posicion Y actual (empezamos con el valor medio)

int speed = 5;        // velocidad a la que cambiamos la posición. Para hacerlo fino usar 1

void setup() 
{ 
  //initialize servos
  servoX.attach(ServoPinX, POS_MIN_X, POS_MAX_X);  // conectamos el servo en este pin

  //use the writeMicroseconds to set the linear actuator to a default centered position
  linearActuator.writeMicroseconds(LinearValue); 

  Serial.begin(9600);
} 

void loop() 
{ 

  /**************Servo Positions *******************************/
  //read the values from the joystick
   JSValue = analogRead(JOY_PIN);
 
   //only update if the joystick is outside the deadzone (i.e. moved oustide the center position)
   if(JSValue > DEADBANDHIGH || JSValue < DEADBANDLOW)
   {
     ValueMapped = map(JSValue, 0, 1023, speed, -speed); //Map analog value from native joystick value (0 to 1023) to incremental change (speed to -speed).
     int newValue= LinearValue + ValueMapped; //add mapped joystick value to present Value
     if((newValue>POS_MIN) && (newValue<POS_MAX))
     {
       if(newValue!=LinearValue)
       {
           LinearValue=newValue;
           //use the writeMicroseconds to set the servos to their new positions
           linearActuator.writeMicroseconds(LinearValue); 
    
           delay(10); // waits for the servo to get to they're position before continuing 
           Serial.println(LinearValue);
       }
     }
   }
      
} 