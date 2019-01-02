
#include <MPU6050_tockn.h>

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
MPU6050 mpu6050(Wire);

LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// the setup routine runs once when you press reset:
void setup() {
  Wire.begin();
   lcd.init();                      // initialize the lcd 
  lcd.init();
   lcd.backlight();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  // initialize serial communication at 9600 bits per second:
  //Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
 mpu6050.update();
  lcd.setCursor(0,0);
  lcd.print(mpu6050.getAccAngleX());
  lcd.setCursor(7,0);
  lcd.print(mpu6050.getAccAngleY());
  lcd.setCursor(0,1);
  lcd.print(mpu6050.getGyroAngleZ());
  lcd.setCursor(7,1);
  lcd.print(mpu6050.getTemp());
  delay(50);   // delay in between reads for stability
 lcd.clear();
}




