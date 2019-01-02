/*------ Board Select ----------------------------
    Arduino Pro or Pro Mini
    Atmega328 (5V, 16Mhz)
  ------------------------------------------------*/
/*-------------------------------------------------
  tunning sensor -linetracer
  Remocon set channel (0~4) - tv remocon
  Low Battery check - 3.7v
  Speed Change => Remocon Mode
  ------------------------------------------------*/
#include "config.h"
#include "ex_Linky.h"
#include "ex_Unplugged.h"
#include "RokitFirmata.h"

#define GREYL1 925
#define GREYL2 945
#define GREYL3 965
#define GREYR1 945
#define GREYR2 955
#define GREYR3 975
#define BLACKL 995
#define BLACKR 995

int melody[] = {NOTE_D3, NOTE_B3, 233};
int tempo[] = {8, 8, 8};
int melody2[] = {466, NOTE_E5, NOTE_C5};
int tempo2[] = {8, 4, 4};

int mode = 0;
int grey = 0;
int greyOld = 0;
int greyTarget = 0;
int speed = 20;
int speedStepSize = 10;
int irBits = 0;

int inBuffer[64];
bool isReading = 1;
short int i;
short int j;

int sensorBL = analogRead(SBL);
int sensorBR = analogRead(SBR);
int baseLV_L = 1023;
int baseLV_R = 1023;

void setupLineTracer(){
  for (int i = 0; i < 100; i++)
  {
    baseLV_L  = min(analogRead(SBL), baseLV_L);
    baseLV_R  = min(analogRead(SBR), baseLV_R);
  }

  //in case it goes to low add threshold of 50
  baseLV_L += 50;
  baseLV_R += 50;

  EEPROM.write(EEP_LINE_SEN_BASE_LH, (baseLV_L >> 8) & 0xff);
  EEPROM.write(EEP_LINE_SEN_BASE_LL, baseLV_L & 0xff);

  EEPROM.write(EEP_LINE_SEN_BASE_RH, (baseLV_R >> 8) & 0xff);
  EEPROM.write(EEP_LINE_SEN_BASE_RL, baseLV_R & 0xff);
}

void stopAndBeep(){
  int i;
  if(grey == greyTarget){
    DCMove(right,15);
    delay(800);
    DCMove(stop,speed);
    for(i=0;i<grey;i++){
      tone(MELODY_PIN, 180);
      delay(250);
      noTone(MELODY_PIN);
      delay(250);
    }
    mode = 0;
    greyTarget = 0;
  }
}

void setup()
{
  Serial.begin(115200);
  LowBatCheck();        //  Low Battery check - 3.7v
  initialize();
  setupLineTracer();
  LedDisplay(1, 100);
}

void loop()
{
  if (ReadVoltage() < 3.7)  LEDColorR(100); //  Low battery, red color
  else if (ReadMic() > 600) LEDColorG(100); //  bright 0~100 ,100: always on
  else  LEDColorG(0); //0: off

  if(mode == 1){
    sensorBL = analogRead(SBL);
    sensorBR = analogRead(SBR);
    
    if (sensorBL < GREYL1 && sensorBR < GREYR1)   DCMove(forward, speed);
    else if (sensorBL > GREYL1 && sensorBR > GREYR1 && sensorBL < GREYL2 && sensorBR < GREYR2 && grey != 1) grey = 1;
    else if (sensorBL > GREYL1 && sensorBR > GREYR1 && sensorBL < GREYL2 && sensorBR < GREYR2 && grey == 1) DCMove(forward, speed);
    else if (sensorBL > GREYL2 && sensorBR > GREYR2 && sensorBL < GREYL3 && sensorBR < GREYR3 && grey != 2) grey = 2;
    else if (sensorBL > GREYL2 && sensorBR > GREYR2 && sensorBL < GREYL3 && sensorBR < GREYR3 && grey == 2) DCMove(forward, speed);
    else if (sensorBL > GREYL3 && sensorBR > GREYR3 && sensorBL < BLACKL && sensorBR < BLACKR && grey != 3) grey = 3;
    else if (sensorBL > GREYL3 && sensorBR > GREYR3 && sensorBL < BLACKL && sensorBR < BLACKR && grey == 3) DCMove(forward, speed);
    else if (sensorBL > BLACKL && sensorBR < BLACKR)    DCMove(right, 15);
    else if (sensorBR > BLACKR && sensorBL < BLACKL)    DCMove(left, 15);
    else if (sensorBL > BLACKL && sensorBR > BLACKR == 0)   DCMove(left, 15);
    else if (sensorBL > BLACKL && sensorBR > BLACKR == 1)   DCMove(right, 15);

    if (grey != greyOld){
      stopAndBeep();
      greyOld = grey;
    }
  }

  if(isReading == 1)
  {
    //check if the serial monitor has anything sent
    if(Serial.available() > 0)
    {
      inBuffer[i] = int(Serial.read());
      if(inBuffer[i] == 10)
      {
        j = 0;
        isReading = 0;
      }
      else ++i;
    }
  }
  else
  {
    for(j=0;j<i;++j)
    {
      switch(inBuffer[j])
      {
        case 64: // character "@"
          mode = 0;
          DCMotor(M1, CCW, inBuffer[j+1]);
          DCMotor(M2, CW, inBuffer[j+2]);
          j=i;
          break;
        case 65: // character "A"
          mode = 0;
          DCMotor(M1, CCW, inBuffer[j+1]);
          DCMotor(M2, CCW, inBuffer[j+2]);
          j=i;
          break;
        case 66: // character "B"
          mode = 0;
          DCMotor(M1, CW, inBuffer[j+1]);
          DCMotor(M2, CW, inBuffer[j+2]);
          j=i;
          break;
        case 67: // character "C"
          mode = 0;
          DCMotor(M1, CW, inBuffer[j+1]);
          DCMotor(M2, CCW, inBuffer[j+2]);
          j=i;
          break;
        case 75: // letter "K"
          mode = 1;
          break;
  
        //------------------------------------------------------------------------
        case 76: //character "L"
          //Print all the data
          //top Left IR sensor
          Serial.print(analogRead(SFL));
          Serial.print(",");
          //top Middle IR
          Serial.print(analogRead(SFF));
          Serial.print(",");
          //top Right IR sensor
          Serial.print(analogRead(SFR));
          Serial.print(",");
          //Bottom Left IR sensor
          Serial.print(analogRead(SBL));
          Serial.print(",");
          //Bottom Right IR sensor
          Serial.print(analogRead(SBR));
          Serial.print(",");
          //Read Voltage of battery
          Serial.print(ReadVoltage());
          Serial.print(",");
          //Read the MIC
          Serial.println(ReadMic());
          break;

        //------------------------------------------------------------------------
        case 77:// character "M"
          mode = 0;
          DCMove(forward,speed);
          break;

        //------------------------------------------------------------------------
        case 78:// character "N"
          mode = 0;
          DCMove(backward,speed);
          break;
  
        //------------------------------------------------------------------------
        case 79:// character "O"
          mode = 0;
          DCMove(left,speed);
          break;
  
        //------------------------------------------------------------------------
        case 80://character "P"
          mode = 0;
          DCMove(right,speed);
          break;
  
        //------------------------------------------------------------------------
        case 81: //character "Q"
          mode = 0;
          DCMove(stop,speed);
          break;

        case 82: //character "R"
          if(analogRead(SBL)>900) irBits = 10;
          else irBits = 0;
          if(analogRead(SBR)>900) irBits++;
          Serial.println(irBits);
          break;
  
        //------------------------------------------------------------------------
        //MOTOR SPEED
        //========================================================
        case 86: //character "V"
          speed = speed - speedStepSize;//decrease the speed
          if(speed<0)
          {
            speed = 0;
          }
          break;
  
        //========================================================
        case 87: //character "W"
          speed = speed + speedStepSize;//increase the speed
          if(speed>100)
          {
            speed = 100;
          }
          break;


        case 90: //character "Z"
          //Currently placing dummy variables
          //since RoPi library is expecting data
          Serial.print("0");
          Serial.print(" ");
          Serial.print("0");
          Serial.print(" ");
          Serial.print("0");
          Serial.print(" ");
          Serial.print(speed);
          Serial.print(" ");
          Serial.print("0");
          Serial.print(" ");
          Serial.print("0");
          Serial.print(" ");
          Serial.println("0");
          //Serial.println(" ");
          break;

        //========================================================
        case 111: //character "o"
          SoundProcess(melody, tempo, 3);
          break;
    
        //========================================================
        case 112: //character "p"
          SoundProcess(melody2, tempo2, 3);
          break;

        //========================================================
        case 113: //character "q"
          greyTarget = 1;
          mode = 1;
          break;
          
        //========================================================
        case 114: //character "r"
          greyTarget = 2;
          mode = 1;
          break;
          
        //========================================================
        case 115: //character "s"
          greyTarget = 3;
          mode = 1;
          break;
  
        //========================================================
        default:
          break;
      }
    }
    i=0;
    isReading=1;
  }
}
