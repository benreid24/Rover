#ifndef IMU_H
#define IMU_H

namespace IMU {

struct Vector {
  double x, y, z;
  Vector() { x = y = z = 0; }
  Vector(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }
};

/// Initializes the IMU
bool init();

/// Returns the temperature in C
int getTemp();

/// Returns the compass heading
double getCompassHeading();

/// Returns the current heading with respect to when first turned on
double getRelativeHeading();

/// Returns raw accelerometer values
Vector getRawAccel();

/// Returns raw gyroscope values
Vector getRawGyro();

}

#endif
