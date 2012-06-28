
#ifndef EP2_OBJ_MODELDATA_H_
#define EP2_OBJ_MODELDATA_H_

#include <string>
#include <vector>

#include <tr1/memory>
#include <tr1/unordered_map>

#include "base4D.h"
#include "vec4D.h"

namespace ep2 {
namespace obj {

struct VertexData {
  unsigned vtx, tex, norm;
  VertexData (unsigned v, unsigned t = 0, unsigned n = 0) :
    vtx(v), tex(t), norm(n) {}
};
class Texture;
typedef std::tr1::shared_ptr<Texture> TexPtr;
typedef std::vector<VertexData> Face;

struct Material {
  float     ambient[4],     // Ka
            diffuse[4],     // Kd
            specular[4],    // Ks
            emission[4],    // Tf
            spec_exponent,  // Ns
            opacy;          // d
  TexPtr    texture;
  void clear();
};

typedef std::tr1::unordered_map<std::string,Material> MaterialLib;

struct MaterialIndex {
  unsigned    begin;
  std::string name;
};

class ModelData {
  public:
    /// Reference-counting smart pointer for model data objects.
    typedef std::tr1::shared_ptr<ModelData> Ptr;
    void set_name (const std::string& name) { name_ = name; }
    void add_vertex (const Base4D& vertex);
    void add_texcoord (const Base4D& texcoord);
    void add_normal (const Vec4D& normal);
    void add_face (const Face& face);
    void add_material (const std::string& name, const Material& material);
    void add_material_index (const std::string& name);
    const std::vector<Base4D>& vertices () const {
      return vertices_;
    }
    const std::vector<Base4D>& texture_vertices () const {
      return texture_vertices_;
    }
    const std::vector<Vec4D>& normals () const {
      return normals_;
    }
    const std::vector<Face>& faces () const {
      return faces_;
    }
    const MaterialLib& materials () const {
      return materials_;
    }
    const std::vector<MaterialIndex>& material_indexes () const {
      return material_indexes_;
    }
    static Ptr create () {
      return ModelData::Ptr(new ModelData);
    }
  private:
    ModelData () {}
    std::string                 name_;
    std::vector<Base4D>         vertices_;
    std::vector<Base4D>         texture_vertices_;
    std::vector<Vec4D>          normals_;
    std::vector<Face>           faces_;
    MaterialLib                 materials_;
    std::vector<MaterialIndex>  material_indexes_;
};

} // namespace obj
} // namespace ep2

#endif

