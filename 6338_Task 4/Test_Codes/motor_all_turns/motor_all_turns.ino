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


void right_turn()
{
digitalWrite(in_1,LOW) ;
digitalWrite(in_2,HIGH) ;
analogWrite(enA,200) ;

digitalWrite(in_3,HIGH) ;
digitalWrite(in_4,LOW) ;
analogWrite(enB,200) ;

delay(2000);
}

void left_turn()
{
digitalWrite(in_1,HIGH) ;
digitalWrite(in_2,LOW) ;
analogWrite(enA,200) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,HIGH) ;
analogWrite(enB,200) ;

delay(2000);
}

void reverse_turn()
{
digitalWrite(in_1,LOW) ;
digitalWrite(in_2,HIGH) ;
analogWrite(enA,200) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,HIGH) ;
analogWrite(enB,200) ;

delay(1200);
}

void stop()
{
digitalWrite(in_1,LOW) ;
digitalWrite(in_2,LOW) ;
analogWrite(enA,255) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,LOW) ;
analogWrite(enB,255) ;
delay(10000);
}

void loop()
{
  right_turn();
  left_turn();
 reverse_turn();
  //stop();
}
