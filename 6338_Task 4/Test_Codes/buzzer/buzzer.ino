int Buzzer = 13;
pinMode(Buzzer,OUTPUT);
void buzz() 
{
  digitalWrite(Buzzer, HIGH);
  delay(5000);
  digitalWrite(Buzzer, LOW);  
}
