#include "PWM.h"
#include "IMU.h"
#include "Motors.h"
#include "Error.h"

void setup() {
  Serial.begin(9600);
  PWM::init();
  Motors::init();
  if (!IMU::init()) {
    Error::quit("Failed to initialize IMU", Error::Fatal);
  }
}

void loop() {
}
