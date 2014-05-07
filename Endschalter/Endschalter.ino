// positive Schritte -> im Uhrzeigersinn

/* 
 Stepper Motor Control - one revolution
 
 This program drives a unipolar or bipolar stepper motor.
 
 The motor driver is attached to digital pins 8,9 of the Arduino.
 
 The motor should revolve one revolution in one direction, then
 one revolution in the other direction.  
 
 Changed by Ronivaldo Sampaio to M Series
 2013
 https://github.com/ronivaldo/Arduino-StepperMSeries
 
 Original:
 http://www.arduino.cc/en/Reference/Stepper
 This example code is in the public domain.
 Created 11 Mar. 2007
 Modified 30 Nov. 2009
 by Tom Igoe
 
 */

#include <StepperMSeries.h>

// change this to the number of steps on your motor
#define STEPS 200
#define PULSE_PIN_1 37
#define DIRECTION_PIN_1 36
#define PULSE_PIN_2 35
#define DIRECTION_PIN_2 34
#define PULSE_PIN_3 33
#define DIRECTION_PIN_3 32

#define input_1 2
#define input_2 3
#define input_3 4
#define input_12 5
#define input_22 6
#define input_32 7

boolean reference_1 = false;
boolean reference_2 = false;
boolean reference_3 = false;

int angle_1=0;
int angle_2=0;
int angle_3=0;

// create an instance of the stepper class, specifying
// the number of steps of the motor and the pins it's
// attached to
StepperMSeries stepper_1(STEPS, PULSE_PIN_1, DIRECTION_PIN_1);
StepperMSeries stepper_2(STEPS, PULSE_PIN_2, DIRECTION_PIN_2);
StepperMSeries stepper_3(STEPS, PULSE_PIN_3, DIRECTION_PIN_3);


void setup() {
  
  
  Serial.begin(9600);
  // set the speed at 60 rpm:
  stepper_1.setSpeed(60);
  stepper_2.setSpeed(60);
  stepper_3.setSpeed(60);
  
  pinMode(input_1, INPUT);
  pinMode(input_2, INPUT);
  pinMode(input_3, INPUT);
  pinMode(input_12, INPUT);
  pinMode(input_22, INPUT);
  pinMode(input_32, INPUT);
  
  delay(1000);
}

void loop() {
  
  if(!reference_1 || !reference_2 || !reference_3){
    if(!reference_1){
      if(!digitalRead(input_1)){
        reference_1=true;
        angle_1=175;
        stepper_1.step(2);
        reference_1=true; 
      }else{
        Serial.println("Fahre hoch 1");
        stepper_1.step(-1);
      }
    }
    if(!reference_2){
      if(!digitalRead(input_2)){
        reference_2=true;
        angle_2=175;
        stepper_2.step(2);
        reference_2=true; 
      }else{
        stepper_2.step(-1);
        Serial.println("Fahre hoch 2");
      }
    }
    if(!reference_3){ 
      if(!digitalRead(input_3)){
        Serial.println(digitalRead(input_3));
        reference_3=true;
        angle_3=175;
        stepper_3.step(2);
        reference_3=true; 
      }else{
        Serial.println("Fahre hoch 3");
        stepper_3.step(-1);
      }
    }
  }else{
    Serial.println("Messen");
    
    doCheck();
  }
  delay(500); 
  Serial.println(""); 
}

void doCheck(){
  if(!digitalRead(input_1)){
    Serial.println("Input_1");
    stepper_1.step(3);
    angle_1=175;
  }
  else if(!digitalRead(input_12)){
    Serial.println("Input_12");
    stepper_1.step(-3);
    angle_1=95;
  }
  
  if(!digitalRead(input_2)){
    Serial.println("Input_2");
    stepper_2.step(3);
    angle_2=175;
  }
  else if(!digitalRead(input_22)){
    Serial.println("Input_22");
    stepper_2.step(-3);
    angle_2=95;
  }
  
  if(!digitalRead(input_3)){
    Serial.println("Input_3");
    stepper_3.step(3);
    angle_3=175;
  }
  else if(!digitalRead(input_32)){
    Serial.println("Input_32");
    stepper_3.step(-3);
    angle_3=95;
  }
}


