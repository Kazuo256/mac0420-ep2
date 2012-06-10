
#include <cstdio>
#include <cmath>

#include <algorithm>

#include "vec4D.h"
#include "point4D.h"

#define PI 3.1415926535898

namespace ep2 {

double Vec4D::angle_to (const Vec4D& rhs) const {
  if (*this == rhs) return 0.0;
  else return acos(normalized()*rhs.normalized())*180.0/PI;
}

Vec4D Vec4D::normalized () const {
  if (*this == Vec4D(0.0, 0.0, 0.0)) return *this;
  Vec4D norm = (*this)/length();
  return norm;
}

Vec4D Vec4D::ypr (double yaw, double pitch, double roll) {
  return Vec4D(pitch, yaw, roll);
}

/// Orthogonalizes the up vector.
static Vec4D ortho (const Vec4D& v, const Vec4D& up) {
  Vec4D result;
  result = v/up;
  return result/v;
}

/// Gets a number's sign.
static double sign (double x) {
  return 1.0 - 2.0*(x < 0.0);
}

Vec4D Vec4D::dir (const Vec4D& v, const Vec4D& up) {
  Vec4D v_dir, aux, y;
  double yaw, pitch, roll;

  aux = v;
  aux.set_y(0.0);
  pitch = aux.angle_to(v)*-sign(v.y());

  yaw = aux.angle_to(Vec4D::Z())*sign(aux.x());

  aux = ortho(v, up);
  y = ortho(v, Vec4D::Y());
  roll = aux.angle_to(y);
  
  return ypr(yaw, pitch, roll);
}

Vec4D Vec4D::normal (const Point4D& a, const Point4D& b, const Point4D& c) {
  //puts("normal");
  //a.dump();
  //b.dump();
  //c.dump();
  return ((b-a)/(c-a)).normalized();
}

} // namespace ep1

