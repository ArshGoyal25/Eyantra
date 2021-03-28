/*
 * Team Id: 6338
 * Author List: Arnav,Sujith,Arsh
 * Filename: 6338_Servo_Motors
 * Theme: AntBot
 * Functions: setup(), servoMotion(), loop()
 */ 
 
#include <Servo.h>

Servo stservo; 
Servo micservo;

/*
 * Function Name: setup
 * Input: stservo, micservo
 * Output: Declares digital pins corresponding the motors and sets initial angle to 0 degrees
 * Logic: Inbuilt Class Functions are used to declare the pins and set the angle
 */ 

void setup()
{
  Serial.begin(9600);
  stservo.attach(3); //Attaches digital pin 3 to standard servo
  micservo.attach(6);//Attaches digital pin 6 to micservo
  stservo.write(0);  //Sets angle to 0
  micservo.write(0); //Sets angle to 0
}


/*
 * Function Name: servoMotion()
 * Input: stservo, micservo
 * Output: Passes instructions to the Servo Motors to rotate according to the required application
 * Logic: Inbuilt Class Function and delay() is used to systematically handle the motors.
 * Example call: servoMotion()
 */ 

void servoMotion()
{  
  //Serial.println("");

  stservo.write(0);
  delay(1000);
  micservo.write(0);
  delay(1000);
  stservo.write(100);
  delay(1000);
  micservo.write(80);
  delay(1000);
  stservo.write(0);
  delay(3000);
  stservo.write(100);
  delay(1000);
  micservo.write(0);
  delay(1000);
  stservo.write(0);
  delay(1000);

}

/*
 * Function Name: loop()
 * Input: NONE
 * Output: Rotates the Servo Motors to pick up the box and drop it continously.
 * Logic: servoMotion() is called within this loop and executed 
 */ 

void loop()
{
  servoMotion();
  delay(1000);
}
