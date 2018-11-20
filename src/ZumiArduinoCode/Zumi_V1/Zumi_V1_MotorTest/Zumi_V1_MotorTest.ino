#include <MPU6050_tockn.h>
#include "U8glib.h"
//I am using the I2C one so select the following class
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);
//-----------------------------------------

#include <Wire.h>
MPU6050 mpu6050(Wire);

//globals for motor values
int leftSpeed = 160;
int rightSpeed = 160;


  //for setting up motor controller
  int STBY = 8;
  int PWMB = 11;
  int BIN2 = 10;
  int BIN1 = 9;
  int PWMA = 5;
  int AIN1 = 7;
  int AIN2 = 6;

  double bitsPerVolts;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  
  u8g.firstPage();
  
  u8g.setFont(u8g_font_04b_24);
  u8g.setPrintPos(0, 10);
  u8g.println("ZUMI :)");
 
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  
  pinMode(STBY, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(STBY, HIGH);
  //This for an accurate analog Read
  bitsPerVolts = 1024.0/(readVccMilliVolts()*0.001);
}

void loop() {


  u8g.firstPage();
  do {
    mpu6050.update();
    
    //set the pixel location on the screen
    //(X position, Y position)
    u8g.setPrintPos(0, 10);
    u8g.println(mpu6050.getGyroAngleX());
    u8g.setPrintPos(20, 10);
    u8g.println(mpu6050.getGyroAngleY());
    u8g.setPrintPos(40, 10);
    u8g.println(mpu6050.getGyroAngleZ());
    
    u8g.setPrintPos(0, 20);
    u8g.println(leftSpeed);
    u8g.setPrintPos(20, 20);
    u8g.println(rightSpeed);
    u8g.setPrintPos(0, 30);
    u8g.println(analogRead(A3)/bitsPerVolts);
  } 
  while ( u8g.nextPage() );

  // rebuild the picture after some delay
  delay(30);

  // moveForward(leftSpeed,rightSpeed);
//  zumiMove(160,160);
//  delay(1000);
//  zumiMove(0,0);
//  delay(1000);
//  zumiMove(-160,-160);
//  delay(1000);

  //delay(1000);
  //moveStop();
  //delay(1000);
  //linkyBeep();
  //moveLeft(160,160);
}


long readVccMilliVolts() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);             // Wait for Vref to settle
  ADCSRA |= _BV(ADSC);  // Convert
  while (bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

//does not work yet
void zumiMove(int rightMotorSpeed,int leftMotorSpeed){
  //left and right motor speed should be out of +255 to -255
  //set it to absolute value of the speed
  analogWrite(PWMA, abs(rightMotorSpeed));
  analogWrite(PWMB, abs(leftMotorSpeed));
  
  if(rightMotorSpeed  > 0)//go right forward
  {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  }
  if(rightMotorSpeed < 0)//go right backward
  {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH); 
  }
  if(rightMotorSpeed == 0) //else stop the motor
  {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW); 
  }
    
   if(leftMotorSpeed > 0)//go right forward
  {
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  }
  if(leftMotorSpeed < 0)//go right backward
  {
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH); 
  }
  if(leftMotorSpeed == 0) //else stop the motor
  {
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW); 
  }



}

void moveStop() {
  analogWrite(PWMA, 0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, LOW);

  analogWrite(PWMB, 0);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, LOW);
}

void moveForward(int speedA, int speedB) {
  analogWrite(PWMA, speedA);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  analogWrite(PWMB, speedB);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}


void moveLeft(int speedA, int speedB) {
  analogWrite(PWMA, speedA);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);

  analogWrite(PWMB, speedB);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}

void moveRight(int speedA, int speedB) {
  analogWrite(PWMA, speedA);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  analogWrite(PWMB, speedB);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
}

void moveBackward(int speedA, int speedB) {
  analogWrite(PWMA, speedA);
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  analogWrite(PWMB, speedB);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
}




void linkyBeep() {

  double k = 1.2;
  //(pin, frequency)
  //440, 523, 698
  tone(4, 523);
  delay(80 * k);

  noTone(4);
  delay(20 * k);

  tone(4, 587);
  delay(80 * k);

  noTone(4);
  delay(20 * k);

  tone(4, 698);
  delay(100 * k);

  noTone(4);
  delay(2000);
}

