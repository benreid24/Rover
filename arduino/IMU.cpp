#include "IMU.h"
#include <Adafruit_BNO055.h>
#include <math.h>

namespace IMU {

namespace{
// Possible vector values can be:
// - VECTOR_ACCELEROMETER - m/s^2
// - VECTOR_MAGNETOMETER  - uT
// - VECTOR_GYROSCOPE     - rad/s
// - VECTOR_EULER         - degrees
// - VECTOR_LINEARACCEL   - m/s^2
// - VECTOR_GRAVITY       - m/s^2
Adafruit_BNO055 bno = Adafruit_BNO055(); 
}

bool init() {
  return bno.begin();
}

int getTemp() {
  return bno.getTemp();
}

double getRelativeHeading() {
  return bno.getVector(Adafruit_BNO055::VECTOR_EULER).x();
}

double getCompassHeading() {
  imu::Vector<3> mag = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  return atan2(mag.z(), mag.y())*180/3.1415;
}

Vector getRawAccel() {
  imu::Vector<3> v = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  return Vector(v.x(), v.y(), v.z());
}

Vector getRawGyro() {
  imu::Vector<3> v = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  return Vector(v.x(), v.y(), v.z());
}

}
