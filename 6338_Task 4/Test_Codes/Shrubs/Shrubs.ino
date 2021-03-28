#include<stdlib.h>
#include"line.h"


// Setup the Arduino
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

void Shrubs()
{
  if(Serial.available())  
  {
    delay(700);
    //Serial.print("hi");
    n= Serial.parseInt();
    Serial.flush();
   
    if(n==1)
    {
      SH1();
      pick_up();
      rSH1();
    }
    else if(n==2)
    {
      SH2();
      pick_up();
      rSH2();
    }        
    else if(n==3)
    {
      SH3();
      pick_up();
      rSH3();
    }    
    else if(n==4)
    {
      SH4();
      pick_up();
      rSH3();
    }
    else if(n==5)
    {
      SH5();
      pick_up();
      rSH5();
    }
    else if(n==6)
    {
      SH6();
      pick_up();
      rSH6();
    }
  }
  delay(300);
  Serial.flush();
}

void AntHills()
{
  
}

void loop()
{
 start_colour();
 server_motion();
 end_colour();
 delay(10000);  
 //delay(1000);
 }
