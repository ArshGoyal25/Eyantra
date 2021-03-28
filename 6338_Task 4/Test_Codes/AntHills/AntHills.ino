#include<stdlib.h>
#include"line.h"

void setup()
{
  Serial.begin(9600);
  pinMode(enA,OUTPUT) ;   
  pinMode(in_1,OUTPUT) ;  
  pinMode(in_2,OUTPUT) ;
  pinMode(enB,OUTPUT) ;   
  pinMode(in_3,OUTPUT) ; 
  pinMode(in_4,OUTPUT) ;
  
}

//work(
//AH=[Q,1,g,t]
//if AH.ser_1=="
//work(0,-1)

//AH=[[1,2,3,4],[2,3,4,5],[3,4,5,6],[4,5,6,7]]
void Queen()
{
  int i;
  int check=-1;
  for(i=0;i<4;i++)
  {
    if (AH[i].type=="Q")
    {
      work(AH[i].number,AH[i].ser_1,AH[i].ser_2)
      check=i;
    }
  }
  for(i=0;i<4;i++)
  {
    if(check!=i)
    {
      work(AH[i].number,AH[i].ser_1,AH[i].ser_2)
    }  
  }
}
////////////////////////////////////////////////////////////////////////////////////////
void work(int b,int c,int d)
{
  if (c==0 || d==0)
  {
    if (c==0 && d==-1 || d==0 && c==-1)
    {
        u_turn();
        AntHills(b);
        if (c==0 && d==-1)
          Trash_removal(2);
        else if (d==0 && c==-1)
          Trash_removal(1);
        r_AntHills(b,0);
    }
    else 
    {
      if(c!=0)
      {
        shrub_select(c);
        AntHills(b);
        Supply_req(1);
        r_AntHills(b,1);
      }
      else if (d!=0)
      {
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
    if (c==-1 && d!=-1)
    {
      shrub_select(d);
      AntHills(b);
      Supply_req(2);
      lineSensor();
      u_turn();
      lineSensor();
      Trash_removal(1);
      r_AntHills(b,0);
      
    }
    else if (c!=-1 && d==-1)
    {
      shrub_select(c);
      AntHills(b);
      Supply_req(1);
      lineSensor();
      u_turn();
      lineSensor();
      Trash_removal(2);
      r_AntHills(b,0);
    } 
  return;
  }

  else
  {
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
}
////////////////////////////////////////////////////////////////////////////////////////
void Trash_removal(int a)
{
  if (a==1)
  {
    left_turn();
    r_lineSensor();
    Servo_pickup();
    left_turn();
  }
  else if (a==2)
  {
    right_turn();
    r_lineSensor();
    Servo_pickup();
    right_turn();
  }
}
////////////////////////////////////////////////////////////////////////////////////////
void Supply_req(int a)
{
  if (a==1)
  {
    left_turn();
    r_lineSensor();
    Servo_drop();
    left_turn();
  }
  else if (a==2)
  {
    right_turn();
    r_lineSensor();
    Servo_drop();
    right_turn();
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////
void TDZ()
{
  int count=0;
  lineSensor();
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
  lineSensor();
  lineSensor();
  count++;
}
//////////////////////////////////////////////////////////////////////////
void AntHills(int a)
{
  lineSensor();
  if(a=="UL")
  {
    left_turn();
    lineSensor();
    right_turn();
    lineSensor();
    stop_motion();    
  }    
  else if(a=="UR")
  {
    right_turn();
    lineSensor();
    left_turn();
    lineSensor();
    stop_motion();
  }  
  else if(a=="LR")
  {
    right_turn();
    lineSensor();
    right_turn();
    lineSensor();
    stop_motion();
  }  
  else if(a=="LL")
  {
    left_turn();
    lineSensor();
    left_turn();
    lineSensor();
    stop_motion();
  }
}
//////////////////////////////////////////////////////////////////////////
void r_AntHills(int a,int b)
{
  lineSensor();
  if(a=="UL" || a=="LR")
     left_turn(); 
  else if(a=="UR" || a=="LL")
    right_turn();
  lineSensor();
  stop_motion();
  if(b==1)
  {
      if (a=="UL" || a=="LL")
         right_turn();
      else if (a=="UR" || a=="LR")
         left_turn();
      lineSensor();
   }
   else if (b==0)
   {
      if (a=="UL" || a=="LL")
        left_turn();
      else if (a=="UR" || a=="UL")
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
        right_turn();
        for(i=1;i<=(4-b);i++)
          lineSensor();
        r_pickup();
        for(i=1;i<=(4-b);i++)
          lineSensor();
        left_turn();
     }   
  else if (a==1)
      {
        left_turn();
        for(i=1;i<=(b-3);i++)
          lineSensor();
        l_pickup();
        for(i=1;i<=(b-3);i++)
          lineSensor();
        right_turn();
      }
}
///////////////////////////////////////////////////////////////
void r_pickup()
{
  left_turn();
  r_lineSensor();
  flil();
  r_lineSensor();
  Servo_pickup();
  left_turn();
}
///////////////////////////////////////////////////////////////
void l_pickup()
{
  right_turn();
  r_lineSensor();
  flil();
  r_lineSensor();
  Servo_pickup();
  right_turn();
}
//////////////////////////////////////////////////////////////

void Servo_pickup()
{
  
}
//////////////////////////////////////////////////////////////////////
void Servo_drop()
{
  
}
 

void loop()
{/*
  lineSensor();
  stop_motion();
  delay(2000);
  right_turn();
  stop_motion();
  delay(2000);
  rlil();
  stop_motion();
  delay(2000);
  right_turn();
  lineSensor();
  stop_motion();
  delay(10000);
  */
 }
