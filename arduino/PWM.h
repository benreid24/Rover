#ifndef PWMCONTROL_H
#define PWMCONTROL_H

namespace PWM {

/// Initializes everything
void init();

/// Sets the raw PWM pulse on the given channel
void setRaw(int channel, int pulseUp, int pulseDown);

/// Sets the speed of the continuous servo. spd is [-100, 100]
void setContinuousServo(int channel, int spd);

}

#endif
