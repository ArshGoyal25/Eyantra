/*
 * Team Id: 6338
 * Author List: Arnav,Sujith,Arsh
 * Filename: 6338_DC_Motor
 * Theme: AntBot
 * Functions: setup() , loop()
 * Global Variables: i, enA, in_1, in_2, enB, in_3, in_4 
*/ 
 
 int i=0; 

 int enA = 3 ; //Used to handle the speed of motor 1

 int in_1 = 8 ; 

 int in_2 = 9 ;

 int enB = 5 ; //Used to handle the speed of motor 2 

 int in_3 = 6 ;

 int in_4 = 7 ;


/*
 * Function Name: setup
 * Input: i, enA, in_1, in_2, enB, in_3, in_4
 * Output: Declares each of pins assigned to the given variables as output.
 * Logic: Function pinMode() is used to declare the pins as output 
 */ 

void setup()

{

// Declaring all the output pins

pinMode(enA,OUTPUT) ;   

pinMode(in_1,OUTPUT) ;  

pinMode(in_2,OUTPUT) ;

pinMode(enB,OUTPUT) ;   

pinMode(in_3,OUTPUT) ; 

pinMode(in_4,OUTPUT) ;

}

/*
 * Function Name: loop
 * Input: i, enA, in_1, in_2, enB, in_3, in_4
 * Output: Rotates the DC motor according to the required application and communicates with the Pi to detect the Aruco ussing PiCam
 * Logic: Function digitalWrite() is used to control the motors and character "S" is sent as a cue for the PiCam to detect Aruco
 */ 


void loop()

{

//moving from start to central node  

digitalWrite(in_1,HIGH) ;
digitalWrite(in_2,LOW) ;
analogWrite(enA,240) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,HIGH) ;
analogWrite(enB,255) ;

delay(3300) ;

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
  
  Serial.write("S");           //The arduino sends out signal "S" to the Pi communicating that it is ready in the right orientaion ( Cue to the PiCam to capture and detect Aruco)
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


delay(1000000);

}
