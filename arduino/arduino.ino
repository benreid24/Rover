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
  Servos::init();
  Motors::init();
  if (!Range::init()) {
    Error::message("Failed to initialize full range capabilities", Error::Nonfatal);
  }
  if (!IMU::init()) {
    Error::quit("Failed to initialize IMU", Error::Fatal);
  }

  LEDs::powerOnSequence();
}

void loop() {
  Serial.println(Range::actualRange());
  delay(300);
}
