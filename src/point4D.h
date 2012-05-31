
#ifndef EP2_POINT4D_H_
#define EP2_POINT4D_H_

#include "base4D.h"
#include "vec4D.h"

namespace ep2 {

class Point4D : public Base4D {
  public:
    /// Constructor.
    /** @param x X-coordinate of the point
     ** @param y Y-coordinate of the point
     ** @param z Z-coordinate of the point */
    explicit Point4D (double x = 0.0,
                      double y = 0.0,
                      double z = 0.0) :
      Base4D(x, y, z, 1.0) {}
    /// Construcor.
    /** @param val Arrays of double with size 3 containing the point
     **            coordinates. */
    Point4D (const double val[3]) :
      Base4D(val[0], val[1], val[2], 1.0) {}
    /// Downcast constructor.
    Point4D (const Base4D& base) :
      Base4D(base) { a_ == 0.0 ? (a_ = 1.0): 0; }
    /// Unary minus.
    Point4D operator - () const;
    /// Subtraction.
    Vec4D operator - (const Point4D& rhs) const;
    /// Product with scalar.
    Point4D operator * (double rhs) const;
    /// Add a vector to the point.
    Point4D operator + (const Vec4D rhs) const;
};

inline Point4D Point4D::operator - () const {
  return Point4D(-x_, -y_, -z_);
}

} //namespace ep2

#endif
