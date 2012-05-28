
#ifndef EP2_TRANSFORM_H_
#define EP2_TRANSFORM_H_

#include "vec4D.h"
#include "model.h"

#include <vector>

namespace ep2 {

class Transform {
  public:
    ///
    /** Matriz em notação de coluna. Matrix[0] é a primeira 
     ** coluna da matriz */ 
    typedef std::vector<Vec4D>      Matrix;
    typedef std::vector<Model>      ModelVec;
    typedef std::vector<Transform>  TransformVec;
    Transform (Matrix matrix) :
      matrix_(matrix) {}
    void composition (Matrix matrix);
    void pushModel (Model model);
    void pushTransform (Transform transform);
  private:
    Matrix        matrix_;
    ModelVec      modelvec_;
    TransformVec  transformvec_;
};

}

#endif
