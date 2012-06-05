
#ifndef EP2_OBJ_MODELDATA_H_
#define EP2_OBJ_MODELDATA_H_

#include <string>
#include <vector>

#include <tr1/memory>

#include "base4D.h"

namespace ep2 {
namespace obj {

// This is overkill for now.
/*
struct VertexData {
  unsigned vtx, tex, norm;
  explicit VertexData (unsigned v, unsigned t = 0, unsigned n = 0) :
    vtx(v), tex(t), norm(n) {}
};
*/

typedef std::vector<unsigned> Face;
struct Material {
  unsigned  begin;
  Base4D    ambient,        // Ka
            diffuse,        // Kd
            specular,       // Ks
            emission;       // Tf
  double    spec_exponent,  // Ns
            opacy;          // d
};

class ModelData {
  public:
    /// Reference-counting smart pointer for model data objects.
    typedef std::tr1::shared_ptr<ModelData> Ptr;
    void set_name (const std::string& name) { name_ = name; }
    void add_vertex (const Base4D& vertex);
    void add_face (const Face& face);
    void add_material (const Material& material);
    const std::vector<Base4D>& vertices () const {
      return vertices_;
    }
    const std::vector<Face>& faces () const {
      return faces_;
    }
    const std::vector<Material>& materials () const {
      return materials_;
    }
    static Ptr create () {
      return ModelData::Ptr(new ModelData);
    }
  private:
    ModelData () {}
    std::string           name_;
    std::vector<Base4D>   vertices_;
    //std::vector<Base4D>   texture_vertices_;
    //std::vector<Vec4D>    normals_;
    std::vector<Face>     faces_;
    std::vector<Material> materials_;
};

} // namespace obj
} // namespace ep2

#endif

