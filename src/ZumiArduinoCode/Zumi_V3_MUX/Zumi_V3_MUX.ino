//V3 Zumi
//Select Arduino Pro Mini 328 under board
//Multiplexer

//A7 is multiplex out
# define MUX_OUTPUT 21
//A1=S0, A2=S1, A3=S2 

#define MUX_S0 15
#define MUX_S1 16
#define MUX_S2 17

# define FRONT_LEFT_LED 11
# define FRONT_RIGHT_LED 12
# define BACK_LEFT_LED  10
# define BACK_RIGHT_LED  9

//A0 14, A1 15, A2 16,
//A3 17, A4 18, A5 19,
//A6 20, A7 21

//BUZZER is on pin A0
# define BUZZER_PIN 14

//Battery voltage is on pin A6
#define BATT_LVL_PIN 20

#define IR_REMREC_PIN 4
//IR receiver is on pin DIG4

# define IR_EMIT_PIN 5
//IR Emitters control pin 
//for the transistors is on DIG 5.
//BE VERY CAREFUL WITH PIN 5

//V3 STILL SAME AS V2
//A3906 Motor Controller is on pins
//IN1 =D3 MLEFTA
//IN2 =D7 MLEFTB
//IN3 =D6 MRIGHTA
//IN4 =D8 MRIGHTB
# define MOTOR_IN1 3
# define MOTOR_IN2 7
# define MOTOR_IN3 6
# define MOTOR_IN4 8

// the setup routine runs once when you press reset:
void setup() {
  delay(1000);
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  //linkyBeep();
  delay(1000);
  //ZumiHonk();

  //setup analog pin for input make sure pullup is used
  //pinMode(A7, INPUT_PULLUP);

  //Motor controller
  pinMode(3,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(8,OUTPUT);

  //IR Led's transistor controll
  pinMode(IR_EMIT_PIN,OUTPUT);
  //analogWrite(IR_EMIT_PIN,100);
  //digitalWrite(5,HIGH);

  //setup analog pins for multiplexer as output
  pinMode(MUX_S0,OUTPUT);
  pinMode(MUX_S1,OUTPUT);
  pinMode(MUX_S2,OUTPUT);

  //choose channel 0 on mux
  digitalWrite(MUX_S0,LOW);
  digitalWrite(MUX_S1,LOW);
  digitalWrite(MUX_S2,LOW);

  pinMode(FRONT_RIGHT_LED,OUTPUT);
  pinMode(FRONT_LEFT_LED,OUTPUT);
  pinMode(BACK_RIGHT_LED,OUTPUT);
  pinMode(BACK_LEFT_LED,OUTPUT);

  //turn on all Zumi Lights
  digitalWrite(FRONT_LEFT_LED,HIGH);
  digitalWrite(FRONT_RIGHT_LED,HIGH);
  digitalWrite(BACK_LEFT_LED,HIGH);
  digitalWrite(BACK_RIGHT_LED,HIGH);
  
}

// the loop routine runs over and over again forever:
void loop() {
 //displayAllIRsensors();
 motorTest();
 
}


void linkyBeep() {
  int frequency = 1000;
  double k = 1.2;
  //(pin, frequency)
  //440, 523, 698
  tone(BUZZER_PIN, 523);
  delay(80 * k);

  noTone(BUZZER_PIN);
  delay(20 * k);

  tone(BUZZER_PIN, 587);
  delay(80 * k);

  noTone(BUZZER_PIN);
  delay(20 * k);

  tone(BUZZER_PIN, 698);
  delay(100 * k);

  noTone(BUZZER_PIN);
  
}



void ZumiHonk() {

  double k = 2;
  //(pin, frequency)
  tone(BUZZER_PIN, 1000);
  digitalWrite(FRONT_LEFT_LED,HIGH);
  digitalWrite(FRONT_RIGHT_LED,HIGH);
  delay(90 * k);
  
  noTone(BUZZER_PIN);
  digitalWrite(FRONT_LEFT_LED,LOW);
  digitalWrite(FRONT_RIGHT_LED,LOW);
  delay(60 * k);

  tone(BUZZER_PIN, 1000);
  digitalWrite(FRONT_LEFT_LED,HIGH);
  digitalWrite(FRONT_RIGHT_LED,HIGH);
  delay(90 * k);


  noTone(BUZZER_PIN);
  
}



int readthisIRSensors(byte indexOfIRSensor)
{
  switch (indexOfIRSensor){
    //--------------------------------------
  case 0:
  //000 = 0
  digitalWrite(15,LOW); 
  digitalWrite(16,LOW);
  digitalWrite(17,LOW); 
  break;
//--------------------------------------
  case 1:
  //001 = 1
  digitalWrite(15,LOW); 
  digitalWrite(16,LOW);
  digitalWrite(17,HIGH); 
  break;
  //--------------------------------------
    case 2:
  //010 = 2
  digitalWrite(15,LOW); 
  digitalWrite(16,HIGH);
  digitalWrite(17,LOW); 
  break;
  //--------------------------------------
  case 3:
  //011 = 3
  digitalWrite(15,LOW); 
  digitalWrite(16,HIGH);
  digitalWrite(17,HIGH); 
  break;
  //--------------------------------------
    case 4:
  //100 = 4
  digitalWrite(15,HIGH); 
  digitalWrite(16,LOW);
  digitalWrite(17,LOW);
break;
//--------------------------------------
  //101 = 5
  digitalWrite(15,HIGH); 
  digitalWrite(16,LOW);
  digitalWrite(17,HIGH);
break;
//--------------------------------------
  case 6:
  //110 = 6
  digitalWrite(15,HIGH); 
  digitalWrite(16,HIGH);
  digitalWrite(17,LOW);
  break;
  //--------------------------------------

  case 7:
  //111 = 7
  digitalWrite(15,HIGH); 
  digitalWrite(16,HIGH);
  digitalWrite(17,HIGH);
  break;
  //--------------------------------------
  
  
  default:
  break;
  }
  return analogRead(MUX_OUTPUT);
}

void displayAllIRsensors()
{
    for(int i=0; i<8;i++){
  Serial.print(readthisIRSensors(i));
  Serial.print(",");
  delay(5);        // delay in between reads for stability
  }
  Serial.println("");
}


void motorTest(){
    
  //turn off motors  
  digitalWrite(3,LOW);
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(8,LOW);
  digitalWrite(FRONT_LEFT_LED,HIGH);
  digitalWrite(FRONT_RIGHT_LED,HIGH);

  delay(1000);

    digitalWrite(FRONT_LEFT_LED,LOW);
  digitalWrite(FRONT_RIGHT_LED,LOW);  
  //turn on motors  
  digitalWrite(3,HIGH);
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(8,LOW);
  delay(1000);

      digitalWrite(FRONT_LEFT_LED,HIGH);
  digitalWrite(FRONT_RIGHT_LED,HIGH);
  //turn on motors  
  digitalWrite(3,LOW);
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(8,LOW);
  delay(1000);

      digitalWrite(FRONT_LEFT_LED,LOW);
  digitalWrite(FRONT_RIGHT_LED,LOW);  
  //turn on motors  
  digitalWrite(3,LOW);
  digitalWrite(7,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(8,LOW);
  delay(1000);

      digitalWrite(FRONT_LEFT_LED,HIGH);
  digitalWrite(FRONT_RIGHT_LED,HIGH);
  //turn on motors  
  digitalWrite(3,LOW);
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(8,HIGH);
  delay(1000);

  digitalWrite(3,LOW);
  digitalWrite(7,LOW);
  digitalWrite(6,LOW);
  digitalWrite(8,LOW);
  digitalWrite(FRONT_LEFT_LED,LOW);
  digitalWrite(FRONT_RIGHT_LED,LOW);  
}

