
#ifndef EP2_OBJ_MODELDATA_H_
#define EP2_OBJ_MODELDATA_H_

#include <string>
#include <vector>

#include "obj/modeldata_fwd.h"
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

//typedef std::vector<VertexData> Face;
typedef std::vector<unsigned> Face;

class ModelData {
  public:
    void set_name (const std::string& name) { name_ = name; }
    void add_vertex (const Base4D& vertex);
    void add_face (const Face& face);
    static ModelDataPtr create () {
      return ModelDataPtr(new ModelData);
    }
  private:
    ModelData () {}
    std::string         name_;
    std::vector<Base4D> vertices_;
    //std::vector<Base4D>   texture_vertices_;
    //std::vector<Vec4D>    normals_;
    std::vector<Face>   faces_;
};

} // namespace obj
} // namespace ep2

#endif

