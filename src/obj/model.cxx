
#include <cstdio>

#include "getglut.h"
#include "model.h"

namespace ep2 {

void Model::render () {
  if (!visible_) return;
  renderer_();
}

}
