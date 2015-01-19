#include <Servo.h>
#include <Arduino.h>

// Calibrado de las posiciones de los servos
// Basado en http://learn.robotgeek.com/demo-code/120-arduino-linear-actuator-tutorial-incremental-joystick-for-small-linear-actuator.html

class controlServo
{
public:


	controlServo(int pinServo,int pinControl)
	{
	    iPinControl=pinControl;
	    iPinServo=pinServo;
      	iPOS_MIN=75;  //fully retracted
	    iPOS_MAX=3200;

	}

	int setPosicion(int pos)
	{
		servoValue=pos;
		//usamos writeMicroseconds para hacerlo más preciso		
		servo.writeMicroseconds(servoValue); 		
        delay(10); // waits for the servo to get to they're position before continuing 
        Serial.print(iPinServo);
        Serial.print(":");
        Serial.println(servoValue);

	}

	void inicializa()
	{
		//initialize servos
		servo.attach(iPinServo, iPOS_MIN, iPOS_MAX);  // conectamos el servo en este pin y establecemos los valores mínimo y máximo
		setPosicion((iPOS_MAX+iPOS_MIN)/2);
	}



    void checkControlSetServo() 
    { 
      
        /**************Servo Positions *******************************/
        // leemos los valores del joystick
        JSValue = analogRead(iPinControl);
         
       
        // solo actualizamos si estamos por encima de la zona central (para evitar vibraciones)
        if(JSValue > DEADBANDHIGH || JSValue < DEADBANDLOW)
        {
           JSValueMapped = map(JSValue, 0, 1023, -speed, speed); //Mapeamos el valor del joystick (0 to 1023) a (-speed to speed)
           int newValue= servoValue + JSValueMapped; //add mapped joystick value to present Value
           if((newValue>iPOS_MIN) && (newValue<iPOS_MAX))
           {
             if(newValue!=servoValue) // Solo actualizamos si es distinto. Si hay vibraciones podemos hacer un filtrado
             {
                 setPosicion(newValue);
             }
           }
        }
    }
     
protected:
	// Ajuste de la zona central del joytstick para ajustar el 0
	const static int DEADBANDLOW=482;   //decrease this value if drift occurs, increase it to increase sensitivity around the center position
	const static int DEADBANDHIGH=542;  //increase this value if drift occurs, decrease it to increase sensitivity around the center position

	int iPOS_MIN;  //fully retracted
	int iPOS_MAX; //fully extended

	Servo servo;    // servo

	int JSValue;             // valor  del joystick. Estará entre 0 and 1023

	int JSValueMapped;        // Se convierte el valor leido en el rango del servo

	int servoValue;   // posicion actual (empezamos con el valor medio)

	const static int speed = 5;        // velocidad a la que cambiamos la posición. Para hacerlo fino usar 1

	int iPinServo; // Pin al que está conectado el servo

	int iPinControl; // Pin analógico al que se conecta el control


};
