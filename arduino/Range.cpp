#include <Arduino.h>
#include <Adafruit_VCNL4010.h>
#include "Range.h"

namespace Range {

namespace {

/**

Volts -> in
2.08 -> 62
2.15 -> 55
2.58 -> 40

Volts -> 1/in
2.08 -> 0.016129
2.15 -> 0.0181818
2.58 -> 0.025

 */
 
const double inchesPerAnalogInput = (5.0/1024.0)/(5.0/512.0);

const double y1 = 2.08, y2 = 2.58;
const double x1 = 0.016129, x2 = 0.025;
const double voltsPerTick = 5.0/1024.0;
const double slope = (y2-y1)/(x2-x1);
const double yint = y1-slope*x1;

const int blockedThresh = 3400;
const int impactThresh = 2600;
const int fourInchThresh = 2500;
const int sixInchThresh = 2440;

Adafruit_VCNL4010 ir;

}

void init() {
  ir.begin();
}

double sonar() {
  return double(analogRead(A0))*inchesPerAnalogInput;
}

double infrared(int samples) {
  double measurements[samples];
  double average = 0;
  double mn = 100000, mx = 0;
  
  for (int i = 0; i<samples; ++i) {
    measurements[i] = analogRead(A1);
    measurements[i] *= voltsPerTick;
    measurements[i] -= yint;
    measurements[i] /= slope;
    measurements[i] = 1/measurements[i];
    average += measurements[i];
    if (measurements[i] < mn)
      mn = measurements[i];
    if (measurements[i] > mx)
      mx = measurements[i];
    delay(18);
  }
  return (average-mn-mx)/(samples-2);
}

ProxCheck proximityCheck() {
  int prox = ir.readProximity();
  if (prox >= blockedThresh)
    return Blocked;
  if (prox >= impactThresh)
    return ImpactIminent;
  if (prox >= fourInchThresh)
    return UnderFourInches;
  if (prox >= sixInchThresh)
    return UnderSixInches;
  return Clear;
}

}
