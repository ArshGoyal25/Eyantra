/*int redPin= 1;
int greenPin = 2;
int bluePin = 3;
*/
  /*pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
   analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);*/


void rgb(char n) {
  
  
 
 
  if (int(n)==82)
    {
       setColor(0, 255, 255); // Red Color
 Serial.println("red");
    }
  else if (int(n)==66)
  {
     setColor(255, 0, 255); // Blue Color
  Serial.println("blue");
  
  }
  else if (int(n)==71)
  {
     setColor(255, 255, 0); // Green Color
 Serial.println("green");
  }
  else if (int(n)==89)
  {
     setColor(0,0, 0 ); // Yellow Color
  Serial.println("yellow");
  }

}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}

///your_mom();
