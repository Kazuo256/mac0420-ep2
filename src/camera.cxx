
#include <cmath>
#include <cstdio>

#include <algorithm>

#include "getglut.h"
#include "camera.h"

namespace ep2 {

void Camera::set_position (const Point4D& position) {
  transform_.set_position(Point4D());
  move(position-Point4D());
}

void Camera::move (const Vec4D& movement) {
  Transform rot = transform_;
  rot.set_position(Base4D());
  transform_.translate(-(rot.matrix()*movement));
}

void Camera::zoom (double d) {
  zoom_ *= (1.0/pow(2.0, d));
}

void Camera::rotatez (double ang) {
  transform_.rotatez(ang);
}

void Camera::rotatey (double ang) {
  transform_.rotatey(ang);
}

void Camera::set_ortho (double ratio) {
  perspective_ = false;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double max_dimension = std::max(view_.x(), view_.y());
  if (ratio >= 1.0)
    glOrtho(
      -ratio*0.75*max_dimension, ratio*0.75*max_dimension,
      -0.75*max_dimension, 0.75*max_dimension,
      -2.0*view_.z(), 10.0*view_.z()
    );
  else
    glOrtho(
      -0.75*max_dimension, 0.75*max_dimension,
      -0.75*max_dimension/ratio, 0.75*max_dimension/ratio,
      -2.0*view_.z(), 10.0*view_.z()
    );
}

void Camera::set_perspective (double ratio) {
  perspective_ = true;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(
    60.0, ratio,
    0.5, view_.z()*10.0
  );
  glMatrixMode(GL_MODELVIEW);
}

void Camera::toggle_projection (double ratio) {
  if (perspective_)
    set_ortho(ratio);
  else
    set_perspective(ratio);
  glutPostRedisplay();
}

void Camera::adjust (double ratio) {
  if (perspective_)
    set_perspective(ratio);
  else
    set_ortho(ratio);
}

void Camera::place () const {
  double matrix[16];
  // Adjusts camera zoom.
  //glTranslated(0.0, 0.0, -zoom_);
  // Signs here are kind of arbitrary. It depends on how you want the camera to
  // move.
  //glRotated(-sphere_pos_.y(), 1.0, 0.0, 0.0);
  //glRotated(sphere_pos_.x(), 0.0, 1.0, 0.0);
  // Moves to the camera's target.
  transform_.matrix().makematrix(matrix);
  glMultMatrixd(matrix);
}

} // namespace ep1

