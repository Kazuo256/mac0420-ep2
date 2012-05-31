
#ifndef EP2_TRANSFORM_H_
#define EP2_TRANSFORM_H_

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
        Matrix (const Vec4D& xaxis = Vec4D::X(),
                const Vec4D& yaxis = Vec4D::Y(),
                const Vec4D& zaxis = Vec4D::Z(),
                const Vec4D& origin = Vec4D::A());
        Vec4D& operator [] (unsigned i) { return columns[i]; }
        Vec4D operator [] (unsigned i) const { return columns[i]; }
      private:
        Vec4D columns[4];
    };
    typedef std::vector<obj::Model> ModelVec;
    typedef std::vector<Transform>  TransformVec;
    Transform (const Matrix& matrix = Matrix()) :
      matrix_(matrix) {}
    void set_identity ();
    void set_position (const Point4D& position);
    void translate (const Vec4D& translation);
    void composition (const Matrix& matrix);
    void pushmodel (const obj::Model& model);
    void pushtransform (const Transform& transform);
    static Transform identity ();
  private:
    Matrix        matrix_;
    ModelVec      modelvec_;
    TransformVec  transformvec_;
};

}

#endif
