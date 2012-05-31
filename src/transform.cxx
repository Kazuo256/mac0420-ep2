

#include "transform.h"
#include "obj/model.h"

namespace ep2 {

Transform::Matrix::Matrix (const Vec4D& xaxis,
                           const Vec4D& yaxis,
                           const Vec4D& zaxis,
                           const Vec4D& origin) {
  columns[0] = xaxis;
  columns[1] = yaxis;
  columns[2] = zaxis;
  columns[3] = origin;
}

void Transform::composition (const Matrix& matrix) {
    Matrix comp;
    for (int i = 0; i < 4; i++) {
      comp[i] = (matrix[0]*matrix_[i].x())+
                (matrix[1]*matrix_[i].y())+
                (matrix[2]*matrix_[i].z())+
                (matrix[3]*matrix_[i].a());
    }
    matrix_ = comp;
}

void Transform::pushmodel (const obj::Model& model) {
  modelvec_.push_back(model); 
}

void Transform::pushtransform (const Transform& transform) {
  transformvec_.push_back(transform);
}

Transform Transform::identity () {
  return Transform(Matrix());
}

} // namespace ep2
