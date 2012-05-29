
#include <cstdio>

#include "getglut.h"
#include "model.h"

namespace ep2 {
namespace obj {

void Model::render () {
  if (!visible_) return;
  renderer_();
}

} // namespace obj
} // namespace ep2

