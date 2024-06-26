#define CH1 1
#define CH2 2
#define CH3 3
#define CH4 4
#define CH5 5
#define CH6 6

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

}

void loop(){
  ch1Value = readChannel(CH1, -255, 255, 0);
  ch2Value = readChannel(CH2, -255, 255, 0);
  ch3Value = readChannel(CH3, -255, 255, 0);
  ch4Value = readChannel(CH4, -255, 255, 0);
  ch5Value = readSwitch(CH5, false);
  ch6Value = readSwitch(CH6, false);

Serial.print(ch1Value);
Serial.print(", ");
Serial.print(ch2Value);
Serial.print(", ");
Serial.print(ch3Value);
Serial.print(", ");
Serial.print(ch4Value);
Serial.print(", ");
Serial.print(ch5Value);
Serial.print(", ");
Serial.println(ch6Value);
  delay(10);
  
}
