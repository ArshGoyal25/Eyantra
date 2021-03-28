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
/////////////////////////////////////////////////////////////////////////
void start_colour()
{
  right_turn();
  stop_motion();
  r_lineSensor();
  stop_motion();
  lineSensor();
  lineSensor();
  lineSensor();
  left_turn();
  stop_motion();
  communication();
  r_lineSensor();
}
/////////////////////////////////////////////////////////////////////////
void server_motion()
{ 
  int j=1;
  while (j<6)
  {
  lineSensor();
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
     //lineSensor();
    }
  right_turn();
  communication();
  r_lineSensor();
  stop_motion();
  //delay(3000);
  j++;
  }
}
////////////////////////////////////////////////////////////////////////
void end_colour()
{
  //lineSensor();
  right_turn();
  lineSensor();
  lineSensor();
  lineSensor();
  left_turn();
  r_lineSensor();
  stop_motion();
}
////////////////////////////////////////////////////////////////////////

void Service_Motion()
{
  start_colour();
  server_motion();
  
  end_colour();
  return;
}
