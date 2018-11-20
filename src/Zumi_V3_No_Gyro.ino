#include <SoftPWM_timer.h>
#include <SoftPWM.h>
#include <Wire.h>
#include <MPU6050_tockn.h>
//#include <U8glib.h>

//U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
MPU6050 mpu6050(Wire);

#define SLAVE_ADDRESS 0x04
#define ROWMAX 128
#define COLMAX 32
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

int motorSpeed = 50;
int sensorBL, sensorBR;
int baseLV_L = 1023;
int baseLV_R = 1023;

void setup() {
  //Motor controller
  pinMode(MOTOR_LEFT_A, OUTPUT);
  pinMode(MOTOR_LEFT_B, OUTPUT);
  pinMode(MOTOR_RIGHT_A, OUTPUT);
  pinMode(MOTOR_RIGHT_B, OUTPUT);

  setMotorState(0, 0, 0);

  SoftPWMBegin();
  SoftPWMSet(MOTOR_LEFT_A, 0);
  SoftPWMSet(MOTOR_LEFT_B, 0);
  SoftPWMSet(MOTOR_RIGHT_A, 0);
  SoftPWMSet(MOTOR_RIGHT_B, 0);

  //setup analog pins for multiplexer as output
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);

  //IR LED's transistor control
  pinMode(IR_EMIT_PIN, OUTPUT);

  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  delay(100);

  //1000 ms fade-up and 1000 ms to fade-down.
  SoftPWMSetFadeTime(MOTOR_LEFT_A, 100, 100);
  SoftPWMSetFadeTime(MOTOR_LEFT_A, 100, 100);
  SoftPWMSetFadeTime(MOTOR_RIGHT_A, 100, 100);
  SoftPWMSetFadeTime(MOTOR_RIGHT_A, 100, 100);

  pinMode(FRONT_RIGHT_LED, OUTPUT);
  pinMode(FRONT_LEFT_LED, OUTPUT);
  pinMode(BACK_RIGHT_LED, OUTPUT);
  pinMode(BACK_LEFT_LED, OUTPUT);

  setupLineTracer();
}

void loop() {
  delay(100);
}

void setupLineTracer() {
  for (int i = 0; i < 100; i++) {
    baseLV_L  = min(readIRaverage(4, 5), baseLV_L);
    baseLV_R  = min(readIRaverage(2, 5), baseLV_R);
  }

  baseLV_L += 50;
  baseLV_R += 50;
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
        break;
      case 65: // character "A"
        setMotorState(3, Wire.read(), Wire.read());
        break;
      case 66: // character "B"
        setMotorState(4, Wire.read(), Wire.read());
        break;
      case 67: // character "C"
        setMotorState(2, Wire.read(), Wire.read());
        break;
      case 70: // character "F"
        motorSpeed = Wire.read();
        break;
      case 77:// character "M"
        setMotorState(1, motorSpeed, motorSpeed);
        break;
      case 78:// character "N"
        setMotorState(2, motorSpeed, motorSpeed);
        break;
      case 79:// character "O"
        setMotorState(4, motorSpeed, motorSpeed);
        break;
      case 80://character "P"
        setMotorState(3, motorSpeed, motorSpeed);
        break;
      case 81: //character "Q"
        setMotorState(0, 0, 0);
        break;
      default:
        break;
    }
  }
}

