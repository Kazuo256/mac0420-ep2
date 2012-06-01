
#include <cstdio>
#include <cmath>

#include <algorithm>

#include "base4D.h"

#define PI 3.1415926535898

namespace ep2 {

double Base4D::length () const {
  return sqrt(x_*x_ + y_*y_ + z_*z_);
}

double Base4D::min () const {
  if (x_ < y_)
    if (x_ < z_) return x_;
    else return z_;
  else if (y_ < z_) return y_;
  else return z_;
}

double Base4D::max () const {
  return std::max(x_, std::max(y_, z_));
}

Base4D Base4D::vec_floor () const {
  Base4D ret = (*this);
  ret.x_ = floor(ret.x_);
  ret.y_ = floor(ret.y_);
  ret.z_ = floor(ret.z_);
  return ret;
} 

Base4D Base4D::vec_ceil () const {
  Base4D ret = (*this);
  ret.x_ = ceil(ret.x_);
  ret.y_ = ceil(ret.y_);
  ret.z_ = ceil(ret.z_);
  return ret;
}

void Base4D::dump () const {
  printf("<%f, %f, %f, %f>\n", x_, y_, z_, w_);
}

} //namespace ep2
