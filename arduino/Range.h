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

bool init();

/// Returns the range detected by the short range ir sensor in inches
double shortRangeIr();

///Returns the range detected by infrared in inches
/// Samples determines how many measurements to average while excluding outliers
/// Each sample takes 20ms to measure
double longRangeIr(int samples = 6);

/// Uses both short and long range ir to get an accurate distance measurement in inches
double actualRange();

/// Returns a ProxCheck
ProxCheck proximityCheck();

}

#endif
