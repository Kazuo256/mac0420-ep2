
#ifndef EP2_OBJ_MODELRENDERER_H_
#define EP2_OBJ_MODELRENDERER_H_

#include <string>
#include <vector>

#include "obj/modeldata_fwd.h"

namespace ep2 {

namespace obj {

class ModelRenderer {
  public:
    explicit ModelRenderer (const ModelDataPtr& data) : data_(data) {}
    void operator () ();
  private:
    ModelDataPtr  data_;
    void render_face (const Face& face);
    void vertex (unsigned i);
};

} // namespace obj
} // namespace ep2

#endif

