#ifndef RANGE_H
#define RANGE_H

namespace Range {

void init();

/// Returns the range detected by sonar in inches
double sonarRange();

///Returns the range detected by infrared in inches
double infraredRange();

}

#endif
