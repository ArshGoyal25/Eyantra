int pi_out=12;
int ard_out=11;
int i=0; 
int enA = 3 ; //Used to handle the speed of motor 1
int in_1 = 8 ; 
int in_2 = 9 ;
int enB = 5 ; //Used to handle the speed of motor 2 
int in_3 = 6 ;
int in_4 = 7 ;
int analogPin1 = 0;  
int analogPin2 = 2;
int analogPin3 = 4;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int value = 0;

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

pinMode(pi_out,INPUT) ;

pinMode(ard_out,OUTPUT) ;

digitalWrite(ard_out,LOW);
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
  Serial.print("\n");
  int avg=((value1+value2+value3)/3);
 /* int a= abs(value1-value2);
 int b= abs(test_2-test_3);
 int c= abs(test_1-test_2);*/
   
if(avg>950)
{
     digitalWrite(in_1,LOW) ;
     digitalWrite(in_2,LOW) ;
     analogWrite(enA,110) ;

     digitalWrite(in_3,LOW) ;
     digitalWrite(in_4,LOW) ;
     analogWrite(enB,110) ;
     ArucoMotion();
    
     delay(1000);
}
else 
{
   if(value2>value1 & value2>value3)
  {
      
   
     
     digitalWrite(in_1,HIGH) ;
     digitalWrite(in_2,LOW) ;
     analogWrite(enA,150);
     digitalWrite(in_3,LOW) ;
     digitalWrite(in_4,HIGH) ;
     analogWrite(enB,150) ;
  }
  else if(value1>value2 & value1>value3)
   {
     digitalWrite(in_1,LOW) ;
     digitalWrite(in_2,HIGH) ;
     analogWrite(enA,150) ;

     digitalWrite(in_3,LOW) ;
     digitalWrite(in_4,HIGH) ;
     analogWrite(enB,150) ;
  }

  else if(value3>value2 & value3>value1)
  {
     digitalWrite(in_1,HIGH) ;
     digitalWrite(in_2,LOW) ;
     analogWrite(enA,150) ;

     digitalWrite(in_3,HIGH) ;
     digitalWrite(in_4,LOW) ;
     analogWrite(enB,150) ;
  }
}

}

void ArucoMotion()

{
digitalWrite(ard_out,HIGH);
Serial.print("sent");


//stopping at central node

digitalWrite(in_1,LOW) ;
digitalWrite(in_2,LOW) ;
analogWrite(enA,255) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,LOW) ;
analogWrite(enB,255) ;

delay(2000) ;

//rotating towards Aruco1

digitalWrite(in_1,LOW) ;
digitalWrite(in_2,HIGH) ;
analogWrite(enA,180) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,HIGH) ;
analogWrite(enB,180) ;
delay(300) ; 

//stopping the robot at the right orientation, ready to detect Aruco 

digitalWrite(in_1,LOW) ;
digitalWrite(in_2,LOW) ;
analogWrite(enA,255) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,LOW) ;
analogWrite(enB,180) ;

delay(1000);

//The robot sequentially rotates to all the Arucos and detects them one by one through the for loop

for(i=0;i<3;i++)
{
       
  delay(3000);
  {
    digitalWrite(in_1,LOW) ;   //Rotating towards the next Aruco
    digitalWrite(in_2,HIGH) ;
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
    delay(1000);
  }
}
if (digitalRead(pi_out)==HIGH)
 {
  Serial.print("dkjf") ;
  digitalWrite(in_1,LOW) ;   //Rotating towards the next Aruco
    digitalWrite(in_2,HIGH) ;
    analogWrite(enA,180) ;

    digitalWrite(in_3,LOW) ;
    digitalWrite(in_4,HIGH) ;
    analogWrite(enB,180) ;
    delay(900);
   //void linesensor();
 }
delay(1000000);

}

void loop()
{
  lineSenor();
  delay(10);
}
