// - Wert -> nach oben

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
#include <Servo.h>
#include <stdlib.h>

#include "S_1.h"
#include "S_2.h"
#include "S_3.h"

// change this to the number of steps on your motor
#define STEPS 800
#define PULSE_PIN_1 37
#define DIRECTION_PIN_1 36
#define PULSE_PIN_2 35
#define DIRECTION_PIN_2 34
#define PULSE_PIN_3 33
#define DIRECTION_PIN_3 32

#define input_1 2    // unten S1
#define input_2 3    // unten S2
#define input_3 4    // unten S3
#define input_12 5    // oben S1
#define input_22 6    // oben S2
#define input_32 7    // oben S3

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

S_1 *s_1 = new S_1();
S_2 *s_2 = new S_2();
S_3 *s_3 = new S_3();

Servo servo_d, servo_h, servo_m, servo_r, servo_k;

int counter = 0;
char n[10];
int numOfFinger = 0;

float actualAngle_1=0, actualAngle_2 = 0, actualAngle_3 = 0, nominalAngle_1=0, nominalAngle_2=0, nominalAngle_3=0, drive_1=0, drive_2=0, drive_3=0;
int x=0, y=0, z=0, daumen=0, hauptfinger=0, mittelfinger=0, ringfinger=0, kleinerfinger=0, winkel=0;
int winkelCounter=3;
float convert = (360.0/(float)(STEPS));

void setup() {
  Serial.begin(9600);

  Serial1.begin(115200);        // The Bluetooth Mate defaults to 115200bps
  delay(320);                     // IMPORTANT DELAY! (Minimum ~276ms)
  Serial1.print("$$$");         // Enter command mode
  delay(120);                      // IMPORTANT DELAY! (Minimum ~10ms)
  Serial1.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  delay(120);
  Serial1.println("---");
  
  servo_d.attach(22);
  servo_h.attach(23);
  servo_m.attach(24);
  servo_r.attach(25);
  servo_k.attach(26);
  
  delay(50);
  
  //servo_d.write(map(daumen,0,1023,89,179));    // keine Zwischenstufen
  servo_h.write(90);
  servo_m.write(90);
  servo_r.write(100);
  servo_k.write(110);  // 120 obere Grenze, 100 untere
  
  Serial1.begin(9600);          // Start bluetooth serial at 9600
  delay(1000);
  
  // set the speed at 60 rpm:
  stepper_1.setSpeed(20);
  stepper_2.setSpeed(20);
  stepper_3.setSpeed(20);
  
  pinMode(input_1, INPUT);
  pinMode(input_2, INPUT);
  pinMode(input_3, INPUT);
  pinMode(input_12, INPUT);
  pinMode(input_22, INPUT);
  pinMode(input_32, INPUT);
  
  pinMode(8, OUTPUT); 
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT); 
  pinMode(11, OUTPUT); 
   
  delay(1000);
  
  stepper_1.step(angleToSteps(-45));
  stepper_2.step(angleToSteps(-45));
  stepper_3.step(angleToSteps(-45));
  
  delay(1000);
}

void loop() {
  
  if(!reference_1 || !reference_2 || !reference_3){
    if(!reference_1){
      if(!digitalRead(input_1)){
        reference_1=true;
        actualAngle_1=95;
        stepper_1.step(angleToSteps(-5));    //wegfahren von Taster
        reference_1=true; 
      }else{
        Serial.println("Fahre runter 1");
        stepper_1.step(1);
      }
    }
    if(!reference_2){
      if(!digitalRead(input_2)){
        reference_2=true;
        actualAngle_2=95;
        stepper_2.step(angleToSteps(-5));
        reference_2=true; 
      }else{
        Serial.println("Fahre runter 2");
        stepper_2.step(1);
      }
    }
    if(!reference_3){ 
      if(!digitalRead(input_3)){
        Serial.println(digitalRead(input_3));
        reference_3=true;
        actualAngle_3=95;
        stepper_3.step(angleToSteps(-5));
        reference_3=true; 
      }else{
        Serial.println("Fahre runter 3");
        stepper_3.step(1);
      }
    }
  }else{
    Serial.println("Messen");
    
    //getData();
    //ausgabe();
    //doRoboterhand();
    doDrive();
    //doCheck();
  }
  delay(50); 
}

void doRoboterhand(){
  //servo_d.write(map(daumen,0,1023,89,179));    // keine Zwischenstufen
  servo_h.write(map(hauptfinger,420,760,85,40));
  servo_m.write(map(mittelfinger,145,610,90,40));
  servo_r.write(map(ringfinger,445,680,100,65));
  servo_k.write(map(kleinerfinger,250,660,110,90));  // 120 obere Grenze, 100 untere 

  if(winkel==0){
    // gegen Uhrzeigersinn
    digitalWrite(8, LOW); 
    digitalWrite(9, HIGH); 
    digitalWrite(10, HIGH); 
    digitalWrite(11, LOW);
    delay(10);
    digitalWrite(8, HIGH); 
    digitalWrite(9, LOW); 
    digitalWrite(10, HIGH); 
    digitalWrite(11, LOW);
    delay(10);
    digitalWrite(8, HIGH); 
    digitalWrite(9, LOW); 
    digitalWrite(10, LOW); 
    digitalWrite(11, HIGH);
    delay(10);
    digitalWrite(8, LOW); 
    digitalWrite(9, HIGH); 
    digitalWrite(10, LOW); 
    digitalWrite(11, HIGH); 
    delay(10);
    
  }else if(winkel==2){
    // im Uhrzeigersinn
    digitalWrite(8, LOW); 
    digitalWrite(9, HIGH); 
    digitalWrite(10, LOW); 
    digitalWrite(11, HIGH); 
    delay(10);
    digitalWrite(8, HIGH); 
    digitalWrite(9, LOW); 
    digitalWrite(10, LOW); 
    digitalWrite(11, HIGH);
    delay(10);
    digitalWrite(8, HIGH); 
    digitalWrite(9, LOW); 
    digitalWrite(10, HIGH); 
    digitalWrite(11, LOW);
    delay(10);
    digitalWrite(8, LOW); 
    digitalWrite(9, HIGH); 
    digitalWrite(10, HIGH); 
    digitalWrite(11, LOW);
    delay(10);
  }
}

void ausgabe(){
  Serial.print(daumen);
  Serial.print('.');
  Serial.print(hauptfinger);
  Serial.print('.');
  Serial.print(mittelfinger);
  Serial.print('.');
  Serial.print(ringfinger);
  Serial.print('.');
  Serial.print(kleinerfinger);
  Serial.print('.');
  Serial.print(x);
  Serial.print('.');
  Serial.print(y);
  Serial.print('.');
  Serial.print(z);
  Serial.print('.');
  Serial.println(winkel);
}

void getData(){
  for(int i=0; i<900; i++){
    if(Serial1.available() && counter <= 9999)  // If the bluetooth sent any characters
    {
      n[counter] = Serial1.read();
      // d...Daumen, h...Hauptfinger, m...Mittelfinger, r...Ringfinger, k...kleiner Finger, x...X-Position, y...Y-Position, z...Z-Position, w...Winkellage
      if(n[counter] != 'd' && n[counter] != 'h' && n[counter] != 'm' && n[counter] != 'r' && n[counter] != 'k' && n[counter] != 'x' && n[counter] != 'y' && n[counter] != 'z' && n[counter] != 'w' && n[counter] != '\0'){
        counter++;
      }else if(n[counter] == '\0'){	//a bunch of \0s is sent at the beginning
        // do nothing
        Serial.println("Nothing");
      }else if(n[counter] == 'd'){
        daumen = atoi(n);
        //Serial.print(daumen);
        //Serial.print('.');
        for(int i = 0; i < 10; i++){
          n[i] = 0;
        }
        counter=0;
      }else if(n[counter] == 'h'){
        hauptfinger = atoi(n);
        //Serial.print(hauptfinger);
        //Serial.print('.');
        for(int i = 0; i < 10; i++){
          n[i] = 0;
        }
        counter=0;
      }else if(n[counter] == 'm'){
        mittelfinger = atoi(n);
        //Serial.print(mittelfinger);
        //Serial.print('.');
        for(int i = 0; i < 10; i++){
          n[i] = 0;
        }
        counter=0;
      }else if(n[counter] == 'r'){
        ringfinger = atoi(n);
        //Serial.print(ringfinger);
        //Serial.print('.');
        for(int i = 0; i < 10; i++){
          n[i] = 0;
        }
        counter=0;
      }else if(n[counter] == 'k'){
        kleinerfinger = atoi(n);
        //Serial.print(kleinerfinger);
        //Serial.print('.');
        for(int i = 0; i < 10; i++){
          n[i] = 0;
        }
        counter=0;
      }else if(n[counter] == 'x'){
        x = atoi(n);
        //Serial.print(x);
        //Serial.print('.');
        for(int i = 0; i < 10; i++){
          n[i] = 0;
        }
        counter=0;
      }else if(n[counter] == 'y'){
        y = atoi(n);
        //Serial.print(y);
        //Serial.print('.');
        for(int i = 0; i < 10; i++){
          n[i] = 0;
        }
        counter=0;
      }else if(n[counter] == 'z'){
        z = atoi(n);
        //Serial.print(z);
        //Serial.print('.');
        for(int i = 0; i < 10; i++){
          n[i] = 0;
        }
        counter=0;
      }else if(n[counter] == 'w'){
        winkel = atoi(n);
        //Serial.print(winkel);
        //Serial.println("");
        for(int i = 0; i < 10; i++){
          n[i] = 0;
        }
        counter=0;
        return;
      }
    }
  }
}


void doDrive(){
  y=0; z=550; x+=10;
  if(x>100) x=0;
  
  nominalAngle_1 = s_1->S1(x, y, z);
  nominalAngle_2 = s_2->S2(x, y, z);
  nominalAngle_3 = s_3->S3(x, y, z);
  
  
  Serial.print(nominalAngle_1);
  Serial.print('\t');
  Serial.print(nominalAngle_2);
  Serial.print('\t');
  Serial.print(nominalAngle_3);
  Serial.print('\t');
  Serial.print(actualAngle_1);
  Serial.print('\t');
  Serial.print(actualAngle_2);
  Serial.print('\t');
  Serial.print(actualAngle_3);
  Serial.print('\t');
  
  drive_1 = (-1)*(nominalAngle_1 - actualAngle_1);
  drive_2 = (-1)*(nominalAngle_2 - actualAngle_2);
  drive_3 = (-1)*(nominalAngle_3 - actualAngle_3);
  
  drive_1=angleToSteps(drive_1);
  drive_2=angleToSteps(drive_2);
  drive_3=angleToSteps(drive_3);
  
  Serial.print(drive_1);
  Serial.print('\t');
  Serial.print(drive_2);
  Serial.print('\t');
  Serial.print(drive_3);
  Serial.println("");
  
  
  stepper_1.step((int)(drive_1));
  stepper_2.step((int)(drive_2));
  stepper_3.step((int)(drive_3));
  
  delay(100);
  
  Serial.print(stepsToAngle(drive_1));
  Serial.print('\t');
  Serial.print(stepsToAngle(drive_2));
  Serial.print('\t');
  Serial.print(stepsToAngle(drive_3));
  Serial.println("");

  actualAngle_1 = actualAngle_1-(stepsToAngle(drive_1));
  actualAngle_2 = actualAngle_2-(stepsToAngle(drive_2));
  actualAngle_3 = actualAngle_3-(stepsToAngle(drive_3));
}

float angleToSteps(float angle){
  float steps = (float)(angle/convert);
  return steps;
}

float stepsToAngle(int steps){
  float angle = float(steps*convert);
  return angle;
}

void doCheck(){
  if(!digitalRead(input_1)){
    Serial.println("Input_1");
    stepper_1.step(angleToSteps(-5));
    actualAngle_1=95;
  }
  else if(!digitalRead(input_12)){
    Serial.println("Input_12");
    stepper_1.step(angleToSteps(5));
    actualAngle_1=175;
  }
  
  if(!digitalRead(input_2)){
    Serial.println("Input_2");
    stepper_2.step(angleToSteps(-5));
    actualAngle_2=95;
  }
  else if(!digitalRead(input_22)){
    Serial.println("Input_22");
    stepper_2.step(angleToSteps(5));
    actualAngle_2=175;
  }
  
  if(!digitalRead(input_3)){
    Serial.println("Input_3");
    stepper_3.step(angleToSteps(-5));
    actualAngle_3=95;
  }
  else if(!digitalRead(input_32)){
    Serial.println("Input_32");
    stepper_3.step(angleToSteps(5));
    actualAngle_3=175;
  }
}


