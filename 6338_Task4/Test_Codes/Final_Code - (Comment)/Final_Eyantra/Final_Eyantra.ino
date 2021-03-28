#include<stdio.h>
#include <Servo.h>
#include "line.h"
#include<Arduino.h>

//////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  pinMode(enA,OUTPUT) ;   
  pinMode(in_1,OUTPUT) ;  
  pinMode(in_2,OUTPUT) ;
  pinMode(enB,OUTPUT) ;   
  //pinMode(in_3,OUTPUT) ; 
  //pinMode(in_4,OUTPUT) ;
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(Buzzer,OUTPUT);
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);  
  stservo.attach(11); //Attaches digital pin 3 to standard servo
  micservo.attach(12);//Attaches digital pin 6 to micservo
  stservo.write(0);  //Sets angle to 0
  micservo.write(0); //Sets angle to 0
}
///////////////////////////////////////////////////////////////

void loop()
{
  lineSensor();
  //Aruco_Motion();
  //Service_Motion();
  //get_det();
  //Queen();
}
