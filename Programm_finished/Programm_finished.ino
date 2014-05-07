// R...V...O

#include <NewPing.h>
#include <SoftwareSerial.h>  
#include "Wire.h"
#include "ADXL345.h"

#define TRIGGER_PIN_1  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define TRIGGER_PIN_2  6
#define TRIGGER_PIN_3  8
#define ECHO_PIN_1     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define ECHO_PIN_2     7
#define ECHO_PIN_3     9
#define MAX_DISTANCE   200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.


ADXL345 Accel;

int bluetoothTx = 12;  // TX-O pin of bluetooth mate, Arduino Micro D12
int bluetoothRx = 11;  // RX-I pin of bluetooth mate, Arduino Micro D11

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
NewPing sonar_1(TRIGGER_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonar_2(TRIGGER_PIN_2, ECHO_PIN_2, MAX_DISTANCE); 
NewPing sonar_3(TRIGGER_PIN_3, ECHO_PIN_3, MAX_DISTANCE);

int x=0;
int y=0;
int z=0;
int d=0;
int h=0;
int m=0;
int r=0;
int k=0;
int w=1;

float acc_data[3];

unsigned int uS_1; // Send ping, get ping time in microseconds (uS).
unsigned int uS_2;
unsigned int uS_3;

void setup()
{
   Serial.begin(9600);
   Wire.begin();
   delay(20);
   Accel.init(ADXL345_ADDR_ALT_LOW);
   Accel.set_bw(ADXL345_BW_12);
   delay(20);
   
   bluetooth.begin(115200);        // The Bluetooth Mate defaults to 51300bps
   delay(330);                     // IMPORTANT DELAY! (Minimum ~276ms)
   bluetooth.print("$$$");         // Enter command mode
   delay(100);                      // IMPORTANT DELAY! (Minimum ~10ms)
   bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
   bluetooth.println("---");
   bluetooth.begin(9600);          // Start bluetooth serial at 9600
   delay(300);
}

void loop()
{
  Accel.get_Gxyz(acc_data);
  
  d=analogRead(4);
  h=analogRead(3);
  m=analogRead(2);
  r=analogRead(1);
  k=analogRead(0);
    
  // angle too high -> do not measure ultrasonic
  if(acc_data[0]>0.75){ 
    w=2;
  }
  // angle too low -> do not measure ultrasonic
  else if(acc_data[0]<(-0.75)){
    w=0;
  }
  // angle alright -> measure ultrasonic
  else{
    w=1;
    
    uS_1 = sonar_1.ping();
    uS_2 = sonar_2.ping();
    uS_3 = sonar_3.ping();
    
    x=25-(uS_1/US_ROUNDTRIP_CM);
    y=(25-(uS_2/US_ROUNDTRIP_CM))*(-1);
    z=15-(uS_3/US_ROUNDTRIP_CM);
  }
  
  Serial.print(d);
  delay(5);
  Serial.print('\t');  //daumen
  delay(5);
  Serial.print(h);
  delay(5);
  Serial.print('\t');  //hauptfinger/zeigefinger
  delay(5);
  Serial.print(m);
  delay(5);
  Serial.print('\t');  //mittelfinger
  delay(5);
  Serial.print(r);
  delay(5);
  Serial.print('\t');  //ringfinger
  delay(5);
  Serial.print(k);
  delay(5);
  Serial.print('\t');  //kleiner finger
  delay(5);
  Serial.print(x);
  delay(5);
  Serial.print('\t');  //x Koordinate (Ort)
  delay(5);
  Serial.print(y);
  delay(5);
  Serial.print('\t');  //y Koordinate (Ort)
  delay(5);
  Serial.print(z);
  delay(5);
  Serial.print('\t');  //z Koordinate (Ort)
  delay(5);
  Serial.print(w);
  delay(5);
  Serial.println('\t');  //Winkel/Drehung der Hand
  delay(5);
  
  /*bluetooth.print(d);
  delay(5);
  bluetooth.print('d');  //daumen
  delay(5);
  bluetooth.print(h);
  delay(5);
  bluetooth.print('h');  //hauptfinger/zeigefinger
  delay(5);
  bluetooth.print(m);
  delay(5);
  bluetooth.print('m');  //mittelfinger
  delay(5);
  bluetooth.print(r);
  delay(5);
  bluetooth.print('r');  //ringfinger
  delay(5);
  bluetooth.print(k);
  delay(5);
  bluetooth.print('k');  //kleiner finger
  delay(5);
  bluetooth.print(x);
  delay(5);
  bluetooth.print('x');  //x Koordinate (Ort)
  delay(5);
  bluetooth.print(y);
  delay(5);
  bluetooth.print('y');  //y Koordinate (Ort)
  delay(5);
  bluetooth.print(z);
  delay(5);
  bluetooth.print('z');  //z Koordinate (Ort)
  delay(5);
  bluetooth.print(w);
  delay(5);
  bluetooth.print('w');  //Winkel/Drehung der Hand
  delay(5);*/  
}
