/*
 * Team Id: #6338
 * Author List: Arsh Goyal, Arnav Agarwal, Sujith K
 * Filename: Colour_Detect
 * Theme: Ant Bot
 * Functions: communication, start_colour, server_motion, end_colour, Service_Motion
 * Global Variables: all global variables are declared in the header file line.h
*/


/*
 * Function Name: communication
 * Input: none
 * Output: none
 * Logic: This function is used to get the position and colour of the six blocks placed in Shrubs Area and store them in the col_arr[6] array
 * Example Call: communication()
 */
void communication()
{ 
  char check;
  Serial.write("C");   
  while(1)
  {    
    Serial.flush();
    check= Serial.read();
    if(check=='R' || check=='G' || check=='B' )
    {
      col_arr[s]=check;
      rgb(check);
      s++;
      return;
    }
  }
}
/*
 * Function Name: start_colour()
 * Input: none
 * Output: none
 * Logic: This function is used to make the robot traverse the Shrubs Area for the first time to scan all the blocks and save their respective positions and colours.
 * The robot returns from the central node after detecting the ArUco markers and reaches the node in front of S1.
 * Example Call: start_colour()
 */
void start_colour()
{
  right_turn(); // robot turns right 
  stop_motion(); // robot stops moving for a small amount of time
  reverse_lineSensor(); // robot moves backwards while following the line until it detects the node
  stop_motion(); // robot stops moving for a small amount of time
  lineSensor(); // robot moves forward while following the line
  lineSensor(); // robot moves forward while following the line
  lineSensor(); // robot moves forward while following the line
  left_turn(); // robot turns left
  stop_motion(); // robot moves backwards while following the line until it detects the node
  communication(); // robot checks the colour of the block which is detected using PiCam and stores it in the col_arr[6] array
  reverse_lineSensor(); // robot moves backwards while following the line until it detects the node
}
/*
 * Function Name: server_motion()
 * Input: none
 * Output: none
 * Logic: This function is used to make the robot traverse the Shrubs Area for the first time to scan all the blocks and save their respective positions and colours.
 * The robot starts scanning each block starting from S1 uptil S6.
 * Example Call: server_motion()
 */
void server_motion()
{ 
  int j=1;
  while (j<6)
  {
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
  communication();
  reverse_lineSensor();
  stop_motion();
  delay(3000);
  j++;
  }
}
/*
 * Function Name: end_colour()
 * Input: none
 * Output: none
 * Logic: This function is used to make the robot return to the start node after scanning all the blocks in the Shrubs Area.
 * Example Call: end_colour()
 */
void end_colour()
{
  right_turn(); // robot turns right
  reverse_lineSensor(); // robot moves backwards while following the line until it detects the node 
  lineSensor(); // robot moves forward while following the line
  lineSensor(); // robot moves forward while following the line
  lineSensor(); // robot moves forward while following the line
  left_turn(); // robot turns left
  reverse_lineSensor(); // robot moves backwards while following the line until it detects the node
  stop_motion(); // robot stops moving for some time
} 
/*
 * Function Name: Service_Motion()
 * Input: none
 * Output: none
 * Logic: This function is used to call the functions start_colour, server_motion, end_colour in sequence for the correct execution of detecting the supply requirements
 * Example Call: Service_Motion()
 */
void Service_Motion()
{
  start_colour(); 
  server_motion();
  end_colour();
}
