
#include <cstdio>

#include "getglut.h"
#include "task.h"

namespace ep2 {

void Object::update () {
  updater_(*this);
}

}

