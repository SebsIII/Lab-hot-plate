#include <Arduino.h>
#include <TM1637Display.h>
#include "MAX6675.h"

// Module connection pins (Digital Pins)
#define CLK 3
#define DIO 2

const int dataPin   = 8;
const int clockPin  = 10;
const int selectPin = 9;

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000

TM1637Display display(CLK, DIO);
MAX6675 thermoCouple(selectPin, dataPin, clockPin);

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  thermoCouple.begin();
  thermoCouple.setSPIspeed(4000000);

  display.setBrightness(3);
  display.showNumberDec(5385);
}

void loop()
{
  delay(1000);
  thermoCouple.read();
  float temp = thermoCouple.getCelsius();
  Serial.println(temp);
  display.poi
  display.showNumberDec(temp * 100, 0x80 >> 1);
  delay(500);
}
