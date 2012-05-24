
#include <cstdio>
#include <cmath>

#include <algorithm>

#include "base4D.h"

#define PI 3.1415926535898

namespace ep2 {

double Vec4D::length () const {
  return sqrt(x_*x_ + y_*y_ + z_*z_);
}

double Vec4D::min () const {
  if (x_ < y_)
    if (x_ < z_) return x_;
    else return z_;
  else if (y_ < z_) return y_;
  else return z_;
}

double Vec4D::max () const {
  return std::max(x_, std::max(y_, z_));
}

Vec4D Vec4D::vec_floor () const {
  Vec4D ret = (*this);
  ret.x_ = floor(ret.x_);
  ret.y_ = floor(ret.y_);
  ret.z_ = floor(ret.z_);
  return ret;
} 

Vec3D Vec3D::vec_ceil () const {
  Vec3D ret = (*this);
  ret.x_ = ceil(ret.x_);
  ret.y_ = ceil(ret.y_);
  ret.z_ = ceil(ret.z_);
  return ret;
}

void Vec3D::dump () const {
  printf("<%f, %f, %f>\n", x_, y_, z_);
}

} //namespace ep2
