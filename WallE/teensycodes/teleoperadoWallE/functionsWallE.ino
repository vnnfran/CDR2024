/* 
~~ Functions Wall-E LARC ~~
                  CDR SLP 2024
*/

// Read the number of a specified channel and convert to the range provided.
// If the channel is off, return the default value
int readChannel(int channelInput, int minLimit, int maxLimit, int defaultValue){
  int ch = pulseIn(channelInput, HIGH, 35000);
  if (ch < 100) return defaultValue;
  return map(ch, 1000, 2000, minLimit, maxLimit);
}

// Read the switch channel and return a boolean value
bool readSwitch(byte channelInput, bool defaultValue){
  int intDefaultValue = (defaultValue)? 100: 0;
  int ch = readChannel(channelInput, 0, 100, intDefaultValue);
  return (ch > 50);
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
