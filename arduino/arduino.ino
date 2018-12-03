#include "Servos.h"
#include "IMU.h"
#include "Motors.h"
#include "Range.h"
#include "Control.h"
#include "LEDs.h"
#include "Error.h"

void setup() {
  Serial.begin(9600);
  LEDs::init();
  Range::init();
  Servos::init();
  Motors::init();
  if (!IMU::init()) {
    Error::quit("Failed to initialize IMU", Error::Fatal);
  }

  LEDs::powerOnSequence();
}

void loop() {
  Control::setHeading(180);
  delay(2000);
  Control::setHeading(0);
  delay(2000);
}
