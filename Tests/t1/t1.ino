#include <PID_v1.h>
#include "MAX6675.h"
#include <SPI.h>

// ====== MAX6675 PINS ======
#define ThermData    8
#define ThermClock  10
#define ThermSelect  9

// ====== SSR ======
#define SSR_PIN 5

// ====== PID ======
double Setpoint = 120.0;   // °C
double Input = 0;
double Output = 0;

double Kp = 5;    // proportional
double Ki = 0.35;   // integral (slow accumulation)
double Kd = 10;    // derivative (damp overshoot)


// Time-proportional SSR control
const unsigned long WindowSize = 1000; // ms
unsigned long windowStartTime = 0;

// MAX6675 timing
const unsigned long tempInterval = 300; // ms (>=220 ms)
unsigned long lastTempRead = 0;

// Serial print timing
const unsigned long printInterval = 500; // ms
unsigned long lastPrint = 0;

// Objects
MAX6675 thermoCouple(ThermSelect, ThermData, ThermClock);
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(9600);

  // MAX6675 CS must start HIGH
  pinMode(ThermSelect, OUTPUT);
  digitalWrite(ThermSelect, HIGH);

  pinMode(SSR_PIN, OUTPUT);
  digitalWrite(SSR_PIN, LOW);

  SPI.begin();
  thermoCouple.begin();
  thermoCouple.setSPIspeed(4000000);

  windowStartTime = millis();

  myPID.SetOutputLimits(0, WindowSize);
  myPID.SetSampleTime(350);   // match MAX6675 update rate
  myPID.SetMode(AUTOMATIC);

  delay(500); // allow MAX6675 to stabilize
}

void loop() {
  unsigned long now = millis();

  // ---- Read thermocouple at valid rate ----
  if (now - lastTempRead >= tempInterval) {
    lastTempRead = now;
    thermoCouple.read();
    Input = 0.7 * Input + 0.3 * thermoCouple.getCelsius();
  }

  // ---- Safety cutoff ----
  if (Input < 0 || Input > 300 ) {
    digitalWrite(SSR_PIN, LOW);
    myPID.SetMode(MANUAL);
    return;
  }

  // ---- PID compute ----
  myPID.Compute();

  // force PID to zero above setpoint


  if (now - lastPrint >= printInterval) {
    lastPrint = now;

    // Print in CSV format: Temperature, Setpoint, Power
    Serial.print(Input, 1);             // Temperature
    Serial.print(",");                  
    Serial.print(Setpoint, 1);          // Setpoint
    Serial.print(",");
    Serial.println((Output / WindowSize) * 100.0, 0);  // SSR Power %
}


  // ---- Time-proportional SSR control ----
  if (now - windowStartTime > WindowSize) {
    windowStartTime += WindowSize;
  }

  digitalWrite(
    SSR_PIN,
    (Output > (now - windowStartTime)) ? HIGH : LOW
  );

  
}
