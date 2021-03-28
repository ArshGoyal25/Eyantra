/*
 * Team Id: #6338
 * Author List: Arsh Goyal, Arnav Agarwal, Sujith K
 * Filename: ArUco_Detect
 * Theme: Ant Bot
 * Functions: Aruco_Motion
 * Global Variables: all global variables are declared in the header file line.h
*/

/*
 * Function Name: Aruco_Motion
 * Input: none
 * Output: none
 * Logic: This function is used to move the robot from the start position to the central node and then make it rotate appropriately so as to detect all the 4 ArUco markers using the PiCam.
 * After detecting the 4 ArUco markers, the robot will turn around and go to the Shrubs Area to detect the supply requirements.
 * Example Call: Aruco_Motion()
 */
void Aruco_Motion()
{
  lineSensor();
  lineSensor();

  // After stopping at the central node, the robot will move forwards a bit and then turn left by 45 degrees so as to orient properly to detect the ArUco marker
  
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  analogWrite(enA,255) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(enB,255) ;
  delay(200) ; 
  
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  analogWrite(enA,255) ;
  
  digitalWrite(in_3,HIGH) ;
  digitalWrite(in_4,LOW) ;
  analogWrite(enB,255) ;
  delay(317) ; 

  //stopping the robot at the right orientation, ready to detect ArUco marker
  
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,LOW) ;
  analogWrite(enA,0) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,LOW) ;
  analogWrite(enB,0) ;
  
  delay(2000);
  
  //The robot sequentially rotates to all the Arucos and detects them one by one through the while loop
  char n;
  while(1)
  {
    Serial.write("S");    //The arduino sends out signal "S" to the Pi communicating that it is ready in the right orientaion (Cue to the PiCam to capture and detect Aruco)
    Serial.flush();
    n=Serial.read();
    Serial.flush();
    if(n=='E')
      {
       digitalWrite(in_1,LOW) ;
       digitalWrite(in_2,HIGH) ;
       analogWrite(enA,255) ;
  
       digitalWrite(in_3,HIGH) ;
       digitalWrite(in_4,LOW) ;
       analogWrite(enB,255) ;
       delay(450) ;  
       lineSensor();
       break;
      }
      else if(n=='1'|n=='2'|n=='3')
      {
        digitalWrite(in_1,HIGH) ;   //Rotating towards the next ArUco
        digitalWrite(in_2,LOW) ;
        analogWrite(enA,255) ;
  
        digitalWrite(in_3,LOW) ;
        digitalWrite(in_4,HIGH) ;
        analogWrite(enB,255) ;
  
        delay(635) ; 
  
        digitalWrite(in_1,LOW) ;  //Stopping again once the right orientation is reached
        digitalWrite(in_2,LOW) ;
        analogWrite(enA,180) ;
  
        digitalWrite(in_3,LOW) ;
        digitalWrite(in_4,LOW) ;
        analogWrite(enB,180) ;
        delay(500);
      }
     
    delay(300);
    Serial.flush();
  }
} 
