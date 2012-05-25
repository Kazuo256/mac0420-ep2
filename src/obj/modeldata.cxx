
#include "obj/modeldata.h"

namespace ep2 {
namespace obj {

using std::string;
using std::vector;

void ModelData::add_vertex (const Base4D& vertex) {
  vertexes_.push_back(vertex);
}

} // namespace obj
} // namespace ep2

