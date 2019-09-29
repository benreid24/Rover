#include "Servos.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

namespace Servos {

namespace {
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

const int refreshRate = 50;
const int sonarArmPanChannel = 14;
const int sonarArmTiltChannel = 15;

const int armPanMinPulse = 0.00053 * double(refreshRate) * 4096.0;
const int armPanMaxPulse = 0.00225 * double(refreshRate) * 4096.0;
const int armPanMidPulse = 0.00133 * double(refreshRate) * 4096.0;

const int armTiltMinPulse = 0.00090 * double(refreshRate) * 4096.0;
const int armTiltMaxPulse = 0.00220 * double(refreshRate) * 4096.0;
const int armTiltMidPulse = 0.00165 * double(refreshRate) * 4096.0;

float currentArmPan = 0;
const float panRate = 0.1; //percent/ms

void setSonarArmPanActual(int pos) {
  if (pos < 0)
    setRaw(sonarArmPanChannel, 0, map(pos, -100, 0, armPanMinPulse, armPanMidPulse));
  else if (pos > 0)
    setRaw(sonarArmPanChannel, 0, map(pos, 0, 100, armPanMidPulse, armPanMaxPulse));
  else
    setRaw(sonarArmPanChannel, 0, armPanMidPulse);
}

void setSonarArmTiltActual(int pos) {
  pos = 0 - pos;
  if (pos < 0)
    setRaw(sonarArmTiltChannel, 0, map(pos, -100, 0, armTiltMinPulse, armTiltMidPulse));
  else if (pos > 0)
    setRaw(sonarArmTiltChannel, 0, map(pos, 0, 100, armTiltMidPulse, armTiltMaxPulse));
  else
    setRaw(sonarArmTiltChannel, 0, armTiltMidPulse);
}

}

void init() {
  pwm.begin();
  pwm.setPWMFreq(50);
  setSonarArmPanActual(0);
  setSonarArmTilt(0);
}

void setRaw(int channel, int pulseUp, int pulseDown) {
  pwm.setPWM(channel, pulseUp, pulseDown);
}

void setSonarArmPan(int pos) {
  const float d = pos > currentArmPan ? panRate : -panRate;
  while (abs(currentArmPan-pos) >= panRate*2) {
    currentArmPan += d;
    setSonarArmPanActual(currentArmPan);
    delay(1);
  }
}

void setSonarArmTilt(int pos) {
  pos = 0 - pos;
  if (pos < 0)
    setRaw(sonarArmTiltChannel, 0, map(pos, -100, 0, armTiltMinPulse, armTiltMidPulse));
  else if (pos > 0)
    setRaw(sonarArmTiltChannel, 0, map(pos, 0, 100, armTiltMidPulse, armTiltMaxPulse));
  else
    setRaw(sonarArmTiltChannel, 0, armTiltMidPulse);
}

}
