#include<stdlib.h>
int analogPin1 = 4;  
int analogPin2 = 1;
int analogPin3 = 2;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int value = 0;
int enA = 3 ; 
int in_1 = 8 ; 
int in_2 = 9 ;
int enB = 5 ; 
int in_3 = 6 ;
int in_4 = 7 ;
int i;
int n=0;
int flag=0 ;
void setup()
{
  Serial.begin(9600);
  pinMode(enA,OUTPUT) ;   
  pinMode(in_1,OUTPUT) ;  
  pinMode(in_2,OUTPUT) ;
  pinMode(enB,OUTPUT) ;   
  pinMode(in_3,OUTPUT) ; 
  pinMode(in_4,OUTPUT) ;
}
//////////////////////////////////////////////////////////
void ArucoMotion()
{
lineSensor();
digitalWrite(in_1,LOW) ;
digitalWrite(in_2,HIGH) ;
analogWrite(enA,180) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,HIGH) ;
analogWrite(enB,180) ;
delay(300) ; 

digitalWrite(in_1,LOW) ;
digitalWrite(in_2,HIGH) ;
analogWrite(enA,180) ;

digitalWrite(in_3,HIGH) ;
digitalWrite(in_4,LOW) ;
analogWrite(enB,180) ;
delay(300) ; 
/*
digitalWrite(in_1,LOW) ;
digitalWrite(in_2,HIGH) ;
analogWrite(enA,180) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,HIGH) ;
analogWrite(enB,180) ;
delay(300) ; 
*/
//stopping the robot at the right orientation, ready to detect Aruco 

digitalWrite(in_1,LOW) ;
digitalWrite(in_2,LOW) ;
analogWrite(enA,255) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,LOW) ;
analogWrite(enB,180) ;

delay(1000);

//The robot sequentially rotates to all the Arucos and detects them one by one through the for loop

while(1)
{
  
  
  Serial.write("S");    //The arduino sends out signal "S" to the Pi communicating that it is ready in the right orientaion ( Cue to the PiCam to capture and detect Aruco)
  
  
  if(Serial.available())  
  {
    delay(700);
    //Serial.print("hi");
    n= Serial.parseInt();
    Serial.flush();
   
    if(n==0)
    {
     digitalWrite(in_1,LOW) ;
     digitalWrite(in_2,HIGH) ;
     analogWrite(enA,180) ;

     digitalWrite(in_3,HIGH) ;
     digitalWrite(in_4,LOW) ;
     analogWrite(enB,180) ;
     delay(300) ;  
     lineSensor();
    }
    else
    {
      digitalWrite(in_1,HIGH) ;   //Rotating towards the next Aruco
      digitalWrite(in_2,LOW) ;
      analogWrite(enA,180) ;

      digitalWrite(in_3,LOW) ;
      digitalWrite(in_4,HIGH) ;
      analogWrite(enB,180) ;

      delay(600) ; 

      digitalWrite(in_1,LOW) ;  //Stopping again once the right orientation is reached
      digitalWrite(in_2,LOW) ;
      analogWrite(enA,180) ;

      digitalWrite(in_3,LOW) ;
      digitalWrite(in_4,LOW) ;
      analogWrite(enB,180) ;
      delay(500);
    }
   }
  delay(300);
  Serial.flush();
}
} 
/////////////////////////////////////////////////////////////////// 
 void lineSensor()
{

  while(1)
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
    
    Serial.print("\n");
    int avg=((value1+value2+value3)/3);
   //if(avg>850)
    if(value1>810 & value2>810 || value2>810 & value3>810)
    {
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,LOW) ;
         analogWrite(enA,110) ;
    
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,LOW) ;
         analogWrite(enB,110) ;
        
         delay(1000);       
    
    
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,HIGH) ;
         analogWrite(enA,110) ;
    
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,HIGH) ;
         analogWrite(enB,110) ;
        
         delay(200);
         return;
        
    }
    else 
    {
       if(value2>value1 & value2>value3)
      {
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,HIGH) ;
         analogWrite(enA,150);
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,HIGH ) ;
         analogWrite(enB,150) ;
      }
      else if(value1>value2 & value1>value3)
       {
         digitalWrite(in_1,HIGH) ;
         digitalWrite(in_2,LOW) ;
         analogWrite(enA,150) ;
    
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,HIGH) ;
         analogWrite(enB,150) ;
      }
    
      else if(value3>value2 & value3>value1)
      {
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,HIGH) ;
         analogWrite(enA,150) ;
    
         digitalWrite(in_3,HIGH) ;
         digitalWrite(in_4,LOW) ;
         analogWrite(enB,150) ;
      }
    }
  delay(8);
  }
}
//////////////////////////////////////////////////////////
void stop_motion()
{
digitalWrite(in_1,LOW) ;
digitalWrite(in_2,LOW) ;
analogWrite(enA,255) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,LOW) ;
analogWrite(enB,255) ;
delay(2000);
}
//////////////////////////////////////////////////////////////
void loop()
{
  ArucoMotion();
  stop_motion();
  delay(2000);
  
}
