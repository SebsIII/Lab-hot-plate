#include <Arduino.h>
#include <TM1637Display.h>
#include "MAX6675.h"

#define DisplayCLK 3
#define DisplayDIO 2

#define ThermData   8
#define ThermClock   10
#define ThermSelect  9

#define SSR 4

#define STARTUP_DELAY  1000
#define CLOCK_DELAY 1500

TM1637Display display(DisplayCLK, DisplayDIO);
MAX6675 thermoCouple(ThermSelect, ThermData, ThermClock);

void setup()
{
  SPI.begin();
  thermoCouple.begin();
  thermoCouple.setSPIspeed(4000000);

  display.setBrightness(1);

  //Init sensors
  pinMode(SSR, OUTPUT);

  delay(STARTUP_DELAY);
}

void loop()
{
  thermoCouple.read();
  float temp = thermoCouple.getCelsius();
  display.showNumberDecEx(temp * 100, 0b01000000, true);
  if(temp >= 22){
    digitalWrite(SSR, HIGH);
  } else {
    digitalWrite(SSR, LOW);
  }
  delay(CLOCK_DELAY);
}
