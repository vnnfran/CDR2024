/*
  ~~~~~ Main Wall-E LARC ~~~~~
                CDR SLP 2024

  Make sure the documents  "mainWallE", "functionsWallE" and "pinsWallE"
  are in the same folder ("mainWallE") as to call functions and pins  -Van :)
*/

#include "pinsWallE.h"
#include <Servo.h>
#include <Stepper.h>

// Variables
int wheelSpeed; int moveY; int moveX; int moveGripper; int turns;
bool servoSwitch; bool stopSwitch; String state;

// Objects
Servo servoGripper;

void setup() {
  // Serial initialization
  Serial.begin(9600);

  // Define pin modes
  pinMode(CH1,INPUT); pinMode(CH2,INPUT); pinMode(CH3,INPUT);
  pinMode(CH4,INPUT); pinMode(CH5,INPUT); pinMode(CH6,INPUT);
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
  digitalWrite(standby, HIGH); 

  delay(250);
}


void loop() {
  
  // Reads channels of RC Controller
  // ** Multiplied by 0.4 to limit speed (255 -> 100)
  turns = int(readChannel(CH1, -255, 255, 0) * 0.5);
  moveGripper = int(readChannel(CH2, -255, 255, 0) * 0.5);
  moveY = int(readChannel(CH3, -255, 255, 0) * 0.5);
  moveX = int(readChannel(CH4, -255, 255, 0) * 0.5);
  stopSwitch = readSwitch(CH5, false);
  servoSwitch = readSwitch(CH6, false);
   
  while (stopSwitch == true){

    // Reads channels of RC Controller
    // ** Multiplied by 0.4 to limit speed (255 -> 100)
    turns = int(readChannel(CH1, -255, 255, 0) * 0.5);
    moveGripper = int(readChannel(CH2, -255, 255, 0) * 0.5);
    moveY = int(readChannel(CH3, -255, 255, 0) * 0.5);
    moveX = int(readChannel(CH4, -255, 255, 0) * 0.5);
    stopSwitch = readSwitch(CH5, false);
    servoSwitch = readSwitch(CH6, false);
   
    
    // Forward - backwards movement
    if (moveY > 15){
      moveForward(moveY);
      state = "Forward";
    }
    else if (moveY < -15){
      moveBackwards(-moveY);
      state = "Backwards";
    }
    
    // Left-right movement
    else if (moveX > 15){
      moveRight(moveX);
      state = "Moving Right";
    }
     else if (moveX < -15){
      moveLeft(-moveX);
      state = "Moving Left";
    }

    // Diagonal movement
    else if (moveY > 15 && moveX > 15){
      diagonalRightForward(moveX);
      state = "Diag Fwd Right";
    }
     else if (moveY > 15 && moveX < -15){
      diagonalLeftForward(-moveX);
      state = "Diag Fwd Left";
    }

    // Tank-type turns
     else if (turns > 15){
      rotateRight(turns);
      state = "Turning Right";
    }
     else if (turns < -15){
      rotateLeft(-turns);
      state = "Turning Left";
    }

     // Raise-lower gripper
     else if (state == "Stopped" && moveGripper < -15){
      digitalWrite(enPin,LOW);
      digitalWrite(dirPin,HIGH);          // LOW is upwards
     for(int x = 0; x < 1000; x++) {   
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(500);
       }
      state = "Raising gripper";
    }
     else if (state == "Stopped" && moveGripper > 15){
      digitalWrite(enPin,LOW);
      digitalWrite(dirPin,LOW);          // LOW is upwards
     for(int x = 0; x < 1000; x++) {   
        digitalWrite(stepPin,HIGH);
        delayMicroseconds(500);
        digitalWrite(stepPin,LOW);
        delayMicroseconds(500);
       }     
      state = "Lowering gripper";
    }

    // Open-close gripper
    else if (state == "Stopped" && servoSwitch == false){
      servoGripper.write(0);
    }
    else if (state == "Stopped" && servoSwitch == true){
      servoGripper.write(80);
    }
    
    else {
      stopMoving();
      digitalWrite(enPin,HIGH);
      state = "Stopped"; 
    }

    Serial.println(state);
    delay(100);
  }
  
  stopMoving();
  digitalWrite(enPin,HIGH);
  Serial.println("Emergency break");
  delay(250);

}
