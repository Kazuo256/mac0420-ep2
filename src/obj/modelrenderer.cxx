
#include <algorithm>

#include <tr1/functional>

#include "getglut.h"

#include "obj/modelrenderer.h"
#include "obj/modeldata.h"

namespace ep2 {
namespace obj {

using std::for_each;
using std::tr1::bind;
using std::tr1::placeholders::_1;

void ModelRenderer::vertex (unsigned i) {
  glVertex4dv(data_->vertices()[i-1].val());
}

void ModelRenderer::render_face (const Face& face) {
  if (face.size() < 3) return;
  glBegin(GL_TRIANGLES);
  {
    Face::const_iterator it;
    for (it = face.begin()+1; it+1 !=face.end(); it++) {
      vertex(face.front());
      vertex(*it);
      vertex(*(it+1));
    }
  }
  glEnd();
}

void ModelRenderer::operator () () {
  for_each(
    data_->faces().begin(),
    data_->faces().end(),
    bind(&ModelRenderer::render_face, this, _1)
  );
}

} // namespace obj
} // namespace ep2

