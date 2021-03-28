/*
 * Team Id: #6338
 * Author List: Arsh Goyal, Arnav Agarwal, Sujith K
 * Filename: AntHills
 * Theme: Ant Bot
 * Functions: get_det, work, Queen, Only_trash_removal, Trash_removal, Supply_req, TDZ, AntHills, r_AntHills, shrub_select, r_pickup, l_pickup, Servo_pickup, Servo_drop, buzz
 * Global Variables: all global variables are declared in the header file line.h
*/
struct Anthill
{
  char type;
  char no;
  char ser_1;
  char ser_2;
  char loc[2];
}AH[4];
/*
 * Function Name: get_det
 * Input: none
 * Output: none
 * Logic: This function is used to get the information about the ant hills from the class made in the python file and printing it on the serial monitor.
 * Example Call: get_det()
 */
void get_det()
{  
  int i=0;
  char ch;
  for(i=0;i<4;i++)
  {
     Serial.print("\n");
     if(i==0)
     {
       Serial.println("UL");
       AH[i].loc[0]='U';
       AH[i].loc[1]='L';
     }
     else if(i==1)
     {
       Serial.println("UR");
       AH[i].loc[0]='U';
       AH[i].loc[1]='R';
     }
     else if(i==2)
     {
       Serial.println("LR");
       AH[i].loc[0]='L';
       AH[i].loc[1]='R';
     }
     else if(i==3)
     {
       Serial.println("LL");
       AH[i].loc[0]='L';
       AH[i].loc[1]='L';
     }
     Serial.println("Enter the anthill type");
     while(1) 
     {
        ch = Serial.read();      
        if (int(ch)>=65 && int(ch) <=122)
          {
            AH[i].type= ch;
            break;
          }
     }
     Serial.print("\n");
     Serial.flush();
     Serial.println("Enter the anthill number");       
     while (1)
     {
        ch = Serial.read();        
        if (int(ch)>=48 && int(ch) <58)
          {
            AH[i].no= ch;
            break;
          }
     } 
     Serial.print("\n");
     Serial.flush();
     Serial.println("Enter the requirement for service location 1\n");
     while(1)
     {
        ch = Serial.read();
        if (int(ch)>=65 && int(ch) <=122)
          {
            AH[i].ser_1= ch;
            break;
          }
     }
     Serial.print("\n");
     Serial.flush();
     Serial.println("Enter the requirement for service location 2\n");    
     while(1)
     {
        ch = Serial.read();
        if (int(ch)>=65 && int(ch) <=122)
          {
            AH[i].ser_2= ch;
            break;
          }
     }
     Serial.print("\n");
     Serial.flush();
  }
  for(i=0;i<4;i++)
  {
     Serial.print(AH[i].type);
     Serial.print("\t");
     Serial.print(AH[i].no);
     Serial.print("\t");
     Serial.print(AH[i].ser_1);
     Serial.print("\t");
     Serial.print(AH[i].ser_2);
     Serial.print("\n");
   }
     return;
}

void work(char,int,int); // function definition 
int check_pos(char a)
{
  int j=0;
  int arg;
  if(a=='N')
        arg=0;
  else if(a=='T')
        arg=-1;
  else
  {  
    for(j=0;j<=5;j++)
       if(col_arr[j]==a)
       {
          arg=j+1;
          col_arr[j]='D';
          break;
       }
  }
  return(arg);
}
/*
 * Function Name: Queen
 * Input: none
 * Output: none
 * Logic: This function is used to make the robot complete the service requirements of the queen ant hill first.
 * Example Call: Queen()
 */
void Queen()
{
  Serial.println("In Queen");
  int i=0;
  int j=0 ;
  int arg_1=0;
  int arg_2=0;
  int check=-1;
  for(i=0;i<4;i++)
  {
    Serial.println("hi");
    if (AH[i].type=='Q')
    {
      Serial.println("Queen detected at");
      Serial.println(i);
      arg_1=check_pos(AH[i].ser_1);
      arg_2=check_pos(AH[i].ser_2);
      Serial.println("Queen service starts");
      Serial.println(arg_1);
      Serial.println(arg_2);
      work(AH[i].loc,arg_1,arg_2);
      check=i;
      break;
    }
  }
  for(i=0;i<4;i++)
  {    
    if(check!=i)
    {
      Serial.println("Start service for AH --");
      Serial.println(i);
      arg_1=check_pos(AH[i].ser_1);
      arg_2=check_pos(AH[i].ser_2);
      Serial.println(arg_1);
      Serial.println(arg_2);
      work(AH[i].loc,arg_1,arg_2);
    }  
  }
  u_turn();
  buzz();
  delay(100000);
}

/*
 * Function Name: work
 * Input: none
 * Output: none
 * Logic: This function is used to check the supply requirements of the ant hill and call the functions which are needed to complete its service. 
 * It takes into account the various possibilities (Eg: No supply, Trash; Supply, Supply; etc) 
 * These are checked by assigning two local variables inside the function. 
 * The value of the variable tells us the kind of requirement for both the service locations of the ant hill as explained below:
 * 0 is for No supply required
 * 1,2,3,4,5,6 is for Location of supply required
 * -1 is for trash
 * Example Call: work('UL',1,0)
 */
void work(char b[2],int c,int d)
{
  if (c==0 || d==0)
  {
    if(c==0 && d==0)
       Serial.println("No Service");
    else 
    {
      if(c!=0)
      {
        Serial.println("Service only for c");
        shrub_select(c);
        AntHills(b);
        Supply_req(1);
        reverse_AntHills(b,1);
      }
      else if (d!=0)
      {
        Serial.println("Service only for d");
        shrub_select(d);
        AntHills(b);
        Supply_req(2);
        reverse_AntHills(b,1);
      }
     }
   return;
   }

   
   else if (c==-1 || d==-1)
   {
    if (c==-1 && d==-1)
    {
       Serial.println("Trash Service Only");
       u_turn();
       AntHills(b);
       Only_trash_removal();
       reverse_AntHills(b,0);
    }
    if (c==-1 && d!=-1)
    {
      Serial.println("Service D Trash C");
      shrub_select(d);
      AntHills(b);
      Supply_req(2);
      lineSensor();
      u_turn();
      lineSensor();
      Trash_removal(1);
      reverse_AntHills(b,0);
      
    }
    else if (c!=-1 && d==-1)
    {
      Serial.println("Service C Trash D");
      shrub_select(c);
      AntHills(b);
      Supply_req(1);
      lineSensor();
      u_turn();
      lineSensor();
      Trash_removal(2);
      reverse_AntHills(b,0);
    } 
  return;
  }

  else
  {
    Serial.println("Service both");
    shrub_select(c);
    AntHills(b);
    Supply_req(1);
    reverse_AntHills(b,1);
    shrub_select(d);
    AntHills(b);
    Supply_req(2);
    reverse_AntHills(b,1);
    return;
  }
  Serial.println("DONE");
}

/*
 * Function Name: Only_trash_removal
 * Input: none
 * Output: none
 * Logic: This function is used when the ant hill has only trash as its service requirement ie, when one service location has trash removal while the other has no supply.
 * In this case, the robot will check both the service locations for the trash block before picking it up and moving towards TDZ for the trash deposition.
 * Example Call: Only_trash_removal()
 */
void Only_trash_removal()
{
    char u;
    left_turn();
    Serial.write("Detect");
    while(1)
    {
      Serial.flush();
      u=Serial.read();
      if (u=='N' || u=='Y')
        break;
    }    
    if (u=='Y') 
    {
      reverse_lineSensor();
      Servo_pickup();
      left_turn();
      Serial.println("TR for S1");
       
    }
    else 
    {
      reverse_lineSensor();
      u_turn();
      reverse_lineSensor();
      Servo_pickup();
      right_turn();
      Serial.println("TR for S2");
      
    }
}
/*
 * Function Name: trash_removal
 * Input: none
 * Output: none
 * Logic: This function is used to remove the trash from the ant hill. The variable 'a' is used to distinguish between the two service locations and the turnings are given to the robot accordingly.
 * Example Call: trash_removal(1)
 */
void Trash_removal(int a)
{
  if (a==1) // when trash is at service 1
  {
    left_turn();
    reverse_lineSensor();
    Servo_pickup();
    rgb('Y');
    left_turn();
    Serial.println("TR for Serv1");
  }
  else if (a==2) // when trash is at service 2
  {
    right_turn();
    reverse_lineSensor();
    Servo_pickup();
    rgb('Y');
    right_turn();
    Serial.println("TR for Serv2");
  }
}
/*
 * Function Name: Supply_req
 * Input: none
 * Output: none
 * Logic: This function is used to place the supply blocks at the service locations of the ant hills
 * Example Call: Supply_req(2)
 */
void Supply_req(int a)
{
  if (a==1)
  {
    left_turn();
    reverse_lineSensor();
    Servo_drop();
    left_turn();
    Serial.println("SR for S1");
  }
  else if (a==2)
  {
    right_turn();
    reverse_lineSensor();
    Servo_drop();
    right_turn();
    Serial.println("SR for S2");
  }
}
/*
 * Function Name: TDZ
 * Input: none
 * Output: none
 * Logic: This function is used to place the trash in the TDZ. The robot turns left for the first time it enters TDZ and then turns right for the second time to aviod stacking of the trash blocks.
 * The robot returns to the start position after depositing the trash.
 * Example Call: TDZ()
 */
void TDZ()
{
  int count=0;
  lineSensor();
  if(count==0)
  {
    left45();
    Servo_drop();
    right45();
  }
  else
  {
    right45();
    Servo_drop();
    left45();
  }    
  u_turn();
  lineSensor();
  lineSensor();
  Serial.println("TDZ and start");
  count++;
}
/*
 * Function Name: AntHills
 * Input: character
 * Output: none
 * Logic: This function is used to move the robot to the required anthill depending on its position
 * Example Call: AntHills('LR')
 */
void AntHills(char a[2])
{
  //lineSensor();
  if(a[0]=='U' and a[1]=='L')
  {
    left_turn();
    lineSensor();
    right_turn();
    lineSensor();
    stop_motion();
    Serial.println("Go to UL")  ;  
  }    
  if(a[0]=='U' and a[1]=='R')
  {
    right_turn();
    lineSensor();
    left_turn();
    lineSensor();
    stop_motion();
    Serial.println("Go to UR");
  }  
  if(a[0]=='L' and a[1]=='R')
  {
    right_turn();
    lineSensor();
    right_turn();
    lineSensor();
    stop_motion();
    Serial.println("Go to LR");
  }  
  if(a[0]=='L' and a[1]=='L')
  {
    left_turn();
    lineSensor();
    left_turn();
    lineSensor();
    stop_motion();
    Serial.println("Go to LL");
  }
}
/*
 * Function Name: reverse_AntHills
 * Input: none
 * Output: none
 * Logic: This function is used to tell the robot where the required supply block is placed and how it should traverse to get to the block
 * It also calls the servo_pickup function which makes the arm pick up the block.
 * Example Call: reverse_AntHills()
 */
void reverse_AntHills(char a[2],int b)
{
  lineSensor();
  if(a[0]=='U' and a[1]=='L' || a[0]=='L' and a[1]=='R')
     left_turn(); 
  else if(a[0]=='U' and a[1]=='R' || a[0]=='L' and a[1]=='L')
    right_turn();
  lineSensor();
  stop_motion();
  if(b==1)
  {
      Serial.println("No Trash. Going to start");
      if (a[0]=='U' and a[1]=='L'|| a[0]=='L' and a[1]=='L')
         right_turn(); 
      else if (a[0]=='U' and a[1]=='R'||a[0]=='L' and a[1]=='R')
         left_turn();
      lineSensor();
   }
   else if (b==0)
   {
      Serial.println("Code called for TDZ");
      if ( a[0]=='U' and a[1]=='L'|| a[0]=='L' and a[1]=='L')
        left_turn();
      else if (a[0]=='U' and a[1]=='R'|| a[0]=='L' and a[1]=='R')
        right_turn();
      TDZ();
   }   
}
/*
 * Function Name: shrub_select
 * Input: none
 * Output: none
 * Logic: This function is used to tell the robot where the required supply block is placed and how it should traverse to get to the block
 * It also calls the servo_pickup function which makes the arm pick up the block.
 * Example Call: shrub_select()
 */
void shrub_select(int supply_location)
{
  int i;
  char a[10];
  if(supply_location==1 || supply_location==2 || supply_location==3) // if the robot has to go to S1 or S2 or S3, it has to take a right turn
    a="right";
  else
    a="left";
  if (a=="right")
    {
        Serial.println("Shrub picked from S123 side  --");
        Serial.println(supply_location);
        right_turn();
        for(i=1;i<=(4-supply_location);i++) 
          lineSensor();
        r_pickup();
        for(i=1;i<=(4-supply_location);i++)
          lineSensor();
        left_turn();
     }   
  else if (a=="left") // if the robot has to go to S4 or S5 or S6, it has to take a left turn
      {
        Serial.println("Shrub picked from S456 side  --");
        Serial.println(supply_location);
        left_turn();
        for(i=1;i<=(supply_location-3);i++)
          lineSensor();
        l_pickup();
        for(i=1;i<=(supply_location-3);i++)
          lineSensor();
        right_turn();
      }
}
/*
 * Function Name: left45
 * Input: none
 * Output: none
 * Logic: This function is used to make the robot tilt a little towards the left
 * Example Call: left45()
 */
void left45()
{
    digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  analogWrite(enA,255) ;
  
  digitalWrite(in_3,HIGH) ;
  digitalWrite(in_4,LOW) ;
  analogWrite(enB,255) ;  
  delay(220);
}
/*
 * Function Name: right45
 * Input: none
 * Output: none
 * Logic: This function is used to make the robot tilt a little towards the right
 * Example Call: right45()
 */
void right45()
{
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,LOW) ;
  analogWrite(enA,255) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(enB,255) ;
  delay(220);
}
/*
 * Function Name: r_pickup
 * Input: none
 * Output: none
 * Logic: This function is used to pick up the block from S1 or S2 or S3 using the robotic arm which uses one standard servo and one micro servo motor.
 * Example Call: r_pickup()
 */
void r_pickup()
{
  left_turn();
  reverse_lineSensor();
  Servo_pickup();
  left_turn();
}
/*
 * Function Name: l_pickup
 * Input: none
 * Output: none
 * Logic: This function is used to pick up the block from S4 or S5 or S6 using the robotic arm which uses one standard servo and one micro servo motor.
 * Example Call: l_pickup()
 */
void l_pickup()
{
  right_turn();
  reverse_lineSensor();
  Servo_pickup();
  right_turn();
}
/*
 * Function Name: Servo_pickup
 * Input: none
 * Output: none
 * Logic: This function is used to pick up the block from the arena using the robotic arm which uses one standard servo and one micro servo motor.
 * Example Call: Servo_pickup()
 */
void Servo_pickup()
{
  stservo.write(0);
  micservo.write(0);
  stservo.write(100);
  delay(1000);
  micservo.write(70);
  delay(1000);
  stservo.write(0);
}
/*
 * Function Name: Servo_drop
 * Input: none
 * Output: none
 * Logic: This function is used to drop the block onto the service location or the Trash Deposition Zone using the robotic arm which uses one standard servo and one micro servo motor.
 * Example Call: Servo_drop()
 */
void Servo_drop()
{
  stservo.write(100);
  delay(1000);
  micservo.write(0);
  delay(1000);
  stservo.write(0);
}
/*
 * Function Name: buzz
 * Input: none
 * Output: none
 * Logic: This function is used to turn on the buzzer for 5 seconds to denote the task is complete
 * Example Call: buzz()
 */
void buzz() 
{
  digitalWrite(Buzzer, HIGH); // the buzzer will turn on for 5 seconds and then turn off when this function is called
  delay(5000);
  digitalWrite(Buzzer, LOW);  
}
