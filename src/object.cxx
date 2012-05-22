
#include <cstdio>

#include "getglut.h"
#include "object.h"

namespace ep1 {

void Object::update () {
  updater_(*this);
}

}

