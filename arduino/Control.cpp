#include "Control.h"
#include "IMU.h"
#include "Motors.h"
#include <Arduino.h>

namespace Control {

namespace {

/// Returns h1-h2 but accounts for 360 wrap
int getHeadingDifference(int h1, int h2) {
  return min(abs(h1-h2), abs(abs(h1-h2)-360));
}

// Returns Left or Right whichever is shorter to go from h1 to h2
Motors::Turn getShorterDir(int h1, int h2) {
  int rightThresh = h1+180;
  if (rightThresh > 360) {
    if (h2<=360 && h2>=h1)
      return Motors::Right;
    else
      return ((rightThresh-360) > h2)?(Motors::Right):(Motors::Left);
  }
  return (h2 >= h1 && h2<=rightThresh)?(Motors::Right):(Motors::Left);
}

int normalizeHeading(int h) {
  while (h < 0)
    h += 360;
  return h%360;
}

int getTurnSpeed(int h1, int h2) {
  int diff = getHeadingDifference(h1, h2);
  int spd = map(diff, 0, 60, 12, 50);
  return (spd>50)?(50):(spd);
}

}

void setHeading(int heading) {
  heading = normalizeHeading(heading);
  int currentHeading = IMU::getRelativeHeading();
  Motors::Turn dir = getShorterDir(currentHeading, heading);
  while (getHeadingDifference(heading, currentHeading) > 3) {
    Motors::turn(dir, getTurnSpeed(heading, currentHeading));
    currentHeading = IMU::getRelativeHeading();
    int d = getHeadingDifference(heading, currentHeading);
    delay(5);
  }
  Motors::brake();
}

}
