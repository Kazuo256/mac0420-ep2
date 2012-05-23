
#include <cstdio>

#include "getglut.h"
#include "task.h"

namespace ep2 {

void Task::add_model (Model& model) {
  models_.push_back(model);
}

void Task::update () {
  updater_(*this);
}

}

