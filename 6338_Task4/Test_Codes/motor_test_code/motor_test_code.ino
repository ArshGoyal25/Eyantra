 int enA = 3; 
 int in_1 = 8 ;
 int in_2 = 7  ;
 int enB = 9;  
 int in_3 = 4 ;
 int in_4 = 2 ;

void setup()

{

pinMode(enA,OUTPUT) ;   
pinMode(in_1,OUTPUT) ;  
pinMode(in_2,OUTPUT) ;
pinMode(enB,OUTPUT) ;   
pinMode(in_3,OUTPUT) ; 
pinMode(in_4,OUTPUT) ;

}



void loop()

{


digitalWrite(in_1,LOW) ;

digitalWrite(in_2,HIGH) ;

analogWrite(enA,255) ;



digitalWrite(in_3,LOW) ;

digitalWrite(in_4,HIGH) ;

analogWrite(enB,255) ;


delay(3000) ;


digitalWrite(in_1,LOW) ;

digitalWrite(in_2,LOW) ;

analogWrite(enA,255) ;



digitalWrite(in_3,LOW) ;
 
digitalWrite(in_4,LOW) ;

analogWrite(enB,255) ;


delay(5000) ;

/*
digitalWrite(in_1,HIGH) ;

digitalWrite(in_2,LOW) ;

analogWrite(enA,255) ;



digitalWrite(in_3,HIGH) ;

digitalWrite(in_4,LOW) ;

analogWrite(enB,255) ;


delay(3000) ;
 
*/
}
