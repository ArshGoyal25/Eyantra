#include<stdlib.h>
int analogPin1 = 4;  
int analogPin2 = 1;
int analogPin3 = 2;
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
int i=0;
int n=0;
int s=0;
int a;
int j;
int flag=1;
char col_arr[6];
#include <Servo.h>

Servo stservo; 
Servo micservo;
 
char check;
/*int redPin= A1;
int greenPin = A2;
int bluePin = A3;*/
void setup()
{
  Serial.begin(9600);
   /*pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
   analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);*/
  pinMode(enA,OUTPUT) ;   
  pinMode(in_1,OUTPUT) ;  
  pinMode(in_2,OUTPUT) ;
  pinMode(enB,OUTPUT) ;   
  pinMode(in_3,OUTPUT) ; 
  pinMode(in_4,OUTPUT) ;
  /*    stservo.attach(11); //Attaches digital pin 3 to standard servo
  micservo.attach(12);//Attaches digital pin 6 to micservo
  stservo.write(0);  //Sets angle to 0
  micservo.write(0); //Sets angle to 0*/
}

/*void communication()
{
  while(1)
  {
    
    
    Serial.write("S");           //The arduino sends out signal "S" to the Pi communicating that it is ready in the right orientaion ( Cue to the PiCam to capture and detect Aruco)
    Serial.flush();
    if(Serial.available())
    {
      check= Serial.read();
      Serial.print(check);
      Serial.flush();
      
    }
    if(int(check)==82 || int(check)==66 || int(check)==71 )
    {
      col_arr[s]=check;
      rgb(check);
      s++;
      return;
    }
  }
}*/

void r_lineSensor()
{

while(a==0)
{
  value1 = analogRead(analogPin1);     // read the input pin
  value2 = analogRead(analogPin2);     // read the input pin
  value3 = analogRead(analogPin3);     // read the input pin
  value = (value1+value2+value3)/3;
  //Serial.print(value1);
  //Serial.print("\t");
  //Serial.print(value2);
  //Serial.print("\t");
  //Serial.print(value3);
  //Serial.print("\n");
  int avg=((value1+value2+value3)/3);
 /* int a= abs(value1-value2);
 int b= abs(test_2-test_3);
 int c= abs(test_1-test_2);*/

if(avg>797)
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
     
   
     delay(250);
     
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
delay(20);
}
}

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
 /* int a= abs(value1-value2);
 int b= abs(test_2-test_3);
 int c= abs(test_1-test_2);*/

if(avg>797)
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
     //right_turn();
     
     //exit(0);

     
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

void u_turn()
{
digitalWrite(in_1,HIGH) ;
digitalWrite(in_2,LOW) ;
analogWrite(enA,200) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,HIGH) ;
analogWrite(enB,200) ;

delay(1300);
}

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


void rlil()
{
  int i;
  i=0;

  while(1)
  {
    value1 = analogRead(analogPin1);     // read the input pin
    value2 = analogRead(analogPin2);     // read the input pin
    value3 = analogRead(analogPin3);     // read the input pin
    value = (value1+value2+value3)/3;
  /*Serial.print(value1);
    Serial.print("\t");
    Serial.print(value2);
    Serial.print("\t");
    Serial.print(value3);
    
    Serial.print("\n");*/
    int avg=((value1+value2+value3)/3);
    if(i==1500)
        break;
    if(value2>value1 & value2>value3)
      {
       digitalWrite(in_1,HIGH) ;
       digitalWrite(in_2,LOW) ;
       analogWrite(enA,255);
       digitalWrite(in_3,HIGH) ;
       digitalWrite(in_4,LOW ) ;
       analogWrite(enB,255) ;
       i++;
      }
     else if(value1>value2 & value1>value3)
      {
  
       digitalWrite(in_1,HIGH) ;
       digitalWrite(in_2,LOW) ;
       analogWrite(enA,255) ;
  
       digitalWrite(in_3,LOW) ;
       digitalWrite(in_4,HIGH) ;
       analogWrite(enB,255) ;
       i++;
       }
  
      else if(value3>value2 & value3>value1)
       {
       digitalWrite(in_1,LOW) ;
       digitalWrite(in_2,HIGH) ;
       analogWrite(enA,255) ;
  
       digitalWrite(in_3,HIGH);
       digitalWrite(in_4,LOW);
       analogWrite(enB,255) ;
       i++;
        }
  }
  delay(12);
}
/////////////////////////////////////////////////////////////////////////

void flil()
{
  int i;
  i=0;

  while(1)
  {
    value1 = analogRead(analogPin1);     // read the input pin
    value2 = analogRead(analogPin2);     // read the input pin
    value3 = analogRead(analogPin3);     // read the input pin
    value = (value1+value2+value3)/3;
  /*Serial.print(value1);
    Serial.print("\t");
    Serial.print(value2);
    Serial.print("\t");
    Serial.print(value3);
    
    Serial.print("\n");*/
    int avg=((value1+value2+value3)/3);
    if(i==1500)
        break;
    if(value2>value1 & value2>value3)
      {
       digitalWrite(in_1,LOW) ;
       digitalWrite(in_2,HIGH) ;
       analogWrite(enA,255);
       digitalWrite(in_3,LOW) ;
       digitalWrite(in_4,HIGH) ;
       analogWrite(enB,255) ;
       i++;
      }
     else if(value1>value2 & value1>value3)
      {
  
       digitalWrite(in_1,HIGH) ;
       digitalWrite(in_2,LOW) ;
       analogWrite(enA,255) ;
  
       digitalWrite(in_3,LOW) ;
       digitalWrite(in_4,HIGH) ;
       analogWrite(enB,255) ;
       i++;
       }
  
      else if(value3>value2 & value3>value1)
       {
       digitalWrite(in_1,LOW) ;
       digitalWrite(in_2,HIGH) ;
       analogWrite(enA,255) ;
  
       digitalWrite(in_3,HIGH);
       digitalWrite(in_4,LOW);
       analogWrite(enB,255) ;
       i++;
        }
  }
  delay(12);
}

void start_colour()
{
  lineSensor();
  right_turn();
  stop_motion();
  /*lineSensor();
  lineSensor();
  lineSensor();
  left_turn();*/
  r_lineSensor();
  stop_motion();
  lineSensor();
  lineSensor();
  lineSensor();
  left_turn();
  stop_motion();
  r_lineSensor();
  
 
  //communication();
   
  
}

void server_motion()
{ 
  j=1;
  while (j<6)
  {
  //lineSensor();
  left_turn();
  lineSensor();
  if (j==3)
    {
      
      digitalWrite(in_1,LOW) ;
     digitalWrite(in_2,HIGH) ;
     analogWrite(enA,255) ;

     digitalWrite(in_3,LOW) ;
     digitalWrite(in_4,HIGH) ;
     analogWrite(enB,255) ;
     
   
     delay(200);
     lineSensor();
    }
  right_turn();
  r_lineSensor();
  stop_motion();
  delay(3000);
  //communication();
  j++;
  }
}

void end_colour()
{
 /* lineSensor();
  right_turn();
  lineSensor();
  lineSensor();
  lineSensor();
  right_turn();
  r_lineSensor();
  stop_motion();
  */
}

void servoMotion()
{  
  //Serial.println("");

  stservo.write(0);
  delay(1000);
  micservo.write(0);
  delay(1000);
  stservo.write(90);
  delay(1000);
  micservo.write(70);
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

void loop()
{
  lineSensor();
  right_turn();
  r_lineSensor();
  flil();
  rlil();
  //servoMotion();
  stop_motion();
  delay(100000);
  
  //start_colour();
  
  //server_motion();
  //end_colour();
 delay(10000);  
 //delay(1000);
}
