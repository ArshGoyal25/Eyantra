/*
 * Team Id: #6338
 * Author List: Arsh Goyal, Arnav Agarwal, Sujith K
 * Filename: Final_Eyantra
 * Theme: Ant Bot
 * Functions: setup, loop
 * Global Variables: all global variables are declared in the header file line.h
*/
#include<stdio.h>
#include <Servo.h>
#include "line.h"

void setup()
{
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(enA,OUTPUT) ;   
  pinMode(in_1,OUTPUT) ;  
  pinMode(in_2,OUTPUT) ;
  pinMode(enB,OUTPUT) ;   
  pinMode(in_3,OUTPUT) ; 
  pinMode(in_4,OUTPUT) ;
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(Buzzer,OUTPUT);
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);  
  stservo.attach(11); //Attaches digital pin 11 to standard servo
  micservo.attach(12);//Attaches digital pin 12 to micservo
  stservo.write(0);  //Sets angle to 0
  micservo.write(0); //Sets angle to 0
}

void start():
{
  char input;
  Serial.write("X");
  while(1):
  {
    Serial.flush();
    input=Serial.read();
    Serial.flush();
    if (input=='Z')
      return;
  }
}
void loop()
{
  start(); // calls the function to start the task once the robot is switched on
  Aruco_Motion(); // calls the function which takes the robot from the start position to the central node and detects all 4 AruCo markers and returns to the start position
  Service_Motion(); // calls the sequence of functions defined in Colour_Detect in order to detect the 6 supply blocks placed in the Shrubs Area
  get_det(); // gets the data about the ArUco marker
  Queen();
}
