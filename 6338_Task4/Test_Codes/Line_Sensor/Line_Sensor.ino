#include <Servo.h>
//#include"line.h"

int analogPin1 = A4;  
int analogPin2 = A1;
int analogPin3 = A2;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int value = 0;
int enA = 3 ; //Used to handle the speed of motor 1
int in_1 = 8 ; 
int in_2 = 9 ;
int enB = 5 ; //Used to handle the speed of motor 2 
int in_3 = 6 ;
int in_4 = 7 ;

void setup()

{
Serial.begin(9600);
// Declaring all the output pins

pinMode(enA,OUTPUT) ;   

pinMode(in_1,OUTPUT) ;  

pinMode(in_2,OUTPUT) ;

pinMode(enB,OUTPUT) ;   

pinMode(in_3,OUTPUT) ; 

pinMode(in_4,OUTPUT) ;

}


void lineSenor()
{
  value1 = analogRead(analogPin1);     // read the input pin
  
  value2 = analogRead(analogPin2);     // read the input pin
  value3 = analogRead(analogPin3);     // read the input pin
  value = (value1+value2+value3)/3;
  Serial.print(value1);
  Serial.print("\t");
  Serial.print(value2);
  Serial.print("\t");
  Serial.print(value3);
  Serial.print("\t");
  Serial.println();
  if(value <70){
    Serial.write("S");
    DCMotion();
    //digitalWrite(Buzzer, HIGH);    
  }
 // else
      //Serial.print("A");
      //digitalWrite(Buzzer, LOW);    

}

void DCMotion()

{

//moving from start to central node  

digitalWrite(in_1,HIGH) ;
digitalWrite(in_2,LOW) ;
analogWrite(enA,240) ;

digitalWrite(in_3,HIGH) ;
digitalWrite(in_4,LOW) ;
analogWrite(enB,255) ;

delay(3300) ;

//stopping at central node

digitalWrite(in_1,LOW) ;
digitalWrite(in_2,HIGH) ;
analogWrite(enA,255) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,HIGH) ;
analogWrite(enB,255) ;

delay(2000) ;
delay(1000000);

}

void loop()
{
 
      lineSenor();
      //DCMotion();
      delay(12);
//  Serial.println("S");
      
}
