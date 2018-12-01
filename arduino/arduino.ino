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
  Control::setHeading(180);
  delay(2000);
  Control::setHeading(0);
}

void loop() {
  delay(50);
}
