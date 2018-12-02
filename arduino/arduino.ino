#include "Servos.h"
#include "IMU.h"
#include "Motors.h"
#include "Range.h"
#include "Control.h"
#include "Error.h"

void setup() {
  Serial.begin(9600);
  Range::init();
  Servos::init();
  Motors::init();
  if (!IMU::init()) {
    Error::quit("Failed to initialize IMU", Error::Fatal);
  }
}

void loop() {
  Serial.print(Range::infrared(5)); Serial.print(" | "); Serial.println(Range::sonar());
}
