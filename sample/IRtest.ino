#include "config.h"
#include "ex_Linky.h"
#include "ex_Unplugged.h"
#include "RokitFirmata.h"

int sensorBL, sensorBR, BLthresh, BRthresh;
int state = 0;
int incomingByte = 0;
int speed = 20;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  switch(state){
    case 0:
      Serial.println("Enter a number from 0-9.");
      DCMove(stop,speed);
      state = 1;
      break;
    case 1:
      if(Serial.available()>0){
        incomingByte = Serial.read();
        if(incomingByte < 48 || incomingByte > 57) Serial.println("Invalid input. Try again.");
        else{
          incomingByte %= 48;
          incomingByte++;
          Serial.print("Going to square: ");
          Serial.println(incomingByte);
          switch(incomingByte){
            case 1:
              BLthresh = 730;
              BRthresh = 745;
              break;
            case 2:
              BLthresh = 739;
              BRthresh = 755;
              break;
            case 3:
              BLthresh = 812;
              BRthresh = 817;
              break;
            case 4:
              BLthresh = 859;
              BRthresh = 853;
              break;
            case 5:
              BLthresh = 880;
              BRthresh = 887;
              break;
            case 7:
            case 6:
              BLthresh = 924;
              BRthresh = 925;
              break;
            case 10:
            case 9:
            case 8:
              BLthresh = 941;
              BRthresh = 961;
              break;
            default:
              break;
          }
          DCMove(forward,speed);
          state = 2;
        }
      }
      break;
    case 2:
      sensorBL = analogRead(A3);
      sensorBR = analogRead(A4);
      if(sensorBL > BLthresh || sensorBR > BRthresh){
        Serial.println("Finished.");
        state = 0;
      }
      break;
    default:
      break;
  }
}
