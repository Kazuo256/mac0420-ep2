
#include "base4D.h"

namespace ep2 {

class Point4D : public base4D {
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
      Base(val[0], val[1], val[2], 1.0) {}
    /// Subtraction.
    Vec4D operator - (const Point4D& rhs) const;
    /// Product with scalar.
    Point4D operator * (double rhs) const;
    /// Add a vector to the point.
    Point4D operator + (const Vec4D rhs) const;
};

} //namespace ep2
