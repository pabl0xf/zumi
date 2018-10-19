#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SLAVE_ADDRESS 0x04
#define OLED_ADDR 0x3C

int number = 0;
int state = 0;

double bitsPerVolts;

Adafruit_SSD1306 display(-1);

void displayDrawBatt(){
  display.fillRect(113,23,127,31,BLACK);
  display.drawLine(114,24,125,24,WHITE);
  display.drawLine(114,30,125,30,WHITE);
  display.drawLine(114,25,114,29,WHITE);
  display.drawLine(126,25,126,29,WHITE);
  display.drawLine(116,26,116,28,WHITE);
  display.drawLine(117,26,117,28,WHITE);
  display.drawPixel(125,25,WHITE);
  display.drawPixel(125,29,WHITE);
}

long readVccMilliVolts() {
  long result;
  
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);
  ADCSRA |= _BV(ADSC);
  while(bit_is_set(ADCSRA,ADSC));
  result = ADCL;
  result |= ADCH<<8;
  result = 1126400L / result;
  
  return result;
}

void setup()
{
  Wire.begin(SLAVE_ADDRESS);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();
  bitsPerVolts = 1024.0/(readVccMilliVolts()*0.001);
}


void loop()
{
  //if(state == 1) displayNumber();
  display.clearDisplay();
  if(analogRead(A3)/bitsPerVolts < 3.7) displayDrawBatt();
  display.setCursor(0, 0);
  display.print(analogRead(A3)/bitsPerVolts);
  display.display();
  delay(100);
}

