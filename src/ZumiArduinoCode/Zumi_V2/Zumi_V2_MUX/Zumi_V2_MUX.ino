//V2 Zumi
//select arduino nano 168 under board
//Multiplexer
//A0 is multiplex out
//A1,15=S0, A2,16=S1, A3,17=S2
#include <Wire.h>
#include "U8glib.h"
//I am using the I2C one so select the following class
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);

#define ROWMAX 128
#define COLMAX 32

//-----------------------------------------

#define BLUE_LED 11
#define RED_LED 10
#define GREEN_LED 9

#define FORWARD 1
#define BACKWARD 2
#define LEFT 3
#define RIGHT 4
#define STOP 0

#define BUZZER_PIN 2
#define IR_REC_PIN 4

//A3906 Motor Controller is on pins
#define LEFTMOTOR_PINA 3
#define LEFTMOTOR_PINB 7
#define RIGHTMOTOR_PINA 6
#define RIGHTMOTOR_PINB 8

unsigned long counter = 0;

//IN1 =D3 MLEFTA
//IN2 =D7 MLEFTB
//IN3 =D6 MRIGHTA
//IN4 =D8 MRIGHTB

//for fast analog read

// Define various ADC prescaler
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

//BUZZER is on pin 2
//Battery voltage is on pin A7
//IR receiver is on pin 4
//IR Emitters control pin for the transistors is on pin 5.
//BE VERY CAREFUL WITH PIN 5

// the setup routine runs once when you press reset:
void setup() {
  Wire.begin();
  delay(100);
  
  u8g.firstPage();
  u8g.setFont(u8g_font_04b_24);
  u8g.setPrintPos(0, 10);
  u8g.println("ZUMI :)");
  u8g.drawBox(0, 0, 3, 3);
  delay(2000);

  // set up the ADC
  ADCSRA &= ~PS_128;  // remove bits set by Arduino library

  // you can choose a prescaler from above.
  // PS_16, PS_32, PS_64 or PS_128
  ADCSRA |= PS_16;

  delay(1000);

  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  linkyBeep();

  //setup analog pin for input make sure pullup is used
  pinMode(A0, INPUT_PULLUP);

  //Motor controller
  pinMode(LEFTMOTOR_PINA, OUTPUT);
  pinMode(LEFTMOTOR_PINB, OUTPUT);
  pinMode(RIGHTMOTOR_PINA, OUTPUT);
  pinMode(RIGHTMOTOR_PINB, OUTPUT);

  //Always start of OFF
  digitalWrite(3, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(8, LOW);

  //IR Led's transistor controll
  pinMode(5, OUTPUT);
  //analogWrite(5, 250);
  digitalWrite(5, HIGH);


  //setup analog pins for multiplexer as output
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  digitalWrite(15, LOW);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);


}

// the loop routine runs over and over again forever:
void loop() {

  u8g.firstPage();
  do {
    if (counter > 10)
    {
      closeEyes();
      delay(1000);
      counter = 0;
    }
    else {
      zumiEyes();
      delay(50);
      counter++;
    }
  }
  while ( u8g.nextPage() );

  //displayAllIRsensors();
  int sum = 0;
  // if(digitalRead(4)==0){
  //  for(int i=0;i<100;i++){
  //  delayMicroseconds(50);
  //  sum = sum + 2*digitalRead(4)-1;
  //  }
  //  }
  //  Serial.println(sum);
  //Serial.println(readthisIRSensors(0));
  //tone(5, 0);
  //analogWrite(5, 254);
  //analogWrite(5, 0);
  //0th IR is the mid right

  //  int valueRight = readthisIRSensors(0);
  //  delay(50);
  //  int valueLeft = readthisIRSensors(1);

  //  motors(BACKWARD);
  //  if(valueRight<50){
  //    motors(LEFT);
  //    Serial.println(valueRight);
  //
  //  }
  //  else if(valueLeft<50)
  //  {
  //    motors(RIGHT);
  //    Serial.println(valueLeft);
  //
  //  }
  //  else
  //  {
  //    motors(STOP);
  //  }
  //

}


void zumiEyes()
{
  int eye_Height = 31;
  int eye_center = 0;

  //set the pixel location on the screen
  //(X position, Y position)
      u8g.drawBox(128/4, 0, 6, 32);
      u8g.drawBox(128/4*3, 0, 6, 32);

}


void closeEyes()
{
  int eye_Height = 31;
  int eye_center = 0;

  //#define ROWMAX 128
  //#define COLMAX 32

  //set the pixel location on the screen
  //(X position, Y position)

  for (int i = COLMAX; i > 0; i--)
  {
    for(int j = ROWMAX; j > 0; j--)
    {
    u8g.drawStr(i, j, " ");
    }
  }

}


void linkyBeep() {

  double k = 1.2;
  //(pin, frequency)
  //440, 523, 698
  tone(2, 523);
  delay(80 * k);

  noTone(2);
  delay(20 * k);

  tone(2, 587);
  delay(80 * k);

  noTone(2);
  delay(20 * k);

  tone(2, 698);
  delay(100 * k);

  noTone(2);
  delay(2000);
}




void motors(int direction)
{
  //maybe use grey code here
  //so you only switch one bit at a time
  switch (direction) {
    //--------------------------------------
    case 0:
      //STOP
      digitalWrite(3, LOW);
      digitalWrite(7, LOW);

      digitalWrite(6, LOW);
      digitalWrite(8, LOW);

      break;
    //--------------------------------------
    case 1:
      //left motor Forward 3=1 7=0
      digitalWrite(3, LOW);
      digitalWrite(7, HIGH);

      //right motor Forward 6=0 8=1
      digitalWrite(6, HIGH);
      digitalWrite(8, LOW);

      break;
    //--------------------------------------
    case 2:
      //left motor backward 3=1 7=0
      digitalWrite(3, HIGH);
      digitalWrite(7, LOW);

      //right motor backward 6=0 8=1
      digitalWrite(6, LOW);
      digitalWrite(8, HIGH);

      break;
    //--------------------------------------
    case 3:
      //left motor Forward 3=1 7=0
      digitalWrite(3, LOW);
      digitalWrite(7, HIGH);

      //right motor backward 6=1 8=0
      digitalWrite(6, HIGH);
      digitalWrite(8, LOW);
      break;
    //--------------------------------------
    case 4:
      //left motor backward 3=1 7=0
      digitalWrite(3, HIGH);
      digitalWrite(7, LOW);

      //right motor Forward 6=0 8=1
      digitalWrite(6, HIGH);
      digitalWrite(8, LOW);
      break;
    //--------------------------------------
    default:

      break;
  }

}


int readthisIRSensors(byte indexOfIRSensor)
{
  //maybe use grey code here
  //so you only switch one bit at a time
  switch (indexOfIRSensor) {
    //--------------------------------------
    case 0:
      //000 = 0
      digitalWrite(15, LOW);
      digitalWrite(16, LOW);
      digitalWrite(17, LOW);
      break;
    //--------------------------------------
    case 1:
      //001 = 1
      digitalWrite(15, LOW);
      digitalWrite(16, LOW);
      digitalWrite(17, HIGH);
      break;
    //--------------------------------------
    case 2:
      //010 = 2
      digitalWrite(15, LOW);
      digitalWrite(16, HIGH);
      digitalWrite(17, LOW);
      break;
    //--------------------------------------
    case 3:
      //011 = 3
      digitalWrite(15, LOW);
      digitalWrite(16, HIGH);
      digitalWrite(17, HIGH);
      break;
    //--------------------------------------
    case 4:
      //100 = 4
      digitalWrite(15, HIGH);
      digitalWrite(16, LOW);
      digitalWrite(17, LOW);
      break;
      //--------------------------------------
      //101 = 5
      digitalWrite(15, HIGH);
      digitalWrite(16, LOW);
      digitalWrite(17, HIGH);
      break;
    //--------------------------------------
    case 6:
      //110 = 6
      digitalWrite(15, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(17, LOW);
      break;
    //--------------------------------------

    case 7:
      //111 = 7
      digitalWrite(15, HIGH);
      digitalWrite(16, HIGH);
      digitalWrite(17, HIGH);
      break;
    //--------------------------------------


    default:
      break;
  }
  return analogRead(A0);
}

void displayAllIRsensors()
{
  analogWrite(5, 155);
  for (int i = 0; i < 8; i++) {

    Serial.print(30 - 1000 / readthisIRSensors(i));
    Serial.print(",");
    // delay(1);        // delay in between reads for stability
  }
  Serial.println("");
  analogWrite(5, 0);

}

