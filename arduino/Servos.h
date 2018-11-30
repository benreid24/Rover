#ifndef PWMCONTROL_H
#define PWMCONTROL_H

namespace Servos {

/// Initializes everything
void init();

/// Sets the raw PWM pulse on the given channel
void setRaw(int channel, int pulseUp, int pulseDown);

/// Sets the position of the arm rotation. Pos is [-100, 100]
void setSonarArmPan(int pos);

/// Sets te position of the arm tilt. Pos is [-100, 100]
void setSonarArmTilt(int pos);

}

#endif
