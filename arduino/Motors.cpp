#include "Motors.h"
#include <Arduino.h>

namespace Motors {

namespace {

enum Pins {
  IN1 = 0,
  IN2 = 1,
  PWM = 2
};

enum Motor {
  LeftMotor = 0,
  RightMotor = 1
};
  
const int motorPins[2][3] = {
  {4, 5, 6}, /// Green, Blue, Purple
  {8, 10, 9}  /// White, Gray, Purple
};

const int standByPin = 7; /// Yellow

void moveMotor(Motor motor, int spd, Direction dir){
  const boolean inPins[] = {LOW, HIGH, LOW};
  const boolean* inPin = inPins + (int)dir;

  digitalWrite(motorPins[motor][IN1], inPin[0]);
  digitalWrite(motorPins[motor][IN2], inPin[1]);
  analogWrite(motorPins[motor][PWM], spd);
}

}

void init() {
  pinMode(standByPin, OUTPUT);
  for (int i = 0; i<2; ++i) {
    for (int j = 0; j<3; ++j)
      pinMode(motorPins[i][j], OUTPUT);
  }
  brake();
}

void brake(){
  digitalWrite(standByPin, LOW); 
}

void releaseBrake(){
  digitalWrite(standByPin, HIGH); 
}

void moveStraight(Direction dir, int spd) {
  spd = map(spd, 0, 100, 0, 255);
  moveMotor(LeftMotor, spd, dir);
  moveMotor(RightMotor, spd, dir);
  releaseBrake();
}

void turn(Turn dir, int spd) {
  spd = map(spd, 0, 100, 0, 255);
  switch (dir) {
    case Left:
      moveMotor(LeftMotor, spd, Backward);
      moveMotor(RightMotor, spd, Forward);
      releaseBrake();
      break;
    case Right:
      moveMotor(LeftMotor, spd, Forward);
      moveMotor(RightMotor, spd, Backward);
      releaseBrake();
      break;
  }
}

}
