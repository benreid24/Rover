#ifndef ERROR_H
#define ERROR_H

#include <Arduino.h>

namespace Error {

enum Type {
  Fatal,
  Nonfatal
};

void quit(String error, Type type);

void message(String error, Type type);
  
}

#endif
