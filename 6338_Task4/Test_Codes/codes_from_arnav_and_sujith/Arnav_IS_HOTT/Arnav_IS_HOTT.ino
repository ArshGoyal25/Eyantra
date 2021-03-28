  #include<stdlib.h>
struct Anthill
{
  char type;
  char no;
  char ser_1;
  char ser_2;
};
char ch;
int i = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {

   Serial.println("Enter the anthill type");
   while(1)
   {
    if(Serial.available())
    {
      lala.type = Serial.read();
      Serial.println(int(lala.type));
      Serial.print("\n");
      Serial.flush();
      break;
    }
   }
   Serial.println("Enter the anthill number");
   
   
   
       
      while (1)
      {
        ch = Serial.read();
        
        if (int(ch)>=48 && int(ch) <=58)
          {lala.no= ch;
          break;}
      } 
       
         Serial.print("\n");
         Serial.flush();
         
 Serial.println("Enter the requirement for service location 1\n");
   while(1)
   {
      ch = Serial.read();
        
        if (int(ch)>=65 && int(ch) <=122)
          {lala.ser_1= ch;
            break;}
     }
        Serial.print("\n");
         Serial.flush();
  
   Serial.println("Enter the requirement for service location 2\n");    
    while(1)
   {
      ch = Serial.read();
        
        if (int(ch)>=65 && int(ch) <=122)
          {lala.ser_2= ch;
         
          break;}
   }
        Serial.print("\n");
        Serial.flush();
        
  
   Serial.println(lala.type);
   Serial.println(lala.no);
   Serial.println(lala.ser_1);
   Serial.println(lala.ser_2);
  delay(100000000);
  
 
   
   
}

