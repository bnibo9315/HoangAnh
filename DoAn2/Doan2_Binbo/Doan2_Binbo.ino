////////////////////////////////////////////////////
//  Author : Thanh Quang Long - Founder HNLShop   //
//  Day : 7/6/2020                                //
////////////////////////////////////////////////////
#include <ShiftRegister74HC595.h>

#define sensor_1 A0
#define sensor_2 A1

// Traffic lights Left
#define Green_Left 13
#define Yellow_Left 12
#define Red_Left 11

// Traffic lights Right
#define Green_Right 10
#define Yellow_Right 9
#define Red_Right 8


ShiftRegister74HC595 SR74HC595_1 (2, 2, 3, 4); 
ShiftRegister74HC595 SR74HC595_2 (2, 5, 6, 7);
int value_1  = 0;
int value_2  = 0;
int value  = 0;
int mode =0 ;
int digit1,digit2,value_sensor1 ,value_sensor2; 
uint8_t  number_1[] = {B11000000, //0
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

void setup() {
  Serial.begin(115200);
  pinMode(Green_Left,OUTPUT);
  pinMode(Yellow_Left,OUTPUT);
  pinMode(Red_Left,OUTPUT);
  pinMode(Green_Right,OUTPUT);
  pinMode(Yellow_Right,OUTPUT);
  pinMode(Red_Right,OUTPUT);

  pinMode(sensor_1,INPUT);
  pinMode(sensor_2,INPUT);
  
  digitalWrite(Green_Left,LOW);
  digitalWrite(Yellow_Left,LOW);
  digitalWrite(Red_Left,LOW);
  digitalWrite(Green_Right,LOW);
  digitalWrite(Yellow_Right,LOW);
  digitalWrite(Red_Right,LOW);
 
}

void loop() {
  // Read 2 sensor
  int value_sensor1 = digitalRead(sensor_1);
  int value_sensor2 = digitalRead(sensor_2);
  digitalWrite(Green_Left,HIGH);
  digitalWrite(Red_Right,HIGH);
  Count(10,3);
  digitalWrite(Yellow_Left,HIGH);
  digitalWrite(Green_Left,LOW);
  Count_Yellow(2,0);
  TrafficLight_Off();
  digitalWrite(Green_Right,HIGH);
  digitalWrite(Red_Left,HIGH);
  Count_next(10,3);
  digitalWrite(Yellow_Right,HIGH);
  digitalWrite(Green_Right,LOW);
  Count_Yellow(2,0);
  TrafficLight_Off();

}

void showNumber_Left(int num)
{
 
    digit2=num % 10 ;
    digit1=(num / 10) % 10 ;
    uint8_t numberToPrint[]= {number_1[digit2],number_1[digit1]};
    SR74HC595_1.setAll(numberToPrint);  

}
void showNumber_Right(int num)
{
 
    digit2=num % 10 ;
    digit1=(num / 10) % 10 ;
    uint8_t numberToPrint[]= {number_1[digit2],number_1[digit1]};
    SR74HC595_2.setAll(numberToPrint);  

}
void readSensor()
{
  int value_sensor1 = digitalRead(sensor_1);
  int value_sensor2 = digitalRead(sensor_2); 
  if( value_sensor1 == 0 )
  {
    value = 10;
    value_2 = 7;
    mode =1 ;
    }
  if( value_sensor2 == 0 )
  {
    value = 10;
    value_1 = 7;
    mode =2 ;
}
  }
void TrafficLight_Off()
{
  digitalWrite(Green_Left,LOW);
  digitalWrite(Yellow_Left,LOW);
  digitalWrite(Red_Left,LOW);
  digitalWrite(Green_Right,LOW);
  digitalWrite(Yellow_Right,LOW);
  digitalWrite(Red_Right,LOW);
  
  }
void Count(int timer_start, int timer_stop) // 0 Left ; 1 Right
{
  if(mode ==0 || mode ==2 )
  {
  for(int i=timer_start; i >= timer_stop; i--)
  {
    showNumber_Left(i);
    showNumber_Right(i-3);
    delay(1000);
   readSensor();
  }
  if(mode == 1)
  {
    mode = 0;
    }
  }
  if ( mode == 1)
  {
     for(int i=timer_start+ value; i >= timer_stop; i--)
  {
    
    showNumber_Left(i );
    showNumber_Right(i+ value_2 - value);
    delay(1000);
    readSensor();
  }

  value_2 = 0;
    }
 }

void Count_next(int timer_start, int timer_stop) // 0 Left ; 1 Right
{  if ( mode == 0 || mode  == 1)
  {
  for(int i=timer_start; i >= timer_stop; i--)
  {
    showNumber_Left(i-3);
    showNumber_Right(i);
    readSensor();
    delay(1000);
  }
  if(mode == 2)
  {
    mode = 0;
    }
  
 }
    if ( mode == 2)
  {
     for(int i=timer_start+ value; i >= timer_stop; i--)
  {
    
    showNumber_Left(i+ value_1 - value );
    showNumber_Right(i);
    delay(1000);
    readSensor();
  }
  value_1 = 0;
    }
}
void Count_Yellow(int timer_start, int timer_stop)
{

  for(int i=timer_start; i >= timer_stop; i--)
  {
    showNumber_Left(i);
    showNumber_Right(i);
    delay(1000);
  }
 }
