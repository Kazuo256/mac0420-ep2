
#include "obj/modeldata.h"

#include <cstring>

namespace ep2 {
namespace obj {

using std::string;
using std::vector;

const static float  DEFAULT_MTL_AMBIENT[4] = { 0.2, 0.2, 0.2, 1.0 },
                    DEFAULT_MTL_DIFFUSE[4] = { 0.8, 0.8, 0.8, 1.0 },
                    DEFAULT_MTL_SPECULAR[4] = { 0.0, 0.0, 0.0, 1.0 },
                    DEFAULT_MTL_EMISSION[4] = { 0.0, 0.0, 0.0, 1.0 },
                    DEFAULT_MTL_SPEC_EXPONENT = 0.0,
                    DEFAULT_MTL_OPACY = 1.0;

void Material::clear () {
  memcpy(ambient, DEFAULT_MTL_AMBIENT, 4*sizeof(float));
  memcpy(diffuse, DEFAULT_MTL_DIFFUSE, 4*sizeof(float));
  memcpy(specular, DEFAULT_MTL_SPECULAR, 4*sizeof(float));
  memcpy(emission, DEFAULT_MTL_EMISSION, 4*sizeof(float));
  spec_exponent = DEFAULT_MTL_SPEC_EXPONENT;
  opacy = DEFAULT_MTL_OPACY;
  texture = TexPtr();
}

void ModelData::add_vertex (const Base4D& vertex) {
  vertices_.push_back(vertex);
}

void ModelData::add_texcoord (const Base4D& texcoord) {
  texture_vertices_.push_back(texcoord);
}

void ModelData::add_face (const Face& face) {
  faces_.push_back(face);
}

void ModelData::add_material (const string& name, const Material& material) {
  materials_[name] = material;
}

void ModelData::add_material_index (const string& name) {
  MaterialIndex index;
  index.name = name;
  index.begin = faces_.size();
  material_indexes_.push_back(index);
}

} // namespace obj
} // namespace ep2

