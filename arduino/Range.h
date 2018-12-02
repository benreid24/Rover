#ifndef RANGE_H
#define RANGE_H

namespace Range {

enum ProxCheck {
  Clear = 0,
  UnderSixInches = 1,
  UnderFourInches = 2,
  ImpactIminent = 3,
  Blocked = 4
};

void init();

/// Returns the range detected by sonar in inches
double sonar();

///Returns the range detected by infrared in inches
/// Samples determines how many measurements to average while excluding outliers
/// Each sample takes 20ms to measure
double infrared(int samples = 6);

/// Returns a ProxCheck
ProxCheck proximityCheck();

}

#endif
