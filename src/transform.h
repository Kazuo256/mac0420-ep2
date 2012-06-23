
#ifndef EP2_TRANSFORM_H_
#define EP2_TRANSFORM_H_

#include "base4D.h"
#include "vec4D.h"
#include "point4D.h"
#include "obj/model.h"

#include <cstring>
#include <vector>

namespace ep2 {

class Transform {
  public:
    ///
    /** Matriz em notação de coluna. Matrix[0] é a primeira 
     ** coluna da matriz */ 
    class Matrix {
      public:
        Matrix (const Base4D& xaxis = Base4D::X(),
                const Base4D& yaxis = Base4D::Y(),
                const Base4D& zaxis = Base4D::Z(),
                const Base4D& origin = Base4D::W());
        void makematrix (double* matrix) const; 
        void dump () const;
        Base4D& operator [] (unsigned i) { return columns[i]; }
        Base4D operator [] (unsigned i) const { return columns[i]; }
        Matrix operator * (const Matrix& rhs) const;
        Base4D operator * (const Base4D& rhs) const;
      private:
        Base4D columns[4];
    };
    typedef std::vector<obj::Model> ModelVec;
    typedef std::vector<Transform>  TransformVec;
    Transform (const Matrix& matrix = Matrix()) :
      matrix_(matrix) {}
    void set_identity ();
    void set_position (const Point4D& position);
    void translate (const Vec4D& translation);
    void scale (const Vec4D& scale);
    void rotatez (const double ang);
    void rotatey (const double ang);
    void rotatex (const double ang);
    void composition (const Matrix& matrix);
    void pushmodel (const obj::Model& model);
    void pushtransform (const Transform& transform);
    const Matrix& matrix() const { return matrix_; }
    const Base4D position() const { return matrix_[3]; }
    ModelVec& modelvec () { return modelvec_; }
    const TransformVec& transformvec () { return transformvec_; }
    void dump () const;
    static Transform identity ();
  private:
    Matrix        matrix_;
    ModelVec      modelvec_;
    TransformVec  transformvec_;
};

}

#endif
