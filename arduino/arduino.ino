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

  const float fdist = Range::actualRange();
  Servos::setSonarArmPan(100);
  delay(1000);
  const float rdist = Range::actualRange();
  Servos::setSonarArmPan(-100);
  delay(1500);
  const float ldist = Range::actualRange();

  Servos::setSonarArmPan(0);
  if (ldist > fdist || rdist > fdist) {
    if (ldist > rdist)
      Control::setHeading(90);
    else
      Control::setHeading(-90);
  }
}

void loop() {
  Control::moveForward();
  Control::moveBackward(4);
  
  Servos::setSonarArmPan(100);
  delay(1000);
  const float rdist = Range::actualRange();
  Servos::setSonarArmPan(-100);
  delay(1500);
  const float ldist = Range::actualRange();
  
  Servos::setSonarArmPan(0);
  if (ldist > rdist)
    Control::setHeading(90);
  else
    Control::setHeading(-90);
}
