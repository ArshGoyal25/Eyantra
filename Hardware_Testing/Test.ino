#include <Servo.h>

int analogPin1 = 0;  
int analogPin2 = 2;
int analogPin3 = 4;
int value1 = 0;
int value2 = 0;
int value3 = 0;
int value = 0;
/*
Servo stservo;
Servo micservo;
//int Buzzer = 13;
*/

void setup()
{
  Serial.begin(9600);
 /* stservo.attach(3);
  micservo.attach(6);
  stservo.write(0);
  micservo.write(0);
 //pinMode(Buzzer,OUTPUT);
 */
}
/*
void servoMotion()
{  
  //Serial.println("");
  micservo.write(60);
  delay(100);
  stservo.write(100);
  delay(100);
  micservo.write(150);
  delay(100);
  stservo.write(0);
  delay(100);

}
*/
void lineSenor()
{
  //Serial.print("you you you");
  //digitalWrite(13, HIGH);
  //Serial.println("me me me");
  value1 = analogRead(analogPin1);     // read the input pin
  
  value2 = analogRead(analogPin2);     // read the input pin
  value3 = analogRead(analogPin3);     // read the input pin
  value = (value1+value2+value3)/3;
  Serial.println(value1);
  Serial.println(value2);
  Serial.println(value3);
 /* if(value <70){
    Serial.write("S");
    //servoMotion();
    //digitalWrite(Buzzer, HIGH);    
  }
  else
      Serial.print("Bunti");
      //digitalWrite(Buzzer, LOW);    
*/
}

void loop(){
 
      lineSenor();
      delay(20);
//  Serial.println("S");
      
  
}
