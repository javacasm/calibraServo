#include <Servo.h>
#include <Arduino.h>

// V 0.5
// Calibrado de las posiciones de los servos
// Basado en http://learn.robotgeek.com/demo-code/120-arduino-linear-actuator-tutorial-incremental-joystick-for-small-linear-actuator.html

class controlServo
{
public:

	controlServo(int pinServo,int pinControl,String id,int iPosInicial,boolean bControlType)
	{  	    
          bControledByJoystick=bControlType;  
          init(pinServo,pinControl,id);
          iPOS_Inicial=iPosInicial;        
          iSigno=1;
        }
        
        controlServo(int pinServo,int pinControl,String id,int iPosInicial)
	{  	    
          bControledByJoystick=true;
          init(pinServo,pinControl,id);
          iPOS_Inicial=iPosInicial;        
          iSigno=1;
        }
        
        
	void init(int pinServo,int pinControl,String id)
	{
		iPinControl=pinControl;
		iPinServo=pinServo;
		iPOS_MIN=75;  //fully retracted
		iPOS_MAX=3200;
		iPOS_Inicial=1100;// (iPOS_MAX+iPOS_MIN)/2;
		strID=id;
	}
        
	controlServo(int pinServo,int pinControl,String id)
	{   init(pinServo,pinControl,id); 	}

	int setPosicion(int pos)
	{
		servoValue=pos;
		//usamos writeMicroseconds para hacerlo más preciso		
		servo.writeMicroseconds(servoValue); 		
		delay(10); // waits for the servo to get to they're position before continuing 
	}

	void setSigno(int signo)
	{  iSigno=signo;
           Serial.print("signo"); 
           Serial.print(strID);
           Serial.println(iSigno);
        }

	String getStatus()
	{  if(iSigno==-1)	
            return strID+"(-):"+servoValue+" ";
           else
           return strID+":"+servoValue+" ";
         }

	String getFullStatus()  // Restamos 14 para que se vea en formato A0-A5
	{	return strID+"@"+iPinServo+", A"+(iPinControl-14)+":"+servoValue+" ";} 


	void inicializa()
	{
		//initialize servos
		servo.attach(iPinServo, iPOS_MIN, iPOS_MAX);  // conectamos el servo en este pin y establecemos los valores mínimo y máximo
		setPosicion(iPOS_Inicial);
	}

	String checkControlSetServo() 
	{ 
	  if(bControledByJoystick)
              return checkControlSetServobyJoystick();
          else
              return checkControlSetServobyPotenciometer();
         }
    
     
protected:

        String checkControlSetServobyPotenciometer()
        {
          JSValue=analogRead(iPinControl);
          int newValue= map(JSValue,0,1024,iPOS_MIN,iPOS_MAX);
          if(abs(newValue-servoValue)>2*speed) // Solo actualizamos si es distinto. Si hay vibraciones podemos hacer un filtrado
	  {
		setPosicion(newValue);
       	  }
	  return getStatus();
        }
        
        String checkControlSetServobyJoystick() 
	{ 
		/**************Servo Positions *******************************/
		// leemos los valores del joystick
		JSValue = analogRead(iPinControl);

		// solo actualizamos si estamos por encima de la zona central (para evitar vibraciones)
		if(JSValue > DEADBANDHIGH || JSValue < DEADBANDLOW)
		{
			JSValueMapped = map(JSValue, 0, 1023, -speed, speed); //Mapeamos el valor del joystick (0 to 1023) a (-speed to speed)
			int newValue= servoValue + iSigno*JSValueMapped; //add mapped joystick value to present Value
			if((newValue>iPOS_MIN) && (newValue<iPOS_MAX))
			{
				if(newValue!=servoValue) // Solo actualizamos si es distinto. Si hay vibraciones podemos hacer un filtrado
				{
					setPosicion(newValue);
				}
			}
		}
		return getStatus(); 
                //return getFullStatus();       
        }
	// Ajuste de la zona central del joytstick para ajustar el 0
	const static int DEADBANDLOW=482;   //decrease this value if drift occurs, increase it to increase sensitivity around the center position
	const static int DEADBANDHIGH=542;  //increase this value if drift occurs, decrease it to increase sensitivity around the center position
        
        boolean bControledByJoystick;
        
	int iPOS_MIN;  //fully retracted
	int iPOS_MAX; //fully extended
	int iPOS_Inicial; // Initial Position (empezamos con el valor medio)

	Servo servo;    // servo

	int JSValue;             // valor  del joystick. Estará entre 0 and 1023

	int JSValueMapped;        // Se convierte el valor leido en el rango del servo

	int servoValue;   // posicion actual 

	const static int speed = 25;        // velocidad a la que cambiamos la posición. Para hacerlo fino usar 1

	int iSigno;
	int iPinServo; // Pin al que está conectado el servo

	int iPinControl; // Pin analógico al que se conecta el control

    String strID;

};
