
#ifndef EP2_TRANSFORM_H_
#define EP2_TRANSFORM_H_

#include "vec4D.h"
#include "obj/model.h"

#include <vector>

namespace ep2 {

class Transform {
  public:
    ///
    /** Matriz em notação de coluna. Matrix[0] é a primeira 
     ** coluna da matriz */ 
    typedef std::vector<Vec4D>      Matrix;
    typedef std::vector<obj::Model> ModelVec;
    typedef std::vector<Transform>  TransformVec;
    Transform (Matrix matrix) :
      matrix_(matrix) {}
    void composition (const Matrix& matrix);
    void pushmodel (const obj::Model& model);
    void pushtransform (const Transform& transform);
  private:
    Matrix        matrix_;
    ModelVec      modelvec_;
    TransformVec  transformvec_;
};

}

#endif
