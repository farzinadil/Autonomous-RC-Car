/*
 The Project name:Jarvis
Self driving REV 2.0 alpha basic structure left turn and right turn and moving forward and stopping 
5/2/19
-Reverse has been added
-more knobs have been added such as full speed and half speed and closing distance.
- restructured switch statements
- Drive loagic has been revidsed and updated
trigger pins = pin 5
echo pins = 4 for front 
            7 for right 
            8 for left
            12 for rear
servo for steering is set to pin 11 
*/
#include <Servo.h>
Servo steering; 

// tuning knobs
 const int Center_angle = 95; // center steering angle in degrees threshold
 const int Left_angle = 155; //to turn left angle in degrees threshold
 const int Right_angle = 50; //to turn right angle in degrees threshold
 const int closing_distance = 110; // closing distance threshhold
 const int half_speed = 50; // 50% duty cycle
 const int full_speed = 100; // 100% duty cycle 
 const int stopped = 0; // shuts off electric motor
 const int setDelay = 1;// delays
 const int between_sensor_delay = 10; // delay for indidual sensor bring up
 const int sensor_timer_on = 20; //ultra sonic sensor timer
 const int sensor_timer_off = 10; //ultra sonic sensor timer
//pin alocation
 const int velo = 3; //motor speed using duty cycle
 const int dir = 2; // forward or reverse  
 const int trig = 5; // ultrasonic sensor trigger (pwm) front of car
 const int front_echo = 4; // ultrasonic echo front of car
 const int right_echo = 7; // ultrasonic echo front of car
 const int left_echo = 8; // ultrasonic echo  of car
 const int rear_echo = 12; // ultrasonic echo rear of car
 int front_distance_cm = 10; // front of car distance in cm readout
 int right_distance_cm = 10; // right of car distance in cm readout
 int left_distance_cm = 10; //left of car distance in cm readout
 int rear_distance_cm = 10; // rear of car distance in cm readout
  
void setup() 
{
  //pin setup
Serial.begin(9600);
steering.attach(11);
pinMode(velo,OUTPUT);
pinMode(dir,OUTPUT);
pinMode(trig,OUTPUT);
pinMode(front_echo,INPUT);
pinMode(right_echo,INPUT);
pinMode(left_echo,INPUT);
pinMode(rear_echo,INPUT);
}

void loop() 
{

 //calling sensor setup functions

front_sensor();
delay(between_sensor_delay);  
left_sensor();
delay(between_sensor_delay);
right_sensor(); 
delay(between_sensor_delay); 
rear_sensor(); 
delay(between_sensor_delay);
  
// self driving logic



int mode = 5; 

// Find which path is clearest

if (front_distance_cm > closing_distance && front_distance_cm >= right_distance_cm  && front_distance_cm >= left_distance_cm  && front_distance_cm >= rear_distance_cm)
{
  mode = 1;
}
else if(left_distance_cm > closing_distance && left_distance_cm > front_distance_cm && left_distance_cm > right_distance_cm && left_distance_cm > rear_distance_cm)
{
  mode = 2;
}
else if(right_distance_cm > closing_distance && right_distance_cm > front_distance_cm && right_distance_cm > left_distance_cm && right_distance_cm > rear_distance_cm)
{
 mode = 3; 
}
else if (rear_distance_cm > closing_distance && rear_distance_cm > right_distance_cm && rear_distance_cm > left_distance_cm)
{
  mode = 4;
}
else if (rear_distance_cm < closing_distance && front_distance_cm < closing_distance && rear_distance_cm < closing_distance )
{
  mode = 5;
}
switch (mode) 
{
  case 1: 
  
    //Straight
    steering.write(Center_angle);
    digitalWrite(dir,HIGH);
    analogWrite(velo,full_speed);
    break;
    
  case 2:

      //Right
      steering.write(Right_angle);
      _delay_ms(100);
      digitalWrite(dir,HIGH);
      analogWrite(velo,half_speed);
      delay(setDelay);
      break;
      
  case 3:  
 
      //Left
      steering.write(Left_angle);
      _delay_ms(100);
      digitalWrite(dir,HIGH);
      analogWrite(velo,half_speed);
      delay(setDelay);
      break;
     
  case 4:
  
      //Middle
      steering.write(Center_angle);
      digitalWrite(dir,LOW);
      analogWrite(velo,half_speed);
      delay(setDelay);
      break;

  default:
  
    //Stop
    digitalWrite(dir,HIGH);
    analogWrite(velo,stopped);
    break;
}

} //end main
/*******************************************************/
 void front_sensor() //front sensor setup
 {

long duration; // ultrasonic value storage
  
digitalWrite(trig,LOW);
delay(sensor_timer_off);
digitalWrite(trig,HIGH);
delay(sensor_timer_on);
digitalWrite(trig,LOW);

pinMode(front_echo,INPUT);
duration = pulseIn(front_echo,HIGH);
//delay(sensor_timer_off);
front_distance_cm = (duration/2)/29.1;
  /*
  Serial.print("front sensor: "); //for sensor debug
  Serial.print(front_distance_cm);
  Serial.print("cm   ");
  Serial.println();
  */
 }
/*******************************************************/
void right_sensor() //right sensor setup
 {

long duration; // ultrasonic value storage
 
digitalWrite(trig,LOW);
delay(sensor_timer_off);
digitalWrite(trig,HIGH);
delay(sensor_timer_on);
digitalWrite(trig,LOW);

pinMode(right_echo,INPUT);
duration = pulseIn(right_echo,HIGH);
//delay(sensor_timer_off);

right_distance_cm = (duration/2)/29.1;
  /*
  Serial.print("right sensor: "); //for sensor debug
  Serial.print(right_distance_cm);
  Serial.print("cm   ");
  Serial.println();
  */
 }
 /*******************************************************/
void left_sensor() //left sensor setup
 {

long duration; // ultrasonic value storage
  
digitalWrite(trig,LOW);
delay(sensor_timer_off);
digitalWrite(trig,HIGH);
delay(sensor_timer_on);
digitalWrite(trig,LOW);

pinMode(left_echo,INPUT);
duration = pulseIn(left_echo,HIGH);
//delay(sensor_timer_off);

left_distance_cm = (duration/2)/29.1;
  /*
  Serial.print("left sensor: "); //for sensor debug
  Serial.print(left_distance_cm);
  Serial.print("cm   ");
  Serial.println();
  */
 }
/*******************************************************/
void rear_sensor() //rear sensor setup
 {

long duration; // ultrasonic value storage
  // front sonic_sensor test
digitalWrite(trig,LOW);
delay(sensor_timer_off);
digitalWrite(trig,HIGH);
delay(sensor_timer_on);
digitalWrite(trig,LOW);

pinMode(rear_echo,INPUT);
duration = pulseIn(rear_echo,HIGH);
//delay(sensor_timer_off);

rear_distance_cm = (duration/2)/29.1;
/*
Serial.print("rear sensor: "); //for sensor debug
Serial.print(rear_distance_cm);
Serial.print("cm   ");
Serial.println();
*/
 }
