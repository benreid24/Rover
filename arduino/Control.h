#ifndef CONTROL_H
#define CONTROL_H

namespace Control {

/// Turns in place until the heading is within the given tolerance
void setHeading(int heading);

/// Travels forward for the given distance, in inches. Pass -1 to travel until an obstacle is reached
void moveForward(float inches = -1, int spd = 100);

/// Travels backward for the given distance. Warning, no collision avoidance is available in reverse
void moveBackward(float inches, int spd = 50);

}

#endif
