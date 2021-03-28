
//int analogPin1 = 4;  
//int analogPin2 = 1;
/*int analogPin3 = 2;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int value = 0;
int enA = 3 ; 
int in_1 = 8 ; 
int in_2 = 9 ;
int enB = 5 ; 
int in_3 = 6 ;
int in_4 = 7 ;*/

int s=0;
//char col_arr[6];
 
char check;
/*int redPin= 1;
int greenPin = 2;
int bluePin = 3;*/
/*void setup()
{
  Serial.begin(9600);
   pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
   analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  pinMode(enA,OUTPUT) ;   
  pinMode(in_1,OUTPUT) ;  
  pinMode(in_2,OUTPUT) ;
  pinMode(enB,OUTPUT) ;   
  pinMode(in_3,OUTPUT) ; 
  pinMode(in_4,OUTPUT) ;
}*/

void communication()
{
  while(1)
  {
    
    
    Serial.write("S");           //The arduino sends out signal "S" to the Pi communicating that it is ready in the right orientaion ( Cue to the PiCam to capture and detect Aruco)
    Serial.flush();
    if(Serial.available())
    {
      check= Serial.read();
      Serial.print(check);
      Serial.flush();
      
    }
    if(int(check)==82 || int(check)==66 || int(check)==71 )
    {
      col_arr[s]=check;
      rgb(check);
      s++;
      return;
    }
  }
}



void start_colour()
{
 /* lineSensor();
  right_turn();
  lineSensor();
  lineSensor();
  lineSensor();
  left_turn();
  r_lineSensor();
  stop_motion();*/
  communication();
   
  
}

void server_motion()
{ 
  int j=1;
  while (j<6)
  {
 /* lineSensor();
  left_turn();
  lineSensor();
  if (j==3)
    {
      lineSensor();
    }
  right_turn();
  r_lineSensor();
  stop_motion();*/
  delay(3000);
  communication();
  j++;
  }
}

void end_colour()
{
 /* lineSensor();
  right_turn();
  lineSensor();
  lineSensor();
  lineSensor();
  right_turn();
  r_lineSensor();
  stop_motion();
  */
}

/*

void loop()
{
  start_colour();
  server_motion();
  end_colour();
 delay(10000);  
 //delay(1000);
 }*/
