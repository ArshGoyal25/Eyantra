
int analogPin1 = 4;  
int analogPin2 = 1;
int analogPin3 = 2;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int value = 0;
int enA = 3 ; 
int in_1 = 8 ; 
int in_2 = 9 ;
int enB = 5 ; 
int in_3 = 6 ;
int in_4 = 7 ;
int i;
int n=0;
int a;
int j;

////////////////////////////////////////////////////////////////
void endlines()
{
  while(1)
{
  value1 = analogRead(analogPin1);     // read the input pin
  value2 = analogRead(analogPin2);     // read the input pin
  value3 = analogRead(analogPin3);     // read the input pin
  value = (value1+value2+value3)/3;
/*Serial.print(value1); 
  Serial.print("\t"); 
  Serial.print(value2); 
  Serial.print("\t");  
  Serial.print(value3); 
  
  Serial.print("\n");*/
  int avg=((value1+value2+value3)/3); 
if(value1>810 && value2>810 || value2>810 && value3>810)
{
     digitalWrite(in_1,LOW) ;
     digitalWrite(in_2,LOW) ;
     analogWrite(enA,110) ;

     digitalWrite(in_3,LOW) ; 
     digitalWrite(in_4,LOW) ; 
     analogWrite(enB,110) ; 
    
     delay(1000);
     

    /*
     digitalWrite(in_1,HIGH) ;
     digitalWrite(in_2,LOW) ;
     analogWrite(enA,110) ;

     digitalWrite(in_3,HIGH) ;
     digitalWrite(in_4,LOW) ;
     analogWrite(enB,110) ;
     */
    
     delay(200);
     return;    
}
else 
{
   if(value2>value1 & value2>value3)
  {
     digitalWrite(in_1,HIGH) ;
     digitalWrite(in_2,LOW) ;
     analogWrite(enA,150);
     digitalWrite(in_3,HIGH) ;
     digitalWrite(in_4,LOW ) ;
     analogWrite(enB,150) ;
  }
  else if(value1>value2 & value1>value3)
   {

     digitalWrite(in_1,HIGH) ;
     digitalWrite(in_2,LOW) ;
     analogWrite(enA,180) ;

     digitalWrite(in_3,LOW) ;
     digitalWrite(in_4,HIGH) ;
     analogWrite(enB,180) ;

  }

  else if(value3>value2 & value3>value1)
  {
     digitalWrite(in_1,LOW) ;
     digitalWrite(in_2,HIGH) ;
     analogWrite(enA,130) ;

     digitalWrite(in_3,HIGH);
     digitalWrite(in_4,LOW);
     analogWrite(enB,130) ;
  }
}
delay(20);
}
}
//////////////////////////////////////////////////////////////////

void r_lineSensor()
{
  while(1)
  {
      value1 = analogRead(analogPin1);     // read the input pin
      value2 = analogRead(analogPin2);     // read the input pin
      value3 = analogRead(analogPin3);     // read the input pin
      value = (value1+value2+value3)/3;
      /*Serial.print(value1);
      Serial.print("\t");
      Serial.print(value2);
      Serial.print("\t");
      Serial.print(value3);
      Serial.print("\n");*/
      int avg=((value1+value2+value3)/3);
      //if(avg>870)
      if(value1>810 && value2>810 || value2>810 && value3>810)
      {
           digitalWrite(in_1,LOW) ;
           digitalWrite(in_2,LOW) ;
           analogWrite(enA,110) ;
      
           digitalWrite(in_3,LOW) ;
           digitalWrite(in_4,LOW) ;
           analogWrite(enB,110) ;
          
           delay(1000);
           
    
        /*
         digitalWrite(in_1,HIGH) ;
         digitalWrite(in_2,LOW) ;
         analogWrite(enA,110) ;
    
         digitalWrite(in_3,HIGH) ;
         digitalWrite(in_4,LOW) ;
         analogWrite(enB,110) ;
         */
        
           //delay(200);
           return;    
      }
      else 
      {
         if(value2>value1 & value2>value3)
         {
           digitalWrite(in_1,HIGH) ;
           digitalWrite(in_2,LOW) ;
           analogWrite(enA,150);
           digitalWrite(in_3,HIGH) ;
           digitalWrite(in_4,LOW ) ;
           analogWrite(enB,150) ;
         }
         else if(value1>value2 & value1>value3)
         {
      
           digitalWrite(in_1,HIGH) ;
           digitalWrite(in_2,LOW) ;
           analogWrite(enA,150) ;
      
           digitalWrite(in_3,LOW) ;
           digitalWrite(in_4,HIGH) ;
           analogWrite(enB,150) ;
          }
      
         else if(value3>value2 & value3>value1)
         {
           digitalWrite(in_1,LOW) ;
           digitalWrite(in_2,HIGH) ;
           analogWrite(enA,150) ;
      
           digitalWrite(in_3,HIGH);
           digitalWrite(in_4,LOW);
           analogWrite(enB,150) ;
          }
    }
    delay(20);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////

void rlil()
{
  int i;
  i=0;

  while(1)
  {
    value1 = analogRead(analogPin1);     // read the input pin
    value2 = analogRead(analogPin2);     // read the input pin
    value3 = analogRead(analogPin3);     // read the input pin
    value = (value1+value2+value3)/3;
  /*Serial.print(value1);
    Serial.print("\t");
    Serial.print(value2);
    Serial.print("\t");
    Serial.print(value3);
    
    Serial.print("\n");*/
    int avg=((value1+value2+value3)/3);
    if(i==2500)
        break;
    if(value2>value1 & value2>value3)
      {
       digitalWrite(in_1,HIGH) ;
       digitalWrite(in_2,LOW) ;
       analogWrite(enA,150);
       digitalWrite(in_3,HIGH) ;
       digitalWrite(in_4,LOW ) ;
       analogWrite(enB,150) ;
       i++;
      }
     else if(value1>value2 & value1>value3)
      {
  
       digitalWrite(in_1,HIGH) ;
       digitalWrite(in_2,LOW) ;
       analogWrite(enA,150) ;
  
       digitalWrite(in_3,LOW) ;
       digitalWrite(in_4,HIGH) ;
       analogWrite(enB,150) ;
       i++;
       }
  
      else if(value3>value2 & value3>value1)
       {
       digitalWrite(in_1,LOW) ;
       digitalWrite(in_2,HIGH) ;
       analogWrite(enA,150) ;
  
       digitalWrite(in_3,HIGH);
       digitalWrite(in_4,LOW);
       analogWrite(enB,150) ;
       i++;
        }
  }
  delay(20);
}
/////////////////////////////////////////////////////////////////////////

void flil()
{
  int i;
  i=0;

  while(1)
  {
    value1 = analogRead(analogPin1);     // read the input pin
    value2 = analogRead(analogPin2);     // read the input pin
    value3 = analogRead(analogPin3);     // read the input pin
    value = (value1+value2+value3)/3;
  /*Serial.print(value1);
    Serial.print("\t");
    Serial.print(value2);
    Serial.print("\t");
    Serial.print(value3);
    
    Serial.print("\n");*/
    int avg=((value1+value2+value3)/3);
    if(i==2000)
        break;
    if(value2>value1 & value2>value3)
      {
       digitalWrite(in_1,LOW) ;
       digitalWrite(in_2,HIGH) ;
       analogWrite(enA,150);
       digitalWrite(in_3,LOW) ;
       digitalWrite(in_4,HIGH) ;
       analogWrite(enB,150) ;
       i++;
      }
     else if(value1>value2 & value1>value3)
      {
  
       digitalWrite(in_1,HIGH) ;
       digitalWrite(in_2,LOW) ;
       analogWrite(enA,150) ;
  
       digitalWrite(in_3,LOW) ;
       digitalWrite(in_4,HIGH) ;
       analogWrite(enB,150) ;
       i++;
       }
  
      else if(value3>value2 & value3>value1)
       {
       digitalWrite(in_1,LOW) ;
       digitalWrite(in_2,HIGH) ;
       analogWrite(enA,150) ;
  
       digitalWrite(in_3,HIGH);
       digitalWrite(in_4,LOW);
       analogWrite(enB,150) ;
       i++;
        }
  }
  delay(20);
}
//////////////////////////////////////////////////////////////////////////////

void lineSensor()
{

  while(1)
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
    if(avg>835)
   // if(value1>810 & value2>810 || value2>810 & value3>810)
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
         analogWrite(enA,110) ;
    
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,HIGH) ;
         analogWrite(enB,110) ;
        
        
        delay(200);
        return;
        
    }
    else 
    {
       if(value2>value1 & value2>value3)
      {
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,HIGH) ;
         analogWrite(enA,150);
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,HIGH ) ;
         analogWrite(enB,150) ;
      }
      else if(value1>value2 & value1>value3)
       {
         digitalWrite(in_1,HIGH) ;
         digitalWrite(in_2,LOW) ;
         analogWrite(enA,150) ;
    
         digitalWrite(in_3,LOW) ;
         digitalWrite(in_4,HIGH) ;
         analogWrite(enB,150) ;
      }
    
      else if(value3>value2 & value3>value1)
      {
         digitalWrite(in_1,LOW) ;
         digitalWrite(in_2,HIGH) ;
         analogWrite(enA,150) ;
    
         digitalWrite(in_3,HIGH) ;
         digitalWrite(in_4,LOW) ;
         analogWrite(enB,150) ;
      }
    }
  delay(8);
  }
}
/////////////////////////////////////////////////////////////////////
void left_turn()
{
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  analogWrite(enA,150) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(enB,150) ;  
  delay(360);
  
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  analogWrite(enA,150) ;
  
  digitalWrite(in_3,HIGH) ;
  digitalWrite(in_4,LOW) ;
  analogWrite(enB,150) ;
  
  delay(700);
}
/////////////////////////////////////////////////////////////////////////////
void right_turn()
{
  
  digitalWrite(in_1,LOW) ;
  digitalWrite(in_2,HIGH) ;
  analogWrite(enA,150) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(enB,150) ;  
  delay(360);
  
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,LOW) ;
  analogWrite(enA,150) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(enB,150) ;
  
  delay(700);
}
////////////////////////////////////////////////////////////////////////////
void u_turn()
{
  digitalWrite(in_1,HIGH) ;
  digitalWrite(in_2,LOW) ;
  analogWrite(enA,200) ;
  
  digitalWrite(in_3,LOW) ;
  digitalWrite(in_4,HIGH) ;
  analogWrite(enB,200) ;
  
  delay(1300);
}
////////////////////////////////////////////////////////////////////////////
void stop_motion()
{
digitalWrite(in_1,LOW) ;
digitalWrite(in_2,LOW) ;
analogWrite(enA,0) ;

digitalWrite(in_3,LOW) ;
digitalWrite(in_4,LOW) ;
analogWrite(enB,0) ;
delay(2000);
}
///////////////////////////////////////////////////////////////////
