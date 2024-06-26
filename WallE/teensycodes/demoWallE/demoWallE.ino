#include "pinsWallE.h"
#include <Stepper.h>
#include <Servo.h>

// Variables
String id;  int errorX = 1000; int errorZ = 1000; int angle; String dir; String color;
String dataRasp; String stringRasp; String movements; String idbox;
String initialPosition; int dirBox;
int wSpeed; int lineSensors; int flag = 0; float waitTime; int flagStart = 0;
long revolutions = 0; long lastPosition; int currentMillis;

// Objects
Servo servoGripper;

void setup() {
  // Serial initialization
  Serial.begin(9600); 
  Serial.setTimeout(100);
  
   // Define pin modes
  pinMode(sensorL1,INPUT); pinMode(sensorL2,INPUT); pinMode(sensorL3,INPUT);
  pinMode(limitSwitchT,INPUT); pinMode(limitSwitchB ,INPUT); 

  pinMode(wheelLFpwm, OUTPUT);  pinMode(wheelRFpwm, OUTPUT);
  pinMode(wheelLBpwm, OUTPUT);  pinMode(wheelRBpwm, OUTPUT);
  pinMode(wheelLFp, OUTPUT);  pinMode(wheelLFn, OUTPUT);
  pinMode(wheelRFp, OUTPUT);  pinMode(wheelRFn, OUTPUT);
  pinMode(wheelLBp, OUTPUT);  pinMode(wheelLBn, OUTPUT);
  pinMode(wheelRBp, OUTPUT);  pinMode(wheelRBn, OUTPUT);
  pinMode(standby, OUTPUT);  
  pinMode(stepPin,OUTPUT); pinMode(dirPin,OUTPUT); pinMode(enPin,OUTPUT);


  servoGripper.attach(pinGripper);
  servoGripper.write(0);
  gripperDown();
  stopMoving();
  digitalWrite(standby, HIGH);
  delay(3000);
}


void loop() {
     while (Serial.available() == 0) { }

    // Turn until it finds a box
    while (id == "NOLABEL"){
            currentMillis = millis();
            while (millis() - currentMillis <= 2500) {
            stringRasp = Serial.readStringUntil('\n');
            separateData(stringRasp);
            delay(1);
            Serial.flush();
            if (id != "NOLABEL"){
              break;
            }
            rotateLeft();
            delay(100);
            stopMoving();
          }
    }
    // Save ID of detected box
    idbox = id;
    // Stop moving once it finds a box
    stopMoving();
    delay(2000);
    
    // Move to pick up the box
    // ** Uses the last detected errorX to move and center the box
    waitTime = errorX*10;
    int currentMillis = millis();
    while (millis() - currentMillis <= waitTime) {
        if (errorX > 0){
           moveRight(60); 
        }
       else if (errorX < 0) {
           moveLeft(60);
       }
    }
    stopMoving();
     // ** Uses last errorZ measurement to move forward
     waitTime = errorZ * 1000;
     float waitZ = waitTime;
       currentMillis = millis();      
     while (millis() - currentMillis <= waitTime) {
         moveForward(60);
     }
     stopMoving();
     delay(2000);

    // Closes gripper
     servoGripper.write(80);
     delay(1500);
     // Raises gripper
     digitalWrite(enPin,LOW);
     digitalWrite(dirPin,LOW);          // LOW is upwards
     for(int x = 0; x < 2000; x++) {   
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(500);
        if (digitalRead(limitSwitchT)==LOW){
          break
        }
       }
      digitalWrite(enPin,HIGH);      

      // Return to original spot
     currentMillis = millis();      
     while (millis() - currentMillis <= waitZ) {
         moveBackwards(60);
     }
     stopMoving();
     delay(2000);

     // Turn to find North / straighten
    
 }
