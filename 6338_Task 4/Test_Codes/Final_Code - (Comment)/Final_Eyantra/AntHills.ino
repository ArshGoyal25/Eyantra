
////////////////////////////////////////////////////////////////////
struct Anthill
{
  char type;
  char no;
  char ser_1;
  char ser_2;
  char loc[2];
}AH[4];

////////////////////////////////////////////////////////////////////
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
     ///////////////////////////////////////////////////////  
     Serial.println("Enter the anthill type");
     while(1) 
     {
        ch = Serial.read();      
        if (ch=='Q' || ch =='R')
          {
            AH[i].type= ch;
            break;
          }
     }
     Serial.print("\n");
     Serial.flush();
     /////////////////////////////////////////////////////////////
     Serial.println("Enter the anthill number");       
     while (1)
     {
        ch = Serial.read();        
        if (ch=='0'||ch=='1' || ch=='2' || ch=='3')
          {
            AH[i].no= ch;
            break;
          }
     } 
     Serial.print("\n");
     Serial.flush();
     //////////////////////////////////////////////////////////////////////////
     Serial.println("Enter the requirement for service location 1\n");
     while(1)
     {
        ch = Serial.read();
        if (ch=='R' || ch =='B'|| ch=='G'||ch=='N'||ch=='T')
          {
            AH[i].ser_1= ch;
            break;
          }
     }
     Serial.print("\n");
     Serial.flush();
     /////////////////////////////////////////////////////////////////////////
     Serial.println("Enter the requirement for service location 2\n");    
     while(1)
     {
        ch = Serial.read();
        if (ch=='R' || ch =='B'|| ch=='G'||ch=='N'||ch=='T')
          {
            AH[i].ser_2= ch;
            break;
          }
     }
     Serial.print("\n");
     Serial.flush();
  }
     ////////////////////////////////////////////////////////////////////
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
/*
['Q',0,'B','G']
['R',1,'R','N']
['R',2,'T','R']
['R',3,'B','T']*/

//char col_arr[6]={'B','R','B','G','R','G'};
/*
["UL",1,4]
["UR",2,0]
["LR",-1,-1]
["LL",3,-1]
*/
////////////////////////////////////////////////////////////////////////////////
void work(char,int,int);

///////////////////////////////////////////////////////////////////////////////////////////
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
//////////////////////////////////////////////////////////////////////////////////////////
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
  buzz();
}

////////////////////////////////////////////////////////////////////////////////////////
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
        r_AntHills(b,1);
      }
      else if (d!=0)
      {
        Serial.println("Service only for d");
        shrub_select(d);
        AntHills(b);
        Supply_req(2);
        r_AntHills(b,1);
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
       r_AntHills(b,0);
    }
    if (c==-1 && d!=-1)
    {
      Serial.println("Service D Trash C");
      shrub_select(d);
      AntHills(b);
      Supply_req(2);
      //lineSensor();
      u_turn();
      //lineSensor();
      Trash_removal(1);
      r_AntHills(b,0);
      
    }
    else if (c!=-1 && d==-1)
    {
      Serial.println("Service C Trash D");
      shrub_select(c);
      AntHills(b);
      Supply_req(1);
      //lineSensor();
      u_turn();
      //lineSensor();
      Trash_removal(2);
      r_AntHills(b,0);
    } 
  return;
  }

  else
  {
    Serial.println("Service both");
    shrub_select(c);
    AntHills(b);
    Supply_req(1);
    r_AntHills(b,1);
    shrub_select(d);
    AntHills(b);
    Supply_req(2);
    r_AntHills(b,1);
    return;
  }
  Serial.println("DONE");
}
////////////////////////////////////////////////////////////////////////////////////////
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
      //r_lineSensor();
      Servo_pickup();
      left_turn();
      Serial.println("TR for S1");
      
    }
    else 
    {
      //r_lineSensor();
      u_turn();
      //r_lineSensor();
      Servo_pickup();
      right_turn();
      Serial.println("TR for S2");
      
    }
}
/////////////////////////////////////////////////////////////////////////////////////
void Trash_removal(int a)
{
  if (a==1)
  {
    left_turn();
    //r_lineSensor();
    Servo_pickup();
    left_turn();
    Serial.println("TR for S1");
  }
  else if (a==2)
  {
    right_turn();
    //r_lineSensor();
    Servo_pickup();
    right_turn();
    Serial.println("TR for S2");
  }
}
////////////////////////////////////////////////////////////////////////////////////////
void Supply_req(int a)
{
  if (a==1)
  {
    left_turn();
    //r_lineSensor();
    Servo_drop();
    left_turn();
    Serial.println("SR for S1");
  }
  else if (a==2)
  {
    right_turn();
    //r_lineSensor();
    Servo_drop();
    right_turn();
    Serial.println("SR for S2");
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////
void TDZ()
{
  int count=0;
  //lineSensor();
  if(count==0)
  {
    //left45
    Servo_drop();
  }
  else
  {
    //right45
    Servo_drop();
  }    
  u_turn();
  //lineSensor();
  //lineSensor();
  Serial.println("TDZ and start");
  count++;
}
//////////////////////////////////////////////////////////////////////////
void AntHills(char a[2])
{
  //lineSensor();
  if(a[0]=='U' and a[1]=='L')
  {
    left_turn();
    //lineSensor();
    right_turn();
    //lineSensor();
    stop_motion();
    Serial.println("Go to UL")  ;  
  }    
  if(a[0]=='U' and a[1]=='R')
  {
    right_turn();
    //lineSensor();
    left_turn();
    //lineSensor();
    stop_motion();
    Serial.println("Go to UR");
  }  
  if(a[0]=='L' and a[1]=='R')
  {
    right_turn();
    //lineSensor();
    right_turn();
    //lineSensor();
    stop_motion();
    Serial.println("Go to LR");
  }  
  if(a[0]=='L' and a[1]=='L')
  {
    left_turn();
    //lineSensor();
    left_turn();
    //lineSensor();
    stop_motion();
    Serial.println("Go to LL");
  }
}
//////////////////////////////////////////////////////////////////////////
void r_AntHills(char a[2],int b)
{
  //lineSensor();
  if(a[0]=='U' and a[1]=='L' || a[0]=='L' and a[1]=='R')
     left_turn(); 
  else if(a[0]=='U' and a[1]=='R' || a[0]=='L' and a[1]=='L')
    right_turn();
  //lineSensor();
  stop_motion();
  if(b==1)
  {
      Serial.println("No Trash. Going to start");
      if (a[0]=='U' and a[1]=='L'|| a[0]=='L' and a[1]=='L')
         right_turn();
      else if (a[0]=='U' and a[1]=='R'||a[0]=='L' and a[1]=='R')
         left_turn();
      //lineSensor();
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
/////////////////////////////////////////////////////////////////
void shrub_select(int b)
{
  int i;
  int a;
  if(b==1 ||b==2 || b==3)
    a=0;
  else
    a=1;
  if (a==0)
    {
        Serial.println("Shrub picked from S123 side  --");
        Serial.println(b);
        right_turn();
        for(i=1;i<=(4-b);i++)
        //  lineSensor();
        r_pickup();
        for(i=1;i<=(4-b);i++)
          //lineSensor();
        left_turn();
     }   
  else if (a==1)
      {
        Serial.println("Shrub picked from S456 side  --");
        Serial.println(b);
        left_turn();
        for(i=1;i<=(b-3);i++)
          //lineSensor();
        l_pickup();
        for(i=1;i<=(b-3);i++)
          //lineSensor();
        right_turn();
      }
}
///////////////////////////////////////////////////////////////
void r_pickup()
{
  left_turn();
  //r_lineSensor();
  Servo_pickup();
  left_turn();
}
///////////////////////////////////////////////////////////////
void l_pickup()
{
  right_turn();
  //r_lineSensor();
  Servo_pickup();
  right_turn();
}
//////////////////////////////////////////////////////////////

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
//////////////////////////////////////////////////////////////////////
void Servo_drop()
{
  stservo.write(100);
  delay(1000);
  micservo.write(0);
  delay(1000);
  stservo.write(0);
}
/////////////////////////////////////////////////////////////////////////
void buzz() 
{
  digitalWrite(Buzzer, HIGH);
  delay(5000);
  digitalWrite(Buzzer, LOW);  
}
