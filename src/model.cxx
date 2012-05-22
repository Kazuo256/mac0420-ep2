
#include <cstdio>

#include "getglut.h"

namespace ep2 {

void Model::render () const {
  if (!visible_) return;
  renderer_();
}

}
