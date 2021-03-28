#include<stdlib.h>
#include"line.h"
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


void st_to_s3()
{ 
  lineSensor();
  right_turn();
  lineSensor();
  left_turn();
  stop_motion();
  //delay(2000);
  r_lineSensor();
  //delay(2000);
  stop_motion();
  //delay(10000);

}

/*
void node_to_node()
{
  lineSensor();
  return(0);
}

void st_to_s2()
{
  st_to_s1();
  node_to_node();
}

void st_to_s1()
{
  st_to_s2();
  node_to_node();
}
*/

void st_to_sujith()
{
  lineSensor();
  left_turn();
  lineSensor();
  right_turn();
}

void st_to_arnav()
{
  lineSensor();
  right_turn();
  lineSensor();
  left_turn();
}

void st_to_nitin()
{
  lineSensor();
  right_turn();
  lineSensor();
  right_turn();
}

void st_to_arsh()
{
  lineSensor();
  left_turn();
  lineSensor();
  left_turn();
}

void loop()
{
  //lineSensor();
 st_to_sujith();
 stop_motion();
 //st_to_s3();  
 //st_to_s3();  
 //st_to_s3();
 //delay(10000);  
 //delay(1000);
 }
