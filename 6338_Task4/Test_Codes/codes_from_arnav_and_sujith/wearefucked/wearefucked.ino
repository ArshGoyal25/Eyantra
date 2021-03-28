#include<stdlib.h>
struct Anthill
{
  char type;
  char no;
  char ser_1;
  char ser_2;
}lala[4];
char ch;
int i = 0;

void setup() {
  Serial.begin(9600);
}

void get_det(Anthill fofo[4]) {
for(i=0;i<4;i++)
{
   Serial.print("\n");
   if(i==0)
    Serial.println("LU");
    else if(i==1)
    Serial.println("RU");
     else if(i==2)
    Serial.println("RD");
     else if(i==3)
    Serial.println("LD");
     
   Serial.println("Enter the anthill type");
   while(1) 
   {
    
    ch = Serial.read();
      
        if (int(ch)>=65 && int(ch) <=122)
          {fofo[i].type= ch;
          
          break;}
    
    /*if(Serial.available())
    {
      fofo.type = Serial.read();
      Serial.println(int(fofo.type));
      Serial.print("\n");
      Serial.flush();
      break;
    }*/
   }
   
         Serial.print("\n");
         Serial.flush();
   
   Serial.println("Enter the anthill number");
   
   
   
       
      while (1)
      {
        ch = Serial.read();
        
        if (int(ch)>=48 && int(ch) <=58)
          {fofo[i].no= ch;
          break;}
      } 
       
         Serial.print("\n");
         Serial.flush();
         
 Serial.println("Enter the requirement for service location 1\n");
   while(1)
   {
      ch = Serial.read();
        
        if (int(ch)>=65 && int(ch) <=122)
          {fofo[i].ser_1= ch;
            break;}
     }
        Serial.print("\n");
         Serial.flush();
  
   Serial.println("Enter the requirement for service location 2\n");    
    while(1)
   {
      ch = Serial.read();
        
        if (int(ch)>=65 && int(ch) <=122)
          {fofo[i].ser_2= ch;
         
          break;}
   }
        Serial.print("\n");
        Serial.flush();
        
 
   Serial.print(fofo[i].type);
    Serial.print("\t");
   Serial.print(fofo[i].no);
    Serial.print("\t");
   Serial.print(fofo[i].ser_1);
    Serial.print("\t");
   Serial.print(fofo[i].ser_2);
   Serial.print("\n");
 
  
}
return;
}
void loop()
{
  
get_det(lala); 
delay(1000000000);
}

