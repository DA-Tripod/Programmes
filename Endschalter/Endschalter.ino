#define input_1 2
#define input_2 3
#define input_3 4
#define input_4 5
#define input_5 6
#define input_6 7

boolean reference_1 = false;
boolean reference_2 = false;
boolean reference_3 = false;
boolean reference_4 = false;
boolean reference_5 = false;
boolean reference_6 = false;

void setup() {
  Serial.begin(9600);
  delay(1000);
  attachInterrupt(input_1, doReference_1, FALLING);
  attachInterrupt(input_2, doReference_2, FALLING);
  attachInterrupt(input_3, doReference_3, FALLING);
  attachInterrupt(input_4, doReference_4, FALLING);
  attachInterrupt(input_5, doReference_5, FALLING);
  attachInterrupt(input_6, doReference_6, FALLING);
  delay(1000);
}

void loop() {
  // wenn Taster offen -> liefert HIGH am Eingang
  if(!reference_1 || !reference_2 || !reference_3 || !reference_4 || !reference_5 || !reference_6){
    if(!reference_1){
      Serial.println("Fahre hoch 1");
    }
    if(!reference_2){
      Serial.println("Fahre hoch 2");
    }
    if(!reference_3){
      Serial.println("Fahre hoch 3");
    }
  if(!reference_4){
      Serial.println("Fahre hoch 4");
    }
    if(!reference_5){
      Serial.println("Fahre hoch 5");
    }
    if(!reference_6){
      Serial.println("Fahre hoch 6");
    }  
  }else{
    Serial.println("Messen");
  }
  delay(100);  
  Serial.println("");
}

void doReference_1(){
  if(!reference_1 && millis()>5000){
    reference_1 = true;
  }
  Serial.println("Fahre runter 1");
}

void doReference_2(){
  if(!reference_2 && millis()>5000){
    reference_2 = true;
  }
  Serial.println("Fahre runter 2");
}

void doReference_3(){
  if(!reference_3 && millis()>5000){
    reference_3 = true;
  }
  Serial.println("Fahre runter 3");
}

void doReference_4(){
  if(!reference_4 && millis()>5000){
    reference_4 = true;
  }
  Serial.println("Fahre runter 3");
}

void doReference_5(){
  if(!reference_5 && millis()>5000){
    reference_5 = true;
  }
  Serial.println("Fahre runter 3");
}

void doReference_6(){
  if(!reference_6 && millis()>5000){
    reference_6 = true;
  }
  Serial.println("Fahre runter 3");
}
