#include "Error.h"

namespace Error {

void quit(String err, Type type) {
  switch (type) {
    case Fatal:
      Serial.print("FATAL: ");
      break;
    default:
      Serial.print("UNKNOWN ERROR TYPE: ");
  }
  Serial.print(err);

  //TODO - Visual indicators?
  while (true) { delay(1000); }
}

}
