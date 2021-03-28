void Aruco_Motion()
{
  //lineSensor();
  //lineSensor();
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

  //stopping the robot at the right orientation, ready to detect Aruco 
  
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,LOW) ;
  analogWrite(enA,0) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,LOW) ;
  analogWrite(enB,0) ;
  
  delay(2000);
  
  //The robot sequentially rotates to all the Arucos and detects them one by one through the for loop
  char n; 
  while(1)
  {
    Serial.write("S"); 
    Serial.flush();//The arduino sends out signal "S" to the Pi communicating that it is ready in the right orientaion ( Cue to the PiCam to capture and detect Aruco)
    n= Serial.read();
    Serial.flush();
    if(n=='E')
      {
       Serial.println("Done");
       digitalWrite(in_1,LOW) ;
       digitalWrite(in_2,HIGH) ;
       analogWrite(enA,255) ;
  
       digitalWrite(in_3,HIGH) ;
       digitalWrite(in_4,LOW) ;
       analogWrite(enB,255) ;
       delay(317) ;  
       //lineSensor();
       break;
      }
    else if ( n=='0' | n=='1' |n=='2' |n=='3')
      {
        Serial.println("Next");
        digitalWrite(in_1,HIGH) ;   //Rotating towards the next Aruco
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
