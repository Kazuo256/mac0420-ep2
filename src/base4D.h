
#ifndef EP2_BASE4D_H_
#define EP2_BASE4D_H_

#include <cstring>

namespace ep2 {

class Base4D {
  public:
    /// Constructor.
    /** @param x X-coordinate
     ** @param y Y-coordinate
     ** @param z Z-coordinate
     ** @param a Alpha-coordinate */
    explicit Base4D ( double x = 0.0, 
                      double y = 0.0, 
                      double z = 0.0,
                      double a = 1.0) :
      x_(x), y_(y), z_(z), w_(a) {} 
    /// Construcor.
    /** @param val Arrays of double with size 3 containing the vector
     **            coordinates. */
    Base4D (const double val[4]) :
      x_(val[0]), y_(val[1]), z_(val[2]), w_(val[3]) {}
    /// Gets the x-coordinate of the vector.
    /** @return double The x-coordinate of the vector. */
    double x () const { return x_; }
    /// Gets the y-coordinate of the vector.
    /** @return double The y-coordinate of the vector. */
    double y () const { return y_; }
    /// Gets the z-coordinate of the vector.
    /** @return double The z-coordinate of the vector. */
    double z () const { return z_; }
    /// Gets the alpha-coordinate of the vector.
    /** @return double The z-coordinate of the vector. */
    double w () const { return w_; }
    /// Gets a read-only array of the vector's coordinates.
    /** @return const double[4] Read-only array of the vector's coordinates. */
    const double* val () const { return val_; }
    /// Sets the x-coordinate of the vector.
    /** @param x The new x-coordinate of the vector. */
    void set_x (double x) { x_ = x; }
    /// Sets the y-coordinate of the vector.
    /** @param y The new y-coordinate of the vector. */
    void set_y (double y) { y_ = y; }
    /// Sets the z-coordinate of the vector.
    /** @param z The new z-coordinate of the vector. */
    void set_z (double z) { z_ = z; }
    /// Sets the alpha-coordinate of the vector.
    /** @param a The new alpha-coordinate of the vector. */
    void set_a (double w) { w_ = w; }
    /// Sets the alpha-coordinate of the vector.
    /** @param z The new z-coordinate of the vector. */
    void set_val (const double val[4]) {
      memcpy(val_, val, 4*sizeof(double));
    }
    /// Sets all the vector's coordinates.
    /** @param x The new x-coordinate of the vector.
     ** @param y The new y-coordinate of the vector.
     ** @param z The new z-coordinate of the vector. */
    void set (double x, double y, double z, double w = 1.0) {
      x_ = x; y_ = y; z_ = z; w_ = w;
    }
    /// Checks if two vectors are the same.
    /** @param rhs Another vector.
     ** @return bool True if they are the same, false otherwise. */
    bool operator == (const Base4D& rhs) const;
    /// Unary minus.
    Base4D operator - () const;
    /// Addition.
    Base4D operator + (const Base4D& rhs) const;
    /// Product with scalar.
    Base4D operator * (double rhs) const;
    /// Division by scalar.
    Base4D operator / (double rhs) const;
    /// Calculates the length of this vector.
    /** @return double The length of this vector. */
    double length () const;
    /// Calculates the biggest component of this vector.
    /** @return double The biggest component of this vector. */
    double min () const;
    /// Calculates the smallest component of this vector.
    /** @return double The smallest component of this vector. */
    double max () const;
    /// Generates a vector with the floor values of this vector.
    /** @return Vec3D a vector with the floor values of this vector. */
    Base4D vec_floor () const;
    /// Generates a vector with the ceil values of this vector.
    /** @return Vec3D a vector with the ceil values of this vector. */
    Base4D vec_ceil () const;
    /// Dumps vector's information.
    void dump() const;
    /// Canonical x-axis.
    /** @return Base4D The (1,0,0,0) vector. */
    static Base4D X () { return Base4D(1.0, 0.0, 0.0, 0.0); }
    /// Canonical y-axis.
    /** @return Base4D The (0,1,0,0) vector. */
    static Base4D Y () { return Base4D(0.0, 1.0, 0.0, 0.0); }
    /// Canonical z-axis.
    /** @return Base4D The (0,0,1,0) vector. */
    static Base4D Z () { return Base4D(0.0, 0.0, 1.0, 0.0); }
    /// Canonical w-axis.
    /** @return Base4D The (0,0,0,1) vector. */
    static Base4D W () { return Base4D(0.0, 0.0, 0.0, 1.0); }
  protected:
    union {
      struct { double x_, y_, z_, w_; };
      struct { double val_[4]; };
    };
};

inline bool Base4D::operator == (const Base4D& rhs) const {
  return x_ == rhs.x_ &&
         y_ == rhs.y_ &&
         z_ == rhs.z_ &&
         w_ == rhs.w_;
}

inline Base4D Base4D::operator - () const {
  return Base4D(-x_, -y_, -z_, -w_);
}

inline Base4D Base4D::operator + (const Base4D& rhs) const {
  return Base4D(x_ + rhs.x_, y_ + rhs.y_, z_ + rhs.z_, w_ + rhs.w_);
}

inline Base4D Base4D::operator * (double rhs) const {
  return Base4D(x_*rhs, y_*rhs, z_*rhs, w_*rhs);
}

inline Base4D Base4D::operator / (double rhs) const {
  return Base4D(x_/rhs, y_/rhs, z_/rhs, w_/rhs);
}

} //namespace ep2

#endif
