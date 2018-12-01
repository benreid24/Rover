#include <Arduino.h>
#include <Adafruit_VCNL4010.h>
#include "Range.h"

namespace Range {

namespace {

const double inchesPerAnalogInput = (5.0/1024.0)/(5.0/512.0);

Adafruit_VCNL4010 ir;

}

void init() {
  ir.begin();
}

double sonarRange() {
  double voltage = analogRead(A0);
  voltage *= 5.0/1024.0;
  return voltage / (5.0/512.0);
}

double infraredRange() {
  return ir.readProximity();
}

}
