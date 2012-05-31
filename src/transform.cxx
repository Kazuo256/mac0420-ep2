

#include "transform.h"
#include "obj/model.h"

namespace ep2 {

Transform::Matrix::Matrix (const Base4D& xaxis,
                           const Base4D& yaxis,
                           const Base4D& zaxis,
                           const Base4D& origin) {
  columns[0] = xaxis;
  columns[1] = yaxis;
  columns[2] = zaxis;
  columns[3] = origin;
}

void Transform::set_identity () {
  matrix_ = Matrix();
}

void Transform::set_position (const Point4D& position) {
  matrix_[3] = position-Point4D();
}

void Transform::translate (const Vec4D& translation) {
  matrix_[3] = Point4D(matrix_[3]) + translation;
}

void Transform::composition (const Matrix& matrix) {
    Matrix comp;
    for (int i = 0; i < 4; i++) {
      comp[i] = (Vec4D(matrix[0])*matrix_[i].x())+
                (Vec4D(matrix[1])*matrix_[i].y())+
                (Vec4D(matrix[2])*matrix_[i].z())+
                (Vec4D(matrix[3])*matrix_[i].a());
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
