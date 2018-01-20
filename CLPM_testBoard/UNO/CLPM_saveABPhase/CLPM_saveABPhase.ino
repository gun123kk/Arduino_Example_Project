#include <Wire.h>
const byte encoderAPhase = 2 ;    //interrupt pin detect encoder A phase
const byte encoderBPhase = 3 ;    //interrupt pin detect encoder B phase
int ABPCounter=0;
byte  APstatus = 0;
byte  BPstatus = 0;
int receiveStep = 0;
int sendStepData= 0;
void setup() {
   Serial.begin(9600);
   Wire.begin(2);
   Wire.onRequest(requestEvent);
  pinMode(encoderAPhase, INPUT_PULLUP);
  pinMode(encoderBPhase, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderAPhase), detectABPhase, CHANGE );
  attachInterrupt(digitalPinToInterrupt(encoderBPhase), detectABPhase, CHANGE );
}

void loop() {
  sendStepData=receiveStep;
  if(receiveStep>=1001){
    //Serial.print(receiveStep);
    //Serial.println(F(" STEP"));
    receiveStep=0;
  }
}

//====================================
//interrupt detectABPhase
//====================================
void detectABPhase() {
  noInterrupts();
  
  APstatus = digitalRead(encoderAPhase);
  BPstatus = digitalRead(encoderBPhase);  
  
     if (APstatus == 0 && BPstatus == 0 && ABPCounter == 0) {
      ABPCounter = 1;
    } else if (APstatus == 0 && BPstatus == 1 && ABPCounter == 1) {
      ABPCounter = 2;
    } else if (APstatus == 1 && BPstatus == 1 && ABPCounter == 2) {
      ABPCounter = 3;
    } else if (APstatus ==1 && BPstatus == 0 && ABPCounter == 3) {
      ABPCounter = 4;
      receiveStep++;
      ABPCounter = 0;
    }
  interrupts();
}

void requestEvent(){    
    byte dd[2];
    dd[0]=sendStepData/256;
    dd[1]=sendStepData % 256;
    Wire.write(dd[0]);
    Wire.write(dd[1]);      
  //Wire.write("hello "); 
}
//=============================
