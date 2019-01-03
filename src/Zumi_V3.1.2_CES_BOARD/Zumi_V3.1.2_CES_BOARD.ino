#include <Wire.h>

#define SLAVE_ADDRESS 0x04
#define MUX_OUTPUT 21
#define MUX_S0 15
#define MUX_S1 16
#define MUX_S2 17
#define FRONT_LEFT_LED 11
#define FRONT_RIGHT_LED 12
#define BACK_LEFT_LED  8
#define BACK_RIGHT_LED  7
#define BUZZER_PIN 14
#define BATT_LVL_PIN 20
#define IR_REMREC_PIN 4
#define IR_EMIT_PIN 3
#define MOTOR_LEFT_A 5
#define MOTOR_LEFT_B 6
#define MOTOR_RIGHT_A 9
#define MOTOR_RIGHT_B 10
#define STOP 0
#define FORWARD 1
#define BACKWARD 2
#define LEFT_TURN 3
#define RIGHT_TURN 4
#define BATT_THRESH 25
#define ACCEL_INCREMENT 20

double bitsPerVolts = 0;

int motorSpeed = 30;
int motorSpeedL = 0;
int motorSpeedR = 0;
int motorSpeedLNew = 0;
int motorSpeedRNew = 0;
int sensorBL, sensorBR;
int baseLV_L = 1023;
int baseLV_R = 1023;
int baseLV_BL = 1023;
int baseLV_BR = 1023;
int light = 0;
int battery = 0;
int success = 0;
int melody = 0;
int temp;
int mode = 0;

long unsigned currentTime = 0;

void setup() {
  //Motor controller setup
  pinMode(MOTOR_LEFT_A, OUTPUT);
  pinMode(MOTOR_LEFT_B, OUTPUT);
  pinMode(MOTOR_RIGHT_A, OUTPUT);
  pinMode(MOTOR_RIGHT_B, OUTPUT);

  //Stop motor
  setMotorState(0, 0, 0);

  //Setup analog pins for multiplexer as output
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);

  //IR LEDs transistor control
  pinMode(IR_EMIT_PIN, OUTPUT);

  //Setup I2C communication
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);


  //LED setup
  pinMode(FRONT_RIGHT_LED, OUTPUT);
  pinMode(FRONT_LEFT_LED, OUTPUT);
  pinMode(BACK_RIGHT_LED, OUTPUT);
  pinMode(BACK_LEFT_LED, OUTPUT);

  digitalWrite(FRONT_LEFT_LED, HIGH);
  digitalWrite(FRONT_RIGHT_LED, HIGH);
  digitalWrite(BACK_LEFT_LED, LOW);
  digitalWrite(BACK_RIGHT_LED, LOW);


  //This is for an accurate analog read
  bitsPerVolts = 1023.0 / (readVccMilliVolts() * 0.001);
  //it uses the internal 1.1volt reference to figure put 
  //if the analogread value of 1023 is actually 5 volts

  //Sound
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  excited(); 
  //motorTest();
  
}

void loop() {
  //Battery code
  if (millis() - currentTime > 400) {
    if (battery < BATT_THRESH) battery++;
    if (analogRead(BATT_LVL_PIN) / bitsPerVolts > 3.8) battery = 0;
    if ( light == 1 ) {
      digitalWrite(FRONT_LEFT_LED, LOW);
      digitalWrite(FRONT_RIGHT_LED, LOW);
      digitalWrite(BACK_LEFT_LED, LOW);
      digitalWrite(BACK_RIGHT_LED, LOW);
      light = 0;
    }
    else {
      if ( battery == BATT_THRESH ) {
        digitalWrite(FRONT_LEFT_LED, HIGH);
        digitalWrite(FRONT_RIGHT_LED, HIGH);
        digitalWrite(BACK_LEFT_LED, HIGH);
        digitalWrite(BACK_RIGHT_LED, HIGH);
        light = 1;
      }
    }
    currentTime = millis();
  }

  //Acceleration/Deceleration code
  //It is only necessary to update the motors if either the left or right motor's target speed changes
  success = 1;
  if  ( motorSpeedL != motorSpeedLNew ) {
    //Get error between target and initial speeds
    temp = motorSpeedLNew - motorSpeedL;
    //Cap the error to prevent from drawing too much current when the error is added to the motor speed
    if (temp > ACCEL_INCREMENT) temp = ACCEL_INCREMENT;
    else if (temp < -ACCEL_INCREMENT) temp = -ACCEL_INCREMENT;
    //If transitioning from forward/reverse positive/negative, stop the motors first
    if ((motorSpeedL + temp)*motorSpeedL < 0) motorSpeedL = 0;
    //Else, add error to motor speed
    else motorSpeedL += temp;
    //Speed changed; update motor state
    success = 0;
  }
  if  ( motorSpeedR != motorSpeedRNew ) {
    temp = motorSpeedRNew - motorSpeedR;
    if (temp > ACCEL_INCREMENT) temp = ACCEL_INCREMENT;
    else if (temp < -ACCEL_INCREMENT) temp = -ACCEL_INCREMENT;
    if ((motorSpeedR + temp)*motorSpeedR < 0) motorSpeedR = 0;
    else motorSpeedR += temp;
    success = 0;
  }
  if ( success == 0 ) {
    if ( motorSpeedL < 0 && motorSpeedR < 0) setMotorState(2, -motorSpeedL, -motorSpeedR);
    else if ( motorSpeedL >= 0 && motorSpeedR < 0) setMotorState(3, motorSpeedL, -motorSpeedR);
    else if ( motorSpeedL >= 0 && motorSpeedR >= 0) setMotorState(1, motorSpeedL, motorSpeedR);
    else setMotorState(4, -motorSpeedL, motorSpeedR);
  }

  //Melodies
  if (melody == 1) {
    //excited();
    melody = 0;
  }

  delay(50);
}

void playNote(int note, int duration) {
  long initialTime = millis();

  while ( millis() - initialTime < duration) {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(note / 2); // period divided by 2 (50% duty cycle)
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(note / 2);
  }
}

void playMelody( int melody[], int beats[], int tempo, int pause) {
  int MAX_COUNT = sizeof(melody);
  long tempos = tempo;
  int pauses = pause;
  int note;
  int beat;
  long duration;

  for (int i = 0; i < MAX_COUNT; i++) {
    note = melody[i];
    beat = beats[i];
    duration = tempos / beat; // Set up timing
    playNote(note, duration);
    delayMicroseconds(pauses);
  }
}

void excited() {
  int excited[] = {955, 758, 638, 638, 758, 638};
  int beats[] = {8, 8, 8, 4, 10, 8};
  int MAX_COUNT = sizeof(excited);
  long tempo = 1000;
  int pause = 700;
  int note;
  int beat;
  long duration;

  for (int i = 0; i < MAX_COUNT; i++) {
    note = excited[i];
    beat = beats[i];
    duration = tempo / beat; // Set up timing
    playNote(note, duration);
    delayMicroseconds(pause);
  }
}

long readVccMilliVolts() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);             // Wait for Vref to settle
  ADCSRA |= _BV(ADSC);  // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

int readIRaverage(int irIndex, int iterations) {
  int sum = 0;
  for (int i = 0; i < iterations; i++) sum += readIR(irIndex);
  return sum / iterations;
}

int readIR(int indexOfIRSensor)
{
  digitalWrite(IR_EMIT_PIN, HIGH);

  //Select different channels on the Multiplexer
  switch (indexOfIRSensor) {
    //--------------------------------------
    case 0://Y0 - UNUSED
      digitalWrite(15, LOW);
      digitalWrite(16, LOW);
      digitalWrite(17, LOW);
      break;
    //--------------------------------------
    case 1://Y1
      //100 = 4
      digitalWrite(15, HIGH);
      digitalWrite(16, LOW);
      digitalWrite(17, LOW);
      break;
    //--------------------------------------
    case 2://Y2
      //010 = 2
      digitalWrite(15, LOW);
      digitalWrite(16, HIGH);
      digitalWrite(17, LOW);
      break;
    //--------------------------------------
    case 3://Y3
      //110 = 6
      digitalWrite(15, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(17, LOW);
      break;
    //--------------------------------------
    case 4://Y4
      //001 = 1
      digitalWrite(15, LOW);
      digitalWrite(16, LOW);
      digitalWrite(17, HIGH);
      break;
    //--------------------------------------
    case 5://Y5
      //101 = 5
      digitalWrite(15, HIGH);
      digitalWrite(16, LOW);
      digitalWrite(17, HIGH);
      break;
    //--------------------------------------
    case 6://Y6
      //011 = 3
      digitalWrite(15, LOW);
      digitalWrite(16, HIGH);
      digitalWrite(17, HIGH);
      break;
    //--------------------------------------
    case 7://Y7 - UNUSED
      digitalWrite(15, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(17, HIGH);
      break;
    //--------------------------------------
    default:
      break;
  }

  int reading = analogRead(MUX_OUTPUT);
 //turn off the emitter
  digitalWrite(IR_EMIT_PIN, LOW);

  return reading;
}

byte setMotorState(byte selectedMotorState, byte speedM1, byte speedM2)
{
  byte motorState = selectedMotorState;

  switch (selectedMotorState) {
    //--------------------------------------
    case 0://Motors stop
      //000 = 0
      analogWrite(MOTOR_LEFT_A, 0);
      analogWrite(MOTOR_LEFT_B, 0);
      analogWrite(MOTOR_RIGHT_A, 0);
      analogWrite(MOTOR_RIGHT_B, 0);

      
      //      SoftPWMSet(MOTOR_LEFT_A, 0);
      //      SoftPWMSet(MOTOR_LEFT_B, 0);
      //      SoftPWMSet(MOTOR_RIGHT_A, 0);
      //      SoftPWMSet(MOTOR_RIGHT_B, 0);


      break;
    //--------------------------------------
    case 1://forward
      //1
      analogWrite(MOTOR_LEFT_A, speedM1);
      analogWrite(MOTOR_LEFT_B, 0);
      analogWrite(MOTOR_RIGHT_A, speedM2);
      analogWrite(MOTOR_RIGHT_B, 0);
      //      SoftPWMSet(MOTOR_LEFT_A, speedM1);
      //      SoftPWMSet(MOTOR_LEFT_B, 0);
      //      SoftPWMSet(MOTOR_RIGHT_A, speedM2);
      //      SoftPWMSet(MOTOR_RIGHT_B, 0);



      break;
    //--------------------------------------
    case 2://backward
      //2
      analogWrite(MOTOR_LEFT_A, 0);
      analogWrite(MOTOR_LEFT_B, speedM1);
      analogWrite(MOTOR_RIGHT_A, 0);
      analogWrite(MOTOR_RIGHT_B, speedM2);


      
      //      SoftPWMSet(MOTOR_LEFT_A, 0);
      //      SoftPWMSet(MOTOR_LEFT_B, speedM1);
      //      SoftPWMSet(MOTOR_RIGHT_A, 0);
      //      SoftPWMSet(MOTOR_RIGHT_B, speedM2);

      break;
    //--------------------------------------
    case 3://left with both motors
      //011 = 3
      analogWrite(MOTOR_LEFT_A, speedM1);
      analogWrite(MOTOR_LEFT_B, 0);
      analogWrite(MOTOR_RIGHT_A, 0);
      analogWrite(MOTOR_RIGHT_B, speedM2);
      //      SoftPWMSet(MOTOR_LEFT_A, speedM1);
      //      SoftPWMSet(MOTOR_LEFT_B, 0);
      //      SoftPWMSet(MOTOR_RIGHT_A, 0);
      //      SoftPWMSet(MOTOR_RIGHT_B, speedM2);
      break;
    //--------------------------------------
    case 4://right with both motors
      //100 = 4
      analogWrite(MOTOR_LEFT_A, 0);
      analogWrite(MOTOR_LEFT_B, speedM1);
      analogWrite(MOTOR_RIGHT_A, speedM2);
      analogWrite(MOTOR_RIGHT_B, 0);
      //      SoftPWMSet(MOTOR_LEFT_A, 0);
      //      SoftPWMSet(MOTOR_LEFT_B, speedM1);
      //      SoftPWMSet(MOTOR_RIGHT_A, speedM2);
      //      SoftPWMSet(MOTOR_RIGHT_B, 0);

      break;
    //--------------------------------------

    case 5://turn left with right motor
      //
      analogWrite(MOTOR_LEFT_A, speedM1);
      analogWrite(MOTOR_LEFT_B, 0);
      analogWrite(MOTOR_RIGHT_A, 0);
      analogWrite(MOTOR_RIGHT_B, 0);
      //      SoftPWMSet(MOTOR_LEFT_A, speedM1);
      //      SoftPWMSet(MOTOR_LEFT_B, 0);
      //      SoftPWMSet(MOTOR_RIGHT_A, 0);
      //      SoftPWMSet(MOTOR_RIGHT_B, 0);

      break;
    //--------------------------------------
    case 6://turn right with right motor
      //
      analogWrite(MOTOR_LEFT_A, 0);
      analogWrite(MOTOR_LEFT_B, speedM1);
      analogWrite(MOTOR_RIGHT_A, 0);
      analogWrite(MOTOR_RIGHT_B, 0);
      //      SoftPWMSet(MOTOR_LEFT_A, 0);
      //      SoftPWMSet(MOTOR_LEFT_B, speedM1);
      //      SoftPWMSet(MOTOR_RIGHT_A, 0);
      //      SoftPWMSet(MOTOR_RIGHT_B, 0);

      break;
    //--------------------------------------

    case 7://turn right with left motor
      //111 = 7
      analogWrite(MOTOR_LEFT_A, 0);
      analogWrite(MOTOR_LEFT_B, 0);
      analogWrite(MOTOR_RIGHT_A, speedM2);
      analogWrite(MOTOR_RIGHT_B, 0);
      //      SoftPWMSet(MOTOR_LEFT_A, 0);
      //      SoftPWMSet(MOTOR_LEFT_B, 0);
      //      SoftPWMSet(MOTOR_RIGHT_A, speedM2);
      //      SoftPWMSet(MOTOR_RIGHT_B, 0);

      break;
    //--------------------------------------


    case 8:////turn left w left motor
      // 8
      analogWrite(MOTOR_LEFT_A, 0);
      analogWrite(MOTOR_LEFT_B, 0);
      analogWrite(MOTOR_RIGHT_A, 0);
      analogWrite(MOTOR_RIGHT_B, speedM2);
      //      SoftPWMSet(MOTOR_LEFT_A, 0);
      //      SoftPWMSet(MOTOR_LEFT_B, 0);
      //      SoftPWMSet(MOTOR_RIGHT_A, 0);
      //      SoftPWMSet(MOTOR_RIGHT_B, speedM2);

      break;
    //--------------------------------------

    default:
      break;
  }
  return motorState;
}

void receiveData() {
  while (Wire.available()) {
    switch (Wire.read()) {
      case 64: // character "@"
        if (mode == 1) {
          motorSpeedLNew = Wire.read();
          motorSpeedRNew = Wire.read();
        }
        else setMotorState(1, Wire.read(), Wire.read());
        break;
      case 65: // character "A"
        if ( mode == 1) {
          motorSpeedLNew = Wire.read();
          motorSpeedRNew = Wire.read();
          motorSpeedRNew = -motorSpeedRNew;
        }
        else setMotorState(3, Wire.read(), Wire.read());
        break;
      case 66: // character "B"
        if ( mode == 1) {
          motorSpeedLNew = Wire.read();
          motorSpeedRNew = Wire.read();
          motorSpeedLNew = -motorSpeedLNew;
        }
        else setMotorState(4, Wire.read(), Wire.read());
        break;
      case 67: // character "C"
        if ( mode == 1) {
          motorSpeedLNew = Wire.read();
          motorSpeedRNew = Wire.read();
          motorSpeedLNew = -motorSpeedLNew;
          motorSpeedRNew = -motorSpeedRNew;
        }
        else setMotorState(2, Wire.read(), Wire.read());
        break;
      case 70: // character "F"
        motorSpeed = Wire.read();
        break;
      case 77:// character "M"
        if ( mode == 1) {
          motorSpeedLNew = motorSpeed;
          motorSpeedRNew = motorSpeed;
        }
        else setMotorState(1, motorSpeed, motorSpeed);
        break;
      case 78:// character "N"
        if ( mode == 1) {
          motorSpeedLNew = -motorSpeed;
          motorSpeedRNew = -motorSpeed;
        }
        else setMotorState(2, motorSpeed, motorSpeed);
        break;
      case 79:// character "O"
        if ( mode == 1) {
          motorSpeedLNew = -motorSpeed;
          motorSpeedRNew = motorSpeed;
        }
        else setMotorState(4, motorSpeed, motorSpeed);
        break;
      case 80:// character "P"
        if ( mode == 1) {
          motorSpeedLNew = motorSpeed;
          motorSpeedRNew = -motorSpeed;
        }
        else setMotorState(3, motorSpeed, motorSpeed);
        break;
      case 81: //character "Q"
        if ( mode == 1) {
          motorSpeedLNew = 0;
          motorSpeedRNew = 0;
        }
        else setMotorState(0, 0, 0);
        break;
      case 82:
        melody = 1;
        break;
      case 84: //character "T"
        digitalWrite(FRONT_LEFT_LED, LOW);
        digitalWrite(FRONT_RIGHT_LED, LOW);
        break;
      case 85: //character "U"
        digitalWrite(FRONT_LEFT_LED, HIGH);
        digitalWrite(FRONT_RIGHT_LED, HIGH);
        break;
      case 86: //character "V"
        //switch acceleration on
        mode = 1;
        break;
      case 87: //character "W"
        //switch acceleration off
        mode = 0;
        break;
      default:
        break;
    }
  }
}

void motorTest() {

  //go through all the motor states
  for (int i = 0; i < 9; i = i + 1)
  {
    //
    for (int j = 0; j < 255; j = j + 1)
    {
      setMotorState(i, j, j);
      delay(1);
      //once reaching the top speed stay at that speed
      if(j==255){
       setMotorState(i, j, j);
      delay(1000);
      }
    }
 
    for (int j = 255; j > 0; j = j - 1)
    {
      setMotorState(i, j, j);
      delay(1);
            //once reaching the top speed stay at that speed
      if(j==255){
       setMotorState(i, j, j);
      delay(1500);
      }
    }
  }
}

void sendData() {
  Wire.write(motorSpeed);
}
