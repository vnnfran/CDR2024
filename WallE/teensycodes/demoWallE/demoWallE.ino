/*
  ~~~~~ Demo Wall-E LARC ~~~~~
  CDR SLP 2024

  Make sure the documents  "demoWallE", "functionsWallE" and "pinsWallE"
  are in the same folder ("demoWallE") as to call functions and pins  -Van :)

  This is a DRAFT of a code made for the Cummins Demo, considering the robot is fully
  autonomous (IMU + ML model + line sensors + encoders)
*/

#include "pinsWallE.h"
#include <Stepper.h>
#include <Servo.h>

// Variables
// Errors begin as large numbers as 0 would indicate object is centered in camera
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

  // Attaches pin to object & opens gripper
  servoGripper.attach(pinGripper);
  servoGripper.write(0);
  // Lower the gripper and stop moving
  gripperDown();
  stopMoving();
  // Pin to HIGH to deactivate stepper motor
  digitalWrite(standby, HIGH);
  delay(3000);
}


void loop() {
    // Loop until serial communication w Raspberry is established
    while (Serial.available() == 0) { }

    // While no box is found, turn left
    while (id == "NOLABEL"){
      // Read serial for 2.5 seconds
      // When reading serial, don't use delays, use loop measuring millis
      currentMillis = millis();
      while (millis() - currentMillis <= 2500) {
        stringRasp = Serial.readStringUntil('\n');
        separateData(stringRasp);
        delay(1);
        Serial.flush();
        // If box is found, break loop before moving
        if (id != "NOLABEL"){
          break;
        }
        // Rotate left and stop
        rotateLeft();
        delay(100);
        stopMoving();
      }
    }

    // Save ID of detected box
    idbox = id;
    // Stop moving once it finds a box (redundant)
    stopMoving();
    delay(2000);
    
    // Move to pick up the box
    // Uses the last detected errorX to move and center the box
    // Adjust this value to improve precision
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
    // Uses last errorZ measurement to move forward
    // The value is a ratio w time taken to move one square of field
    // Adjust this value to improve precision
    waitTime = errorZ * 1000;
    float waitZ = waitTime;
    currentMillis = millis();      
    while (millis() - currentMillis <= waitTime) {
      moveForward(60);
    }
    stopMoving();
    delay(2000);

    // At this point, robot has turned until finding box, centered in X, approached in Y
    // Box should be right inside the gripper

    // Closes gripper
    servoGripper.write(80);
    delay(1500);
    // Raises gripper a little bit so box does not drag on floor
    digitalWrite(enPin,LOW);           // LOW activates stepper motor
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
    digitalWrite(enPin,HIGH);          // HIGH deactivates stepper motor

    // Move backwards and return to original spot
    currentMillis = millis();      
    while (millis() - currentMillis <= waitZ) {
      moveBackwards(60);
    }
    stopMoving();
    delay(2000);

    // Turn to find North / straighten
    
 }
