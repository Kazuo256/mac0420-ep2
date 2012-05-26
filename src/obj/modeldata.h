
#ifndef EP2_OBJ_MODELDATA_H_
#define EP2_OBJ_MODELDATA_H_

#include <vector>

#include "obj/modeldata_fwd.h"
#include "base4D.h"

namespace ep2 {
namespace obj {

class ModelData {
  public:
    void add_vertex (const Base4D& vertex);
    static ModelDataPtr create () {
      return ModelDataPtr(new ModelData);
    }
  private:
    ModelData () {}
    std::vector<Base4D> vertexes_;
};

} // namespace obj
} // namespace ep2

#endif

