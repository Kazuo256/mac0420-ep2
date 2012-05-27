
#include "obj/modeldata.h"

namespace ep2 {
namespace obj {

using std::string;
using std::vector;

void ModelData::add_vertex (const Base4D& vertex) {
  vertices_.push_back(vertex);
}

void ModelData::add_face (const Face& face) {
  faces_.push_back(face);
}

} // namespace obj
} // namespace ep2

