
#include <cstdio>

#include "getglut.h"
#include "model.h"

namespace ep2 {
namespace obj {

void Model::render () const {
  if (visible_ == false) return;
  renderer_();
}

} // namespace obj
} // namespace ep2

