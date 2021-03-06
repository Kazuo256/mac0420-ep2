

#include "transform.h"
#include "obj/model.h"
#include <cmath>
#include <cstdio>

#define PI 3.14159265

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

void Transform::Matrix::dump () const {
  columns[0].dump();
  columns[1].dump();
  columns[2].dump();
  columns[3].dump();
}

Transform::Matrix Transform::Matrix::operator * (const Matrix& rhs) const {
  Matrix comp;
  for (int i = 0; i < 4; i++) {
      comp[i] = (columns[0]*rhs[i].x())+
                (columns[1]*rhs[i].y())+
                (columns[2]*rhs[i].z())+
                (columns[3]*rhs[i].w());
  }
  return comp;
}

Base4D Transform::Matrix::operator * (const Base4D& rhs) const {
  Base4D comp;
  comp = (columns[0]*rhs.x())+
         (columns[1]*rhs.y())+
         (columns[2]*rhs.z())+
         (columns[3]*rhs.w());
  return comp;
}

void Transform::set_identity () {
  matrix_ = Matrix();
}

void Transform::set_position (const Point4D& position) {
  matrix_[3] = position;
}

void Transform::translate (const Vec4D& translation) {
  matrix_[3] = Point4D(matrix_[3]) + translation;
}

void Transform::scale (const Vec4D& scale) {
  matrix_[0] = matrix_[0]*scale.x();
  matrix_[1] = matrix_[1]*scale.y();
  matrix_[2] = matrix_[2]*scale.x();
}

void Transform::rotatez (const double ang) {
  Matrix rotate;
  double rad = -ang*PI/180;
  rotate[0] = Base4D(cos(rad), sin(rad), 0.0, 0.0);
  rotate[1] = Base4D(-sin(rad), cos(rad), 0.0, 0.0);
  rotate[2] = Base4D(0.0, 0.0, 1.0, 0.0);
  rotate[3] = Base4D(0.0, 0.0, 0.0, 1.0);
 
  matrix_ = rotate * matrix_;
}

void Transform::rotatey (const double ang) {
  Matrix rotate;
  double rad = -ang*PI/180;
  rotate[0] = Base4D(cos(rad), 0.0, sin(rad), 0.0);
  rotate[1] = Base4D(0.0, 1.0, 0.0, 0.0);
  rotate[2] = Base4D(-sin(rad), 0.0, cos(rad), 0.0);
  rotate[3] = Base4D(0.0, 0.0, 0.0, 1.0);

  matrix_ = rotate * matrix_;
}

void Transform::rotatex (const double ang) {
  Matrix rotate;
  double rad = -ang*PI/180;
  rotate[0] = Base4D(1.0, 0.0, 0.0, 0.0);
  rotate[1] = Base4D(0.0, cos(rad), sin(rad), 0.0);
  rotate[2] = Base4D(0.0, -sin(rad), cos(rad), 0.0);
  rotate[3] = Base4D(0.0, 0.0, 0.0, 1.0);

  matrix_ = rotate * matrix_;
}

void Transform::composition (const Matrix& matrix) {
  matrix_ = matrix * matrix_;
}

void Transform::pushmodel (const obj::Model& model) {
  modelvec_.push_back(model); 
}

void Transform::pushtransform (const Transform& transform) {
  transformvec_.push_back(transform);
}

void Transform::dump () const {
  matrix_.dump();
}

Transform Transform::identity () {
  return Transform(Matrix());
}

} // namespace ep2
