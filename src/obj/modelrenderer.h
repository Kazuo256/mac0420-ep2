
#ifndef EP2_OBJ_MODELRENDERER_H_
#define EP2_OBJ_MODELRENDERER_H_

#include <string>
#include <vector>

#include "obj/modeldata.h"

namespace ep2 {

namespace obj {

class ModelRenderer {
  public:
    explicit ModelRenderer (const ModelData::Ptr& data) : data_(data) {}
    void operator () ();
    static void default_material ();
  private:
    ModelData::Ptr data_;
    void render_face (const Face& face);
    void render_triangle (const VertexData& v1,
                          const VertexData& v2,
                          const VertexData& v3);
    void vertex (const VertexData& v);
};

} // namespace obj
} // namespace ep2

#endif

