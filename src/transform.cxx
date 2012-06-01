

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

void Transform::Matrix::makematrix (double* matrix) const {

  for ( int j = 0; j < 16; j+=4 ) 
    for ( int i = 0; i < 4; i++ )
      matrix[j+i] = (*this)[j/4].val()[i];

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
      comp[i] = (matrix[0]*matrix_[i].x())+
                (matrix[1]*matrix_[i].y())+
                (matrix[2]*matrix_[i].z())+
                (matrix[3]*matrix_[i].w());
    }
    matrix_ = comp;
}

void Transform::pushmodel (const obj::Model& model) {
  modelvec_.push_back(model); 
}

void Transform::pushtransform (const Transform& transform) {
  transformvec_.push_back(transform);
}

void Transform::dump () const {
  matrix_[0].dump();
  matrix_[1].dump();
  matrix_[2].dump();
  matrix_[3].dump();
}

Transform Transform::identity () {
  return Transform(Matrix());
}

} // namespace ep2
