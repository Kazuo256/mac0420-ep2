
#include <cstdio>

#include "getglut.h"
#include "task.h"

namespace ep2 {

void Object::add_model (Model& model) {
  models_.push_back(model);
}

void Object::update () {
  updater_(*this);
}

}

