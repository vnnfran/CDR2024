// Define Input Connections
#define CH1 2
#define CH2 6
#define CH3 10
#define CH4 11
#define CH5 12
#define CH6 13

// Define motor control pins
const int motorA1 = 5; // Motor A control pin 1
const int motorA2 = 4; // Motor A control pin 2
const int motorB1 = 7; // Motor B control pin 1
const int motorB2 = 8; // Motor B control pin 2
const int pwmA = 3;
const int pwmB = 9;

// Integers to represent values from sticks and pots
int ch1Value;
int ch2Value;
int ch3Value;
int ch4Value; 
int ch5Value;

// Boolean to represent switch value
bool ch6Value;

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

void moveForward(int speedf) {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(pwmA, int(speedf*0.92));
  analogWrite(pwmB, int(speedf*0.95));

  Serial.println("Forward");
}

void moveBackward(int speedf) {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(pwmA, int(speedf*0.92));
  analogWrite(pwmB, int(speedf*0.95));
  Serial.println("Backwards");
}

void turnLeft(int speedfwd, int speedturn) {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  analogWrite(pwmA, int(speedfwd*0.92) - (speedturn * 0.15));
  analogWrite(pwmB, int(speedfwd*0.95));
  Serial.println("turnLeft");
}

void turnRight(int speedfwd, int speedturn) {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(pwmA, int(speedfwd*0.92));
  analogWrite(pwmB, int(speedfwd*0.95) - (speedturn * 0.15));
  Serial.println("turnRight");
}

void stopMotors() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  Serial.println("StopMotors");
}

void stopTurning() {
  stopMotors(); // Stop all motors to stop turning
  Serial.println("StopTurning");
}

void setup(){
  // Serial monitor
  Serial.begin(9600);
  
  // Define Inputs
  pinMode(CH1, INPUT);
  pinMode(CH2, INPUT);
  pinMode(CH3, INPUT);
  pinMode(CH4, INPUT);
  pinMode(CH5, INPUT);
  pinMode(CH6, INPUT);

  // Define Outputs
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);

}


void loop() {
  
  ch6Value = readSwitch(CH6, false);
  stopMotors();
  while (ch6Value == 1){
      // Get values for each channel
    ch1Value = readChannel(CH1, -255, 255, 0);
    ch3Value = readChannel(CH3, -255, 255, 0);
    ch6Value = readSwitch(CH6, false);
   
  // Forward movement
    if (ch3Value >= 30) { // Move forward
      moveForward(ch3Value);
  
      if (ch1Value <= -30) { // Turn left
        turnLeft(ch3Value,-ch1Value);
      } else if (ch1Value >= 30) { // Turn right
        turnRight(ch3Value,ch1Value);
      } 
      else{
      moveForward(ch3Value);  
      }
  
    } 
    
    else if (ch3Value <= -30) { // Move backwards
      moveBackward(-ch3Value);
      
      // Determine turning direction and speed based on CH1 joystick inputs
      if (ch1Value <= -30) { // Turn left
        turnLeft(-ch3Value, -ch1Value);
      } else if (ch1Value >= 30) { // Turn right
        turnRight(-ch3Value, ch1Value);
      } 
  
    } 
    else { // Stop movement
      stopMotors();
    }
    
    delay(100); // Adjust delay as needed
  }
}
