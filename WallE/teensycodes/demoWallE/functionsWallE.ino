/* 
~~ Functions Wall-E LARC ~~
CDR SLP 2024
*/

// Separate Serial data
void separateData(String dataStr){
  String data1; String data2; String data3; String data4; String data5;
  int firstCommaIndex = dataStr.indexOf(',');
  int secondCommaIndex = dataStr.indexOf(',', firstCommaIndex + 1);
  int thirdCommaIndex = dataStr.indexOf(',', secondCommaIndex + 1);
  int fourthCommaIndex = dataStr.indexOf(',', thirdCommaIndex + 1);

  if (firstCommaIndex != -1 && secondCommaIndex != -1 && thirdCommaIndex != -1 && fourthCommaIndex != -1) {
      data1 = dataStr.substring(0, firstCommaIndex);
      data2 = dataStr.substring(firstCommaIndex + 1, secondCommaIndex);
      data3 = dataStr.substring(secondCommaIndex + 1, thirdCommaIndex); 
      data4 = dataStr.substring(thirdCommaIndex + 1, fourthCommaIndex); 
      data5 = dataStr.substring(fourthCommaIndex + 1); 
    } 
    errorX = data1.toInt();
    errorZ = data2.toInt();
    dir = data3;
    id = data4;
    color = data5;
}

 // Reset Data
 void resetData(){
  errorX = 0; errorZ = 0;
  }

// Read line sensors
int readLineSensors(){
   int valLineSensors = 0;
   if (digitalRead(sensorL1) == HIGH){
      valLineSensors = valLineSensors+100;
    }
    if (digitalRead(sensorL2)  == HIGH){
      valLineSensors = valLineSensors+10;
    }
    if (digitalRead(sensorL3) == HIGH){
      valLineSensors = valLineSensors+1;
    }
   return valLineSensors;
  }

// Read ultrasonic sensors
float readDistance(){
  float dur1; float dur2; float dist;
  digitalWrite(sensorULTrig, HIGH);
  delay(1);
  digitalWrite(sensorULTrig,LOW);
  dur1 = pulseIn(sensorULEcho, HIGH);
  digitalWrite(sensorURTrig, HIGH);
  delay(1);
  digitalWrite(sensorURTrig,LOW);
  dur2 = pulseIn(sensorUREcho, HIGH);
  dist = ((dur1 * 0.034 / 2)+(dur2*0.034 / 2)/2); // Avg of both
  return dist;
}


// Gripper movement
void gripperUp(int level){
    digitalWrite(enPin,LOW);
    digitalWrite(dirPin,LOW);          // LOW is upwards
      if (level == 0){
         for(int x = 0; x < 950; x++) {  
              Serial.println("up");
              digitalWrite(stepPin,HIGH);
              delayMicroseconds(500);
              digitalWrite(stepPin,LOW);
              delayMicroseconds(500);
              if (digitalRead(limitSwitchT) == LOW){ 
                break;
              }
         }
      }
      else if (level == 1){
         for(int x = 0; x < 13500; x++) {   // Ground to second
              digitalWrite(stepPin,HIGH);
              delayMicroseconds(500);
              digitalWrite(stepPin,LOW);
              delayMicroseconds(500);
              if (digitalRead(limitSwitchT) == LOW){ 
                break;
              }
         }
       }
       else if (level == 2){
           while(digitalRead(limitSwitchT) == HIGH){
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(500); 
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(500); 
          }
          for (int x = 0; x < 1700; x++){
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(500); 
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(500);
             if (digitalRead(limitSwitchT) == LOW){ 
                break;
             } 
        }
       }
     digitalWrite(enPin,HIGH);
 }  

 void gripperDown(){
       digitalWrite(enPin,LOW);
       digitalWrite(dirPin,HIGH);          // HIGH is downwards
       while(digitalRead(limitSwitchB) == HIGH){
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(500); 
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(500); 
       }
         for (int x = 0; x < 600; x++){
            digitalWrite(stepPin,HIGH); 
            delayMicroseconds(500); 
            digitalWrite(stepPin,LOW); 
            delayMicroseconds(500); 
            if (digitalRead(limitSwitchB) == LOW){ 
                break;
            } 
        }
        digitalWrite(enPin,HIGH);
  }
 
// Movement
void moveForward(int wheelSpeed) {
  analogWrite(wheelLFpwm, 1.13* wheelSpeed);
  analogWrite(wheelRFpwm, wheelSpeed);
  analogWrite(wheelLBpwm, 1.13 * wheelSpeed);
  analogWrite(wheelRBpwm, wheelSpeed);
  
  digitalWrite(wheelLFp, HIGH);   digitalWrite(wheelLFn, LOW);
  digitalWrite(wheelRFp, HIGH);   digitalWrite(wheelRFn, LOW);
  digitalWrite(wheelLBp, HIGH);   digitalWrite(wheelLBn, LOW);
  digitalWrite(wheelRBp, HIGH);   digitalWrite(wheelRBn, LOW);
}

void moveBackwards(int wheelSpeed) {
  analogWrite(wheelLFpwm, 1.13* wheelSpeed);
  analogWrite(wheelRFpwm, wheelSpeed);
  analogWrite(wheelLBpwm, 1.13 * wheelSpeed);
  analogWrite(wheelRBpwm, wheelSpeed);
  
  digitalWrite(wheelLFp, LOW);   digitalWrite(wheelLFn, HIGH);
  digitalWrite(wheelRFp, LOW);   digitalWrite(wheelRFn, HIGH);
  digitalWrite(wheelLBp, LOW);   digitalWrite(wheelLBn, HIGH);
  digitalWrite(wheelRBp, LOW);   digitalWrite(wheelRBn, HIGH);
}

void moveRight(int wheelSpeed) {
  analogWrite(wheelLFpwm, 1.05* wheelSpeed);
  analogWrite(wheelRFpwm, wheelSpeed);
  analogWrite(wheelLBpwm, 1.1 * wheelSpeed);
  analogWrite(wheelRBpwm, wheelSpeed);
  
  digitalWrite(wheelLFp, HIGH);   digitalWrite(wheelLFn, LOW);
  digitalWrite(wheelRFp, LOW);   digitalWrite(wheelRFn, HIGH);
  digitalWrite(wheelLBp, LOW);   digitalWrite(wheelLBn, HIGH);
  digitalWrite(wheelRBp, HIGH);   digitalWrite(wheelRBn, LOW);
}

void moveLeft(int wheelSpeed) {
  analogWrite(wheelLFpwm, 1* wheelSpeed);
  analogWrite(wheelRFpwm, 1.05*wheelSpeed);
  analogWrite(wheelLBpwm, 1.5 * wheelSpeed);
  analogWrite(wheelRBpwm, wheelSpeed);
  
  digitalWrite(wheelLFp, LOW);   digitalWrite(wheelLFn, HIGH);
  digitalWrite(wheelRFp, HIGH);   digitalWrite(wheelRFn, LOW);
  digitalWrite(wheelLBp, HIGH);   digitalWrite(wheelLBn, LOW);
  digitalWrite(wheelRBp, LOW);   digitalWrite(wheelRBn, HIGH);
}

void rotateLeft(int wheelSpeed) {
  analogWrite(wheelLFpwm, 1.13* wheelSpeed);
  analogWrite(wheelRFpwm, wheelSpeed);
  analogWrite(wheelLBpwm, 1.13 * wheelSpeed);
  analogWrite(wheelRBpwm, wheelSpeed);
  
  digitalWrite(wheelLFp, LOW);   digitalWrite(wheelLFn, HIGH);
  digitalWrite(wheelRFp, HIGH);   digitalWrite(wheelRFn, LOW);
  digitalWrite(wheelLBp, LOW);   digitalWrite(wheelLBn, HIGH);
  digitalWrite(wheelRBp, HIGH);   digitalWrite(wheelRBn, LOW);
}

void rotateRight(int wheelSpeed) {
  analogWrite(wheelLFpwm, 1.13* wheelSpeed);
  analogWrite(wheelRFpwm, wheelSpeed);
  analogWrite(wheelLBpwm, 1.13 * wheelSpeed);
  analogWrite(wheelRBpwm, wheelSpeed);
  
  digitalWrite(wheelLFp, HIGH);   digitalWrite(wheelLFn, LOW);
  digitalWrite(wheelRFp, LOW);   digitalWrite(wheelRFn, HIGH);
  digitalWrite(wheelLBp, HIGH);   digitalWrite(wheelLBn, LOW);
  digitalWrite(wheelRBp, LOW);   digitalWrite(wheelRBn, HIGH);
}

void diagonalLeftForward(int wheelSpeed) {
  analogWrite(wheelLFpwm, 0);
  analogWrite(wheelRFpwm, wheelSpeed);
  analogWrite(wheelLBpwm, wheelSpeed);
  analogWrite(wheelRBpwm, 0);
  
  digitalWrite(wheelLFp, LOW);   digitalWrite(wheelLFn, LOW);
  digitalWrite(wheelRFp, HIGH);   digitalWrite(wheelRFn, LOW);
  digitalWrite(wheelLBp, HIGH);   digitalWrite(wheelLBn, LOW);
  digitalWrite(wheelRBp, LOW);   digitalWrite(wheelRBn, LOW);
}

void diagonalRightForward(int wheelSpeed) {
  analogWrite(wheelLFpwm, wheelSpeed);
  analogWrite(wheelRFpwm, 0);
  analogWrite(wheelLBpwm, 0);
  analogWrite(wheelRBpwm, wheelSpeed);
  
  digitalWrite(wheelLFp, HIGH);   digitalWrite(wheelLFn, LOW);
  digitalWrite(wheelRFp, LOW);   digitalWrite(wheelRFn, LOW);
  digitalWrite(wheelLBp, LOW);   digitalWrite(wheelLBn, LOW);
  digitalWrite(wheelRBp, HIGH);   digitalWrite(wheelRBn, LOW);
}

void diagonalLeftBackward(int wheelSpeed) {
  analogWrite(wheelLFpwm, wheelSpeed);
  analogWrite(wheelRFpwm, 0);
  analogWrite(wheelLBpwm, 0);
  analogWrite(wheelRBpwm, wheelSpeed);
  
  digitalWrite(wheelLFp, LOW);   digitalWrite(wheelLFn, HIGH);
  digitalWrite(wheelRFp, LOW);   digitalWrite(wheelRFn, LOW);
  digitalWrite(wheelLBp, LOW);   digitalWrite(wheelLBn, LOW);
  digitalWrite(wheelRBp, LOW);   digitalWrite(wheelRBn, HIGH);
}

void diagonalRightBackward(int wheelSpeed) {
  analogWrite(wheelLFpwm, 0);
  analogWrite(wheelRFpwm, wheelSpeed);
  analogWrite(wheelLBpwm, wheelSpeed);
  analogWrite(wheelRBpwm, 0);
  
  digitalWrite(wheelLFp, LOW);   digitalWrite(wheelLFn, LOW);
  digitalWrite(wheelRFp, LOW);   digitalWrite(wheelRFn, HIGH);
  digitalWrite(wheelLBp, LOW);   digitalWrite(wheelLBn, HIGH);
  digitalWrite(wheelRBp, LOW);   digitalWrite(wheelRBn, LOW);
}

void stopMoving() {
  analogWrite(wheelLFpwm, 0);
  analogWrite(wheelRFpwm, 0);
  analogWrite(wheelLBpwm, 0);
  analogWrite(wheelRBpwm, 0);
  
  digitalWrite(wheelLFp, LOW);   digitalWrite(wheelLFn, LOW);
  digitalWrite(wheelRFp, LOW);   digitalWrite(wheelRFn, LOW);
  digitalWrite(wheelLBp, LOW);   digitalWrite(wheelLBn, LOW);
  digitalWrite(wheelRBp, LOW);   digitalWrite(wheelRBn, LOW);
}

void Final(){
    stopMoving();
}
