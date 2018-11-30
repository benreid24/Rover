#ifndef MOTORS_H
#define MOTORS_H

namespace Motors {

enum Direction {
  Forward = 0,
  Backward = 1
};

enum Turn {
  Left = 0,
  Right = 1
};

void init();

void brake();

void releaseBrake();

/// spd is [0, 100]
void moveStraight(Direction dir, int spd);

/// spd is [0, 100]
void turn(Turn dir, int spd);

}

#endif
