#include<Arduino.h>
int analogPin1 = A4;  
int analogPin2 = A1;
int analogPin3 = A2;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int value = 0;
int enA = 3 ; 
int in_1 = 7 ; 
int in_2 = 8 ;
int enB = 9 ; 
int in_3 = 4 ;
int in_4 = 2 ;
int redPin= A5;
int greenPin = A6;
int bluePin = A7;
Servo stservo; 
Servo micservo;  
int Buzzer=13;
char col_arr[6]; 

int s=0;
/////////////////////////////////////////////////////////////
void r_lineSensor()
{
  while(1)
  {
      value1 = analogRead(analogPin1);     // read the input pin
      value2 = analogRead(analogPin2);     // read the input pin
      value3 = analogRead(analogPin3);     // read the input pin
      value = (value1+value2+value3)/3;
      int avg=((value1+value2+value3)/3);
      if(avg>797)
      //if(value1>810 && value2>810 || value2>810 && value3>810)
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
          analogWrite(enA,200) ;

          digitalWrite(in_3,LOW) ;
          digitalWrite(in_4,HIGH) ;
          analogWrite(enB,200) ;
          delay(200);
          break;    
      }
      else 
      {
         if(value2>value1 & value2>value3)
         {
           digitalWrite(in_1,HIGH) ;
           digitalWrite(in_2,LOW) ;
           analogWrite(enA,255);
           digitalWrite(in_3,HIGH) ;
           digitalWrite(in_4,LOW ) ;
           analogWrite(enB,255) ;
         }
         else if(value1>value2 & value1>value3)
         {
      
           digitalWrite(in_1,HIGH) ;
           digitalWrite(in_2,LOW) ;
           analogWrite(enA,255) ;
      
           digitalWrite(in_3,LOW) ;
           digitalWrite(in_4,HIGH) ;
           analogWrite(enB,255) ;
          }
      
         else if(value3>value2 & value3>value1)
         {
           digitalWrite(in_1,LOW) ;
           digitalWrite(in_2,HIGH) ;
           analogWrite(enA,255) ;
      
           digitalWrite(in_3,HIGH);
           digitalWrite(in_4,LOW);
           analogWrite(enB,255) ;
          }
    }
    delay(12);
  }
}
/////////////////////////////////////////////////////////////
void lineSensor()
{

  while(1)
  {
    value1 = analogRead(analogPin1);     // read the input pin
    value2 = analogRead(analogPin2);     // read the input pin
    value3 = analogRead(analogPin3);     // read the input pin
    //value = (value1+value2+value3)/3;
    int avg=((value1+value2+value3)/3);
      Serial.print(value1);
  Serial.print("\t");
  Serial.print(value2);
  Serial.print("\t");
  Serial.print(value3);
  Serial.print("\t");
  Serial.println();
    if(avg>797)
    //if(value1>810 & value2>810 || value2>810 & value3>810)
    {
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,LOW) ;
         analogWrite(enA,255) ;
    
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,LOW) ;
         analogWrite(enB,255) ;
        
         delay(2000);       
    
    
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,HIGH) ;
         analogWrite(enA,255) ;
    
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,HIGH) ;
         analogWrite(enB,255) ;
        
         delay(50);
         return;
        
    }
    else 
    {
       if(value2>value1 & value2>value3)
      {
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,HIGH) ;
         analogWrite(enA,255);
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,HIGH ) ;
         analogWrite(enB,255) ;
      }
      else if(value1>value2 & value1>value3)
       {
         digitalWrite(in_1,HIGH) ;
         digitalWrite(in_2,LOW) ;
         analogWrite(enA,255) ;
    
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,HIGH) ;
         analogWrite(enB,255) ;
      }
    
      else if(value3>value2 & value3>value1)
      {
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,HIGH) ;
         analogWrite(enA,255) ;
    
         digitalWrite(in_3,HIGH) ;
         digitalWrite(in_4,LOW) ;
         analogWrite(enB,255) ;
      }
    }
  delay(12);
  }
}
/////////////////////////////////////////////////////////////////////
void left_turn()
{
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  analogWrite(enA,255) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(enB,255) ;  
  delay(450);
  
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  analogWrite(enA,255) ;
  
  digitalWrite(in_3,HIGH) ;
  digitalWrite(in_4,LOW) ;
  analogWrite(enB,255) ;  
  delay(635);
}
/////////////////////////////////////////////////////////////////////////////
void right_turn()
{
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  analogWrite(enA,255) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(enB,255) ;  
  delay(450);
  
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,LOW) ;
  analogWrite(enA,255) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(enB,255) ;
  delay(635);
}
////////////////////////////////////////////////////////////////////////////
void u_turn()
{
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,LOW) ;
  analogWrite(enA,255) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(enB,255) ;
  delay(1270);
}
////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////
