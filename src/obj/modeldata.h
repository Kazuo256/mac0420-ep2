
#ifndef EP2_OBJ_MODELDATA_H_
#define EP2_OBJ_MODELDATA_H_

#include <vector>

#include "obj/modeldata_fwd.h"
#include "base4D.h"

namespace ep2 {
namespace obj {

class ModelData {
  public:
    ModelData () {}
    void add_vertex (const Base4D& vertex);
  private:
    std::vector<Base4D> vertexes_;
};

} // namespace obj
} // namespace ep2

#endif

