/*
 * Team Id: #6338
 * Author List: Arsh Goyal, Arnav Agarwal, Sujith K
 * Filename: line.h
 * Theme: Ant Bot
 * Functions: reverse_lineSensor, lineSensor, left_turn, right_turn, u_turn, stop_motion
 * Global Variables: redPin, greenPin, bluePin, analogPin1, analogPin2, analogPin3, value1, value2, value3, value, enA, in_1, in_2, in_3, in_4, enB, i, j, n, a
*/
int analogPin1 = 4;  // this is the analog pin connected to the right sensor of the 3 channel line sensor
int analogPin2 = 1;  // this is the analog pin connected to the middle sensor of the 3 channel line sensor
int analogPin3 = 2;  // this is the analog pin connected to the left sensor of the 3 channel line sensor
int value1 = 0;     // this is the analog value which is read by the arduino nano from the right sensor
int value2 = 0;     // this is the analog value which is read by the arduino nano from the middle sensor
int value3 = 0;    // this is the analog value which is read by the arduino nano from the left sensor
int avg=0;    // this is the average of the analog readings from the three sensors
int enA = 3 ; // this is the PWM pin connected for motor 1 which is used to control the speed of the motor
int in_1 = 8 ; // this is the output pin from the arduino for motor 1
int in_2 = 9 ; // this is the output pin from the arduino for motor 1
int enB = 5 ;  // this is the PWM pin connected for motor 2 which is used to control the speed of the motor
int in_3 = 6 ; // this is the output pin from the arduino for motor 2
int in_4 = 7 ; // this is the output pin from the arduino for motor 2
int redPin= A5; // this is the analog pin which is connected to the red lead of the RGB LED
int greenPin = A6; // this is the analog pin which is connected to the green lead of the RGB LED
int bluePin = A7;  // this is the analog pin which is connected to the blue lead of the RGB LED
Servo stservo; // this is the standard servo motor
Servo micservo; // this is the micro servo motor 
int Buzzer=13; // this is the digital pin connected as an output for the buzzer
char col_arr[6]; // this array stores the position as well as the colour of the blocks placed at the Shrub Area
int check;
/*
 * Function Name: reverse_lineSensor
 * Input: none
 * Output: none
 * Logic: This function is used to bring the robot back to a node after a particular turn. 
 * We are using the line Sensor code only but the only difference is the direction of the potential
 * applied across the two terminals of the DC motors is reversed. This makes the robot move backwards while following the black line.
 * Example Call: reverse_lineSensor
 */ 
void reverse_lineSensor()
{
  while(1)
  {
      value1 = analogRead(analogPin1);     // read the analog value for the right sensor (0-1023)
      value2 = analogRead(analogPin2);     // read the analog value for the middle sensor (0-1023)
      value3 = analogRead(analogPin3);     // read the analog value for the left sensor (0-1023)
      int avg=((value1+value2+value3)/3);  // the average of the three sensors is calculated 
      if(avg>797)                          // if the average is above 797 that means a node is encountered and the robot stops for one second and moves forward for a very small amount of time
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
         if(value2>value1 & value2>value3) // if the middle sensor is on the black line while the other two are on white, the robot will continue to move backwards
         {
           digitalWrite(in_1,HIGH) ;
           digitalWrite(in_2,LOW) ;
           analogWrite(enA,255);
           digitalWrite(in_3,HIGH) ;
           digitalWrite(in_4,LOW ) ;
           analogWrite(enB,255) ;
         }
         else if(value1>value2 & value1>value3) // if the right sensor is on the black line while the other two are on white, the robot will turn left
         {
      
           digitalWrite(in_1,HIGH) ;
           digitalWrite(in_2,LOW) ;
           analogWrite(enA,255) ;
      
           digitalWrite(in_3,LOW) ;
           digitalWrite(in_4,HIGH) ;
           analogWrite(enB,255) ;
          }
      
         else if(value3>value2 & value3>value1) // if the left sensor is on the black line while the other two are on white, the robot will turn right
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
/*
 * Function Name: lineSensor
 * Input: none
 * Output: none
 * Logic: This function is used to make the robot follow the black line in the arena.
 * We are reading the analog input from the three phototransistors using the basic analogRead function. 
 * The nodes are detected using the average of the three sensors. 
 * Example Call: lineSensor
 */ 
void lineSensor()
{

  while(1)
  {
     value1 = analogRead(analogPin1);     // read the analog value for the right sensor (0-1023)
     value2 = analogRead(analogPin2);     // read the analog value for the middle sensor (0-1023)
     value3 = analogRead(analogPin3);     // read the analog value for the left sensor (0-1023)
     int avg=((value1+value2+value3)/3);  // the average of the three sensors is calculated 
     if(avg>797)                          // if the average is above 797 that means a node is encountered and the robot stops for one second and moves forward for a very small amount of time
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
       if(value2>value1 & value2>value3)  // if the middle sensor is on the black line while the other two are on white, the robot will continue to move forwards
      {
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,HIGH) ;
         analogWrite(enA,255);
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,HIGH ) ;
         analogWrite(enB,255) ;
      }
      else if(value1>value2 & value1>value3) // if the right sensor is on the black line while the other two are on white, the robot will turn right 
       {
         digitalWrite(in_1,HIGH) ;
         digitalWrite(in_2,LOW) ;
         analogWrite(enA,255) ;
    
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,HIGH) ;
         analogWrite(enB,255) ;
      }
    
      else if(value3>value2 & value3>value1) // if the left sensor is on the black line while the other two are on white, the robot will turn left
      {
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,HIGH) ;
         analogWrite(enA,255) ;
    
         digitalWrite(in_3,HIGH) ;
         digitalWrite(in_4,LOW) ;
         analogWrite(enB,255) ;
      }
    }
  delay(15);
  }
}
/*
 * Function Name: left_turn
 * Input: none
 * Output: none
 * Logic: This function is used to make the robot perform a left turn. 
 * We are making the robot move forward and then turn left so it is oriented perfectly after the turn.
 * Example Call: left_turn()
 */ 
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
/*
 * Function Name: right_turn
 * Input: none
 * Output: none
 * Logic: This function is used to make the robot perform a right turn. 
 * We are making the robot move forward and then turn right so it is oriented perfectly after the turn.
 * Example Call: right_turn()
 */ void right_turn()
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
/*
 * Function Name: u_turn
 * Input: none
 * Output: none
 * Logic: This function is used to make the robot perform a 180 degree turn.
 * We are turning it clockwise for a certain amount of time till it is facing the other way.
 * Example Call: u_turn()
 */ 
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
/*
 * Function Name: stop_motion
 * Input: none
 * Output: none
 * Logic: This function is used to make the robot stop moving.
 * We are setting both the input pins for both the motors (in_1, in_2, in_3, in_4) to the LOW state so the motors do not rotate.
 * Example Call: stop_motion()
 */ 
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
