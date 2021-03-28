 /*
 * Team Id: #6338
 * Author List: Arnav Agarwal, Arsh Gayal, Sujith K
 * Filename: rgb_test.ino
 * Theme: Ant Bot 
 * Functions: rgb, setColor
 * Global Variables: All global variables are declared in the header file line.h
 */



/*
 * Function Name: rgb
 * Input: a character 
 * Output: none
 * Logic: This function is used to glow the correct colour of the RGB LED.
 * We are doing so by the checking the ASCII value of the character sent by the Raspberry Pi through the serial port.
 * Example Call: rgb(R)
 */  
void rgb(char n) 
{  
  if(n=='R')
    {
      setColor(0, 255, 255); // RGB LED will glow red in colour for one second and then turn off.
      delay(1000);
      setColor(255,255,255);
    }
  else if (n=='B')
    { 
      setColor(255, 0, 255); // RGB LED will glow blue in colour for one second and then turn off.
      delay(1000);
      setColor(255,255,255);
    }
  else if (n=='G')
    {
      setColor(255, 255, 0); // RGB LED will glow green in colour for one second and then turn off.
      delay(1000);
      setColor(255,255,255);
    }
  else if (n=='Y')
    {
     setColor(0,255,0); // RGB LED will glow yellow in colour for one second and then turn off.
     delay(1000);
     setColor(255,255,255);
    }
}


/*
 * Function Name:setColor
 * Input: redValue, greenValue, blueValue. These parameters are the analog values used to turn on the LED with the correct colour.
 * Output: none
 * Logic: This function is used to set the analog values of the red, green and blue analog pins that have been declared.
 * We are doing this using the basic analogWrite function which is present in the IDE.
 * Example Call: setColor(0,255,255)
 */ 
void setColor(int redValue, int greenValue, int blueValue) 
{
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
