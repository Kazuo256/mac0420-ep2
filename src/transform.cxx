

#include "transform.h"

namespace ep2 {

void Transform::composition (const Matrix& matrix) {
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

void Transform::pushmodel (const Model& model) {
 modelvec_.push_back(model); 
}

void Transform::pushtransform (const Transform& transform) {
  transformvec_.push_back(transform);
}

} // namespace ep2
