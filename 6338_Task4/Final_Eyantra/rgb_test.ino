void rgb(char n) 
{  
  if(int(n)==82)
    {
      setColor(0, 255, 255); // Red Color
      delay(1000);
      setColor(255,255,255);
    }
  else if (int(n)==66)
    { 
      setColor(255, 0, 255); // Blue Color
      delay(1000);
      setColor(255,255,255);
    }
  else if (int(n)==71)
    {
      setColor(255, 255, 0); // Green Color
      delay(1000);
      setColor(255,255,255);
    }
  else if (int(n)==89)
    {
     setColor(0,255,0); // Yellow Color
     delay(1000);
     setColor(255,255,255);
    }
}

void setColor(int redValue, int greenValue, int blueValue) 
{
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
