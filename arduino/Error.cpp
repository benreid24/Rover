#include "Error.h"
#include "LEDs.h"

namespace Error {

namespace {

void printErrorType(Type type) {
  switch (type) {
    case Fatal:
      Serial.print("FATAL: ");
      break;
    case Nonfatal:
      Serial.print("NONFATAL: ");
      break;
    default:
      Serial.print("UNKNOWN ERROR TYPE: ");
  }
}

}

void quit(String err, Type type) {
  printErrorType(type);
  Serial.print(err);

  LEDs::fatalErrorState();
}

void message(String err, Type type) {
  printErrorType(type);
  Serial.print(err);

  LEDs::errorState();
}

}
