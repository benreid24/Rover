#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

namespace PWM {

namespace {
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
}

// you can use this function if you'd like to set the pulse length in seconds
// e.g. setServoPulse(0, 0.001) is a ~1 millisecond pulse width. its not precise!
void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  
  pulselength = 1000000;
  pulselength /= 50;
  pulselength /= 4096;
  pulse *= 1000000;  // convert to us
  pulse /= pulselength;

  pwm.setPWM(n, 0, pulse);
}

void init() {
  pwm.begin();
  pwm.setPWMFreq(50);
}

void setRaw(int channel, int pulseUp, int pulseDown) {
  pwm.setPWM(channel, pulseUp, pulseDown);
}

void setContinuousServo(int channel, int spd) {
  const double middle = 0.00145, upper = 0.002, lower = 0.001;
  double dspd = double(spd)/100;
  if (spd > 0)
    setServoPulse(channel, dspd*(upper-middle)+middle);
  else if (spd < 0)
    setServoPulse(channel, dspd*(middle-lower)+middle);
  else
    setServoPulse(channel, middle);
}

}
