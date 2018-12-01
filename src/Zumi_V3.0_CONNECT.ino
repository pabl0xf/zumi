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

double bitsPerVolts = 0;

int motorSpeed = 50;
int sensorBL, sensorBR;
int baseLV_L = 1023;
int baseLV_R = 1023;
int mode = 0;
int alarm = 0;

float angle, initAngle;
float dAngle = 0.0;

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

  //100 ms fade-up and 100 ms to fade-down.
  SoftPWMSetFadeTime(FRONT_RIGHT_LED, 1, 1);
  SoftPWMSetFadeTime(FRONT_LEFT_LED, 1, 1);
  SoftPWMSetFadeTime(BACK_LEFT_LED, 1, 1);
  SoftPWMSetFadeTime(BACK_RIGHT_LED, 1, 1);

  //This is for an accurate analog read
  bitsPerVolts = 1023.0 / (readVccMilliVolts() * 0.001);

  //Sound
  pinMode(BUZZER_PIN, OUTPUT);

  setupLineTracer();
}

void loop() {
  if (analogRead(BATT_LVL_PIN) / bitsPerVolts <= 3.1) {
    if (millis() - currentTime > 1000) alarm = 1 - alarm;
    if (alarm == 1) digitalWrite(BUZZER_PIN, HIGH);
    else digitalWrite(BUZZER_PIN, LOW);
  }
}

void setupLineTracer() {
  for (int i = 0; i < 100; i++) {
    baseLV_L  = min(readIRaverage(4, 5), baseLV_L);
    baseLV_R  = min(readIRaverage(2, 5), baseLV_R);
  }
  baseLV_L += 50;
  baseLV_R += 50;
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

  return analogRead(MUX_OUTPUT);
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
        setMotorState(1, Wire.read(), Wire.read());
        mode = 0;
        break;
      case 65: // character "A"
        setMotorState(3, Wire.read(), Wire.read());
        mode = 0;
        break;
      case 66: // character "B"
        setMotorState(4, Wire.read(), Wire.read());
        mode = 0;
        break;
      case 67: // character "C"
        setMotorState(2, Wire.read(), Wire.read());
        mode = 0;
        break;
      case 68: // character "D"
        setMotorState(3, motorSpeed, motorSpeed);
        dAngle = Wire.read();
        mode = 1;
        break;
      case 69: // character "D"
        setMotorState(4, motorSpeed, motorSpeed);
        dAngle = Wire.read();
        mode = 1;
        break;
      case 70: // character "F"
        motorSpeed = Wire.read();
        break;
      case 77:// character "M"
        setMotorState(1, motorSpeed, motorSpeed);
        mode = 0;
        break;
      case 78:// character "N"
        setMotorState(2, motorSpeed, motorSpeed);
        mode = 0;
        break;
      case 79:// character "O"
        setMotorState(4, motorSpeed, motorSpeed);
        mode = 0;
        break;
      case 80://character "P"
        setMotorState(3, motorSpeed, motorSpeed);
        mode = 0;
        break;
      case 81: //character "Q"
        setMotorState(0, 0, 0);
        mode = 0;
        break;
      case 82: //character "R"
        excited();
        break;
      default:
        break;
    }
  }
}

