
#include "point4D.h"

namespace ep2 {

Vec4D Point4D::operator - (const Point4D& rhs) const {
  Vec4D ret(rhs.x_-x_, rhs.y_-y_, rhs.z_-z_);
  return ret;
}

Point4D Point4D::operator * (double rhs) const {
  Point4D ret(rhs*x_, rhs*y_, rhs*z_);
  return ret;
}

Point4D Point4D::operator + (const Vec4D rhs) const {
  Point4D ret(rhs.x()+x_, rhs.y()+y_, rhs.z()+z_);
  return ret;
}

}//namespace ep2
