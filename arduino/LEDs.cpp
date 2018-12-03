#include "LEDs.h"
#include <Arduino.h>

namespace LEDs {

namespace {

const int powerLed = A3;
const int activeLed = A2;
const int errorLed = A4;

}

void init() {
  pinMode(powerLed, OUTPUT);
  pinMode(activeLed, OUTPUT);
  pinMode(errorLed, OUTPUT);

  digitalWrite(powerLed, HIGH);
  digitalWrite(activeLed, LOW);
  digitalWrite(errorLed, LOW);
}

void powerOnSequence() {
  int period = 700;

  digitalWrite(errorLed, HIGH);
  while (period >= 50) {
    digitalWrite(activeLed, HIGH);
    delay(period);
    digitalWrite(activeLed, LOW);
    delay(period);
    period -= 50;
  }
  digitalWrite(activeLed, HIGH);
  delay(500);
  digitalWrite(errorLed, LOW);
}

}
