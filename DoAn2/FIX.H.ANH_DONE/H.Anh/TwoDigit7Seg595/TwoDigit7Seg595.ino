#include <ShiftRegister74HC595.h>

/* 
 *  2 Digitl 7 segment display PCB board with (2) 74HC595 shift register ICs
 *  Arduino Tutorial - www.Ardumotive.com
 *  Dev: Michalis Vasilakis // Date: 31/1/2018 // Ver:1.0
 */
// create shift register object (number of shift registers, data pin, clock pin, latch pin)

ShiftRegister74HC595 sr (2, 2, 3, 4);
ShiftRegister74HC595 sr1 (2, 5, 6, 7);  

#define R 8
#define Y 9
#define G 10

#define R1 11
#define Y1 12
#define G1 13

int number=5; 
int number_Y=2;
int number_G=8;;

int number1=10; 
int number_Y1=3;
int number_G1=12;

unsigned long time1 =0;
unsigned long time2 =0;


int value,digit1,digit2,digit3,digit4; 
uint8_t  numberB[] = {B11000000, //0
                      B11111001, //1 
                      B10100100, //2
                      B10110000, //3 
                      B10011001, //4
                      B10010010, //5
                      B10000011, //6
                      B11111000, //7
                      B10000000, //8
                      B10011000 //9
                     };

uint8_t  numberB1[] = {B11000000, //0
                      B11111001, //1 
                      B10100100, //2
                      B10110000, //3 
                      B10011001, //4
                      B10010010, //5
                      B10000011, //6
                      B11111000, //7
                      B10000000, //8
                      B10011000 //9
                     };

void countDown_R();
void countDown_Y();
void countDown_G();

void countDown_R1();
void countDown_Y1();
void countDown_G1();

void trai();
void phai();
void tong();

void setup() {
  pinMode(R,OUTPUT);  digitalWrite(R,0);
  pinMode(Y,OUTPUT);  digitalWrite(Y,0);
  pinMode(G,OUTPUT);  digitalWrite(G,0);

  pinMode(R1,OUTPUT); digitalWrite(R1,0);
  pinMode(Y1,OUTPUT); digitalWrite(Y1,0);
  pinMode(G1,OUTPUT); digitalWrite(G1,0);
  //Count from 0 to 'number' 
  //countUp();
  //countUp1();
  //Count from 'number' to 0
  //countDown();  // <--- Comment countUp and uncomment countDown
  //countDown_Y();
  //countDown1();
  //Blink 4 times all on and all off.
  //blink();  
}

void loop() 
{
  //trai();
  //phai();
  ////////////////////////////////////////////
     if( (unsigned long) ( millis() - time1) > 1500 )
     {
      trai();
      time1=millis();
     }
  ////////////////////////////////////////////
     if( (unsigned long) ( millis() - time2) > 500 )
     {
      phai();
      time2=millis();
     }
//////////////////////////////////////////////
}
////////////////////////////////////////////////////////////
void trai()
{
  digitalWrite(R,1);    
  countDown_R();        
  digitalWrite(R,0); 
  delay(500);       
     
  digitalWrite(Y,1);   
  countDown_Y();
  digitalWrite(Y,0); 
  delay(500);
  
  digitalWrite(G,1); 
  countDown_G();
  digitalWrite(G,0);
  delay(1000);
}
////////////////////////////////////////////////////////////
void tong()
{
  digitalWrite(R,1);    
  countDown_R();        
  digitalWrite(R,0); 
  delay(500);       
     
  digitalWrite(Y,1);   
  countDown_Y();
  digitalWrite(Y,0); 
  delay(500);
  
  digitalWrite(G,1); 
  countDown_G();
  digitalWrite(G,0);
  delay(1000);
}
////////////////////////////////////////////////////////////
void phai()
{
  digitalWrite(G1,1);  //G  
  countDown_G1();        
  digitalWrite(G1,0);    
  delay(500);       
     
  digitalWrite(Y1,1);    
  countDown_Y1();
  digitalWrite(Y1,0);
  delay(500);
  
  digitalWrite(R1,1);  //R
  countDown_R1();
  digitalWrite(R1,0);
  delay(1000);
}
////////////////////////////////////////////////////////////
/*
/////////////////////////////////////////////////////////////
void countUp(){
  for (int i = 0; i<=number; i++){
    //Split number to digits:
    digit2=i % 10 ;
    digit1=(i / 10) % 10 ;
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {numberB[digit2],numberB[digit1]};
    sr.setAll(numberToPrint); 
    //sr1.setAll(numberToPrint);
    //Reset them for next time
    digit1=0;
    digit2=0;
    delay(1000); // Repeat every 1 sec
  }
}
///////////////////////////////////////////////////////////////
void countUp1(){
  for (int i = 0; i<=number; i++){
    //Split number to digits:
    digit2=i % 10 ;
    digit1=(i / 10) % 10 ;
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {numberB[digit2],numberB[digit1]};
    //sr.setAll(numberToPrint); 
    sr1.setAll(numberToPrint);
    //Reset them for next time
    digit1=0;
    digit2=0;
    delay(1000); // Repeat every 1 sec
  }
}
/////////////////////////////////////////////////////////////
*/
void countDown_R(){
  number=5;
  for (number; number>=0; number--){
    //Split number to digits:
    digit2=number % 10 ;
    digit1=(number / 10) % 10 ;
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {numberB[digit2],numberB[digit1]};
    sr.setAll(numberToPrint); 
    //Reset them for next time
    digit1=0;
    digit2=0;
    delay(1000); // Repeat every 1 sec
  }
}
///////////////////////////////////////////////////////////
/*
void countDown_R1(){
  number1 = 5;
  for (number1; number1>=0; number1--){
    //Split number to digits:
    digit4=number1 % 10 ;                                       
    digit3=(number1 / 10) % 10 ;                               
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {numberB1[digit4],numberB1[digit3]}; //uint8_t numberToPrint[]= {numberB[digit2],numberB[digit1]};
    sr1.setAll(numberToPrint); 
    //Reset them for next time
    digit3=0;
    digit4=0;
    delay(1000); // Repeat every 1 sec
  }
}
///////////////////////////////////////////////////////////
void countDown_Y(){
  number_Y = 3;
  for (number_Y; number_Y>=0; number_Y --){
    //Split number to digits:
    digit2=number_Y % 10 ;
    digit1=(number_Y / 10) % 10 ;
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {numberB[digit2],numberB[digit1]};
    sr.setAll(numberToPrint); 
    //Reset them for next time
    digit1=0;
    digit2=0;
    delay(1000); // Repeat every 1 sec
  }
}
//////////////////////////////////////////////////////////////////
void countDown_Y1(){
  number_Y1 = 3;
  for (number_Y1; number_Y1>=0; number_Y1 --){
    //Split number to digits:
    digit4=number_Y1 % 10 ;
    digit3=(number_Y1 / 10) % 10 ;
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {numberB1[digit4],numberB1[digit3]};
    sr1.setAll(numberToPrint); 
    //Reset them for next time
    digit3=0;
    digit4=0;
    delay(1000); // Repeat every 1 sec
  }
}
/////////////////////////////////////////////////////////////////
void countDown_G(){
  number_G = 8;
  for (number_G; number_G>=0; number_G --){
    //Split number to digits:
    digit2=number_G % 10 ;
    digit1=(number_G / 10) % 10 ;
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {numberB[digit2],numberB[digit1]};
    sr.setAll(numberToPrint); 
    //Reset them for next time
    digit1=0;
    digit2=0;
    delay(1000); // Repeat every 1 sec
  }
}
////////////////////////////////////////////////////////////
void countDown_G1(){
  number_G1 = 8;
  for (number_G1; number_G1>=0; number_G1 --){
    //Split number to digits:
    digit4=number_G1 % 10 ;
    digit3=(number_G1 / 10) % 10 ;
    //Send them to 7 segment displays
    uint8_t numberToPrint[]= {numberB1[digit4],numberB1[digit3]};
    sr1.setAll(numberToPrint); 
    //Reset them for next time
    digit3=0;
    digit4=0;
    delay(1000); // Repeat every 1 sec
  }
}
////////////////////////////////////////////////////////////
*/
//Blink
void blink(){
  for(int i = 0; i<4; i++){
    sr.setAllLow(); // set all pins Low (off)
    delay(1000);
    sr.setAllHigh(); // set all pins High (on)
    delay(1000);
  }
}
