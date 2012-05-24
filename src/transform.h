
#ifndef EP2_TRANSFORM_H_
#define EP2_TRANSFORM_H_

#include "vec4D.h"
#include <vector>

namespace ep2 {

class Transform {
  public:
    ///
    /** Matriz em notação de coluna. Matrix[0] é a primeira 
     ** coluna da matriz */ 
    typedef std::vector<Vec4D>  Matrix;
    Transform (Matrix matrix) :
      matrix_(matrix) {}
    void composition (Matrix matrix);
  private:
    Matrix matrix_;
};

}

#endif
