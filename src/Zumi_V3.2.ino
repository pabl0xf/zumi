#include <SoftPWM_timer.h>
#include <SoftPWM.h>
#include <Wire.h>

#define SLAVE_ADDRESS 0x04
#define MUX_OUTPUT 21
#define MUX_S0 15
#define MUX_S1 16
#define MUX_S2 17
#define FRONT_LEFT_LED 11
#define FRONT_RIGHT_LED 12
#define BACK_LEFT_LED  10
#define BACK_RIGHT_LED  9
#define BUZZER_PIN 14
#define BATT_LVL_PIN 20
#define IR_REMREC_PIN 4
#define IR_EMIT_PIN 5
#define MOTOR_LEFT_A 6
#define MOTOR_LEFT_B 8
#define MOTOR_RIGHT_A 7
#define MOTOR_RIGHT_B 3
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

  SoftPWMBegin();
  SoftPWMSet(MOTOR_LEFT_A, 0);
  SoftPWMSet(MOTOR_LEFT_B, 0);
  SoftPWMSet(MOTOR_RIGHT_A, 0);
  SoftPWMSet(MOTOR_RIGHT_B, 0);

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

  //100 ms fade-up and 100 ms to fade-down.
  SoftPWMSetFadeTime(MOTOR_LEFT_A, 100, 100);
  SoftPWMSetFadeTime(MOTOR_LEFT_A, 100, 100);
  SoftPWMSetFadeTime(MOTOR_RIGHT_A, 100, 100);
  SoftPWMSetFadeTime(MOTOR_RIGHT_A, 100, 100);

  //LED setup
  pinMode(FRONT_RIGHT_LED, OUTPUT);
  pinMode(FRONT_LEFT_LED, OUTPUT);
  pinMode(BACK_RIGHT_LED, OUTPUT);
  pinMode(BACK_LEFT_LED, OUTPUT);

  digitalWrite(FRONT_LEFT_LED, LOW);
  digitalWrite(FRONT_RIGHT_LED, LOW);
  digitalWrite(BACK_LEFT_LED, LOW);
  digitalWrite(BACK_RIGHT_LED, LOW);

  //100 ms fade-up and 100 ms to fade-down.
  SoftPWMSetFadeTime(FRONT_RIGHT_LED, 1, 1);
  SoftPWMSetFadeTime(FRONT_LEFT_LED, 1, 1);
  SoftPWMSetFadeTime(BACK_LEFT_LED, 1, 1);
  SoftPWMSetFadeTime(BACK_RIGHT_LED, 1, 1);

  //This is for an accurate analog read
  bitsPerVolts = 1023.0 / (readVccMilliVolts() * 0.001);

  //Sound
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
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
    excited();
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
  digitalWrite(5, HIGH);

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
  digitalWrite(5, LOW);

  return reading;
}

byte setMotorState(byte selectedMotorState, byte speedM1, byte speedM2)
{
  byte motorState = selectedMotorState;
  switch (selectedMotorState) {
    //--------------------------------------
    case 0://Stop
      SoftPWMSet(MOTOR_LEFT_A, 0);
      SoftPWMSet(MOTOR_LEFT_B, 0);
      SoftPWMSet(MOTOR_RIGHT_A, 0);
      SoftPWMSet(MOTOR_RIGHT_B, 0);
      break;
    //--------------------------------------
    case 1://Forward
      SoftPWMSet(MOTOR_LEFT_A, speedM1);
      SoftPWMSet(MOTOR_LEFT_B, 0);
      SoftPWMSet(MOTOR_RIGHT_A, speedM2);
      SoftPWMSet(MOTOR_RIGHT_B, 0);
      break;
    //--------------------------------------
    case 2://Backward
      SoftPWMSet(MOTOR_LEFT_A, 0);
      SoftPWMSet(MOTOR_LEFT_B, speedM1);
      SoftPWMSet(MOTOR_RIGHT_A, 0);
      SoftPWMSet(MOTOR_RIGHT_B, speedM2);
      break;
    //--------------------------------------
    case 3://Right
      SoftPWMSet(MOTOR_LEFT_A, speedM1);
      SoftPWMSet(MOTOR_LEFT_B, 0);
      SoftPWMSet(MOTOR_RIGHT_A, 0);
      SoftPWMSet(MOTOR_RIGHT_B, speedM2);
      break;
    //--------------------------------------
    case 4://Left
      SoftPWMSet(MOTOR_LEFT_A, 0);
      SoftPWMSet(MOTOR_LEFT_B, speedM1);
      SoftPWMSet(MOTOR_RIGHT_A, speedM2);
      SoftPWMSet(MOTOR_RIGHT_B, 0);
      break;
    //--------------------------------------
    case 5://Left motor forward
      SoftPWMSet(MOTOR_LEFT_A, speedM1);
      SoftPWMSet(MOTOR_LEFT_B, 0);
      SoftPWMSet(MOTOR_RIGHT_A, 0);
      SoftPWMSet(MOTOR_RIGHT_B, 0);
      break;
    //--------------------------------------
    case 6://Left motor reverse
      SoftPWMSet(MOTOR_LEFT_A, 0);
      SoftPWMSet(MOTOR_LEFT_B, speedM1);
      SoftPWMSet(MOTOR_RIGHT_A, 0);
      SoftPWMSet(MOTOR_RIGHT_B, 0);
      break;
    //--------------------------------------
    case 7://Right motor forward
      SoftPWMSet(MOTOR_LEFT_A, 0);
      SoftPWMSet(MOTOR_LEFT_B, 0);
      SoftPWMSet(MOTOR_RIGHT_A, speedM2);
      SoftPWMSet(MOTOR_RIGHT_B, 0);
      break;
    //--------------------------------------
    case 8://Right motor reverse
      SoftPWMSet(MOTOR_LEFT_A, 0);
      SoftPWMSet(MOTOR_LEFT_B, 0);
      SoftPWMSet(MOTOR_RIGHT_A, 0);
      SoftPWMSet(MOTOR_RIGHT_B, speedM2);
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

void sendData() {
  Wire.write(motorSpeed);
}

