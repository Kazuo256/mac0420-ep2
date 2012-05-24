
#ifndef EP2_VEC4D_H_
#define EP2_VEC4D_H_

#include "base4D.h"
#include <cstring>

namespace ep2 {

class Vec4D : public Base4D {
  public:
    /// Constructor.
    /** @param x X-coordinate of the vector
     ** @param y Y-coordinate of the vector
     ** @param z Z-coordinate of the vector */
    explicit Vec4D ( double x = 0.0, 
                      double y = 0.0, 
                      double z = 0.0) :
      Base4D(x, y, z, 0.0) {}
    /// Construcor.
    /** @param val Arrays of double with size 3 containing the vector
     **            coordinates. */
    Vec4D (const double val[4]) :
      Base4D(val[0], val[1], val[2], 0.0) {}
    /// Unary minus.
    Vec4D operator - () const;
    /// Addition.
    Vec4D operator + (const Vec4D& rhs) const;
    /// In-place addition.
    Vec4D& operator += (const Vec4D& rhs);
    /// Subtraction.
    Vec4D operator - (const Vec4D& rhs) const;
    /// Scalar product.
    double operator * (const Vec4D& rhs) const;
    /// Vectorial product.
    Vec4D operator / (const Vec4D& rhs) const;
    /// Product with scalar.
    Vec4D operator * (double rhs) const;
    /// Division by scalar.
    Vec4D operator / (double rhs) const;
    /// Calculates the absolute angle between two vectors.
    /** @param rhs Another vector.
     ** @return double The absolute angle between this and the ther vector. */
    double angle_to (const Vec4D& rhs) const;
    /// Makes a normalized version of this vector.
    /** @return Vec4D Normalized version of this vector. */
    Vec4D normalized () const;
    /// X-axis canonical vector.
    /** @return Vec4D The (1,0,0) vector. */
    static Vec4D X () { return Vec4D(1.0, 0.0, 0.0); }
    /// Y-axis canonical vector.
    /** @return Vec4D The (0,1,0) vector. */
    static Vec4D Y () { return Vec4D(0.0, 1.0, 0.0); }
    /// Z-axis canonical vector.
    /** @return Vec4D The (0,0,1) vector. */
    static Vec4D Z () { return Vec4D(0.0, 0.0, 1.0); }
    /// Z-axis canonical vector.
    /** @return Vec4D The (0,0,1) vector. */
    static Vec4D A () { return Vec4D(0.0, 0.0, 1.0); }
    /// Makes a vector in the yaw-pitch-roll format.
    /** These can be used to define an ep1::Object transformation.
     ** @param yaw Yaw angle.
     ** @param pitch Pitch angle.
     ** @param roll Roll angle.
     ** @return Vec4D Corresponding vector in the yaw-pitch-roll format. */
    static Vec4D ypr (double yaw, double pitch, double roll);
    /// Makes a vector in the yaw-pitch-roll format from a directional vector.
    /** This is used to make rotation vectors out of direction vectors. The up
     ** vector is a required infomation.
     ** @param v  A directional vector (does not need to be normalized)
     ** @param up The up vector (normalized) of the intended rotation.
     ** @return Vec4D Corresponding rotation vector in the yaw-pitch-woll
     **               format. */
    static Vec4D dir (const Vec4D& v, const Vec4D& up = Vec4D::Y()); 
  private:
    union {
      struct { double x_, y_, z_, a_; };
      struct { double val_[4]; };
    };
};

inline Vec4D Vec4D::operator - () const {
  return Vec4D(-x_, -y_, -z_);
}

inline Vec4D Vec4D::operator + (const Vec4D& rhs) const {
  return Vec4D(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_);
}

inline Vec4D& Vec4D::operator += (const Vec4D& rhs) {
  x_ += rhs.x_;
  y_ += rhs.y_;
  z_ += rhs.z_;
  return *this;
}

inline Vec4D Vec4D::operator - (const Vec4D& rhs) const {
  return *this + (-rhs);
}

inline double Vec4D::operator * (const Vec4D& rhs) const {
  return x_*rhs.x_ + y_*rhs.y_ + z_*rhs.z_;
}

inline Vec4D Vec4D::operator / (const Vec4D& rhs) const {
    return Vec4D( y_*rhs.z_ - z_*rhs.y_,
                  z_*rhs.x_ - x_*rhs.z_,
                  x_*rhs.y_ - y_*rhs.x_);
}

inline Vec4D Vec4D::operator * (double rhs) const {
  return Vec4D(x_*rhs, y_*rhs, z_*rhs);
}

inline Vec4D Vec4D::operator / (double rhs) const {
  return Vec4D(x_/rhs, y_/rhs, z_/rhs);
}

} // namespace ep2

#endif

