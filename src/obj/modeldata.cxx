
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

void ModelData::add_material (const Material& material) {
  materials_.push_back(material);
  materials_.back().begin = faces_.size();
}

} // namespace obj
} // namespace ep2

