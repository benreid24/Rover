#ifndef ERROR_H
#define ERROR_H

#include <Arduino.h>

namespace Error {

enum Type {
  Fatal
};

void quit(String error, Type type);
  
}

#endif
