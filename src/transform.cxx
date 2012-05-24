

#include "transform.h"

namespace ep2 {

void Transform::composition (Matrix matrix) {
  if (matrix.size() == 4) {
    Matrix comp;
    for (int i = 0; i < 4; i++) {
      comp[i] = (matrix[0]*matrix_[i].x())+
                (matrix[1]*matrix_[i].y())+
                (matrix[2]*matrix_[i].z())+
                (matrix[3]*matrix_[i].a());
    }
    matrix_ = comp;
  }
}

} // namespace ep2
