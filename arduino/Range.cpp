#include <Arduino.h>
#include <Adafruit_VCNL4010.h>
#include <Adafruit_VL53L0X.h>
#include "Range.h"

namespace Range {

namespace {

/**


18 -> 0
16 -> 0
14 -> 1    1.0714
12 -> 1.5  1.125
6 -> 1.6   1.266
3 -> 1     1.333
1 -> 1.5   1.5

Volts -> in
2.08 -> 62
2.15 -> 55
2.58 -> 40

Volts -> 1/in
2.08 -> 0.016129
2.15 -> 0.0181818
2.58 -> 0.025

 */
 
const double inPerMm = 1.0/24.1;
const double shortIrCorrectionThresh = 13.8;
const double shortIrCorrection = -1.3;

const double y1 = 2.08, y2 = 2.58;
const double x1 = 0.016129, x2 = 0.025;
const double voltsPerTick = 5.0/1024.0;
const double slope = (y2-y1)/(x2-x1);
const double yint = y1-slope*x1;

const int blockedThresh = 3400;
const int impactThresh = 2600;
const int fourInchThresh = 2500;
const int sixInchThresh = 2440;

Adafruit_VCNL4010 prox;
Adafruit_VL53L0X ir;

}

bool init() {
  return ir.begin() && prox.begin();
}

double shortRangeIr() {
  VL53L0X_RangingMeasurementData_t measure;
  ir.rangingTest(&measure, false);
  if (measure.RangeStatus!=4 && measure.RangeMilliMeter<=512) {
    double r = double(measure.RangeMilliMeter)*inPerMm;
    return (r<=shortIrCorrectionThresh)?(r+shortIrCorrection):(r);
  }
  return -1;
}

double longRangeIr(int samples) {
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

double actualRange() {
  double r = shortRangeIr();
  return (r>0)?(r):(longRangeIr(6));
}

ProxCheck proximityCheck() {
  int val = prox.readProximity();
  if (val >= blockedThresh)
    return Blocked;
  if (val >= impactThresh)
    return ImpactIminent;
  if (val >= fourInchThresh)
    return UnderFourInches;
  if (val >= sixInchThresh)
    return UnderSixInches;
  return Clear;
}

}
