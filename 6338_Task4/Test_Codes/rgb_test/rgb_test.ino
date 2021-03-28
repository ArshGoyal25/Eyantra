Serial.println();
#include <LiquidCrystal_I2C.h>
int redPin= 11;
int greenPin = A0;
int bluePin = A5;
char n;
int flag=1;
void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
   analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}



void rgb() {
  
 
  
  Serial.println("enter colour");
  
 while(1)
 {
  n=Serial.read();
  Serial.flush();
  if (int(n)==82)
    {
       setColor(0, 255, 255); // Red Color
  delay(1000);
  break;
  
    }
  else if (int(n)==66)
  {
     setColor(255, 255, 0); // Blue Color
  delay(1000);
  break;
  
  }
  else if (int(n)==71)
  {
     setColor(255, 0, 255); // Green Color
  delay(1000);
  break;
  
  }
  else if (int(n)==89)
  {
     setColor(0,0, 0 ); // Yellow Color
  delay(1000);
  break;
  
  }

}
}


void loop()
{

rgb();
}
