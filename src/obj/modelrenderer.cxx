
#include <algorithm>

#include <tr1/functional>

#include "getglut.h"

#include "obj/modelrenderer.h"

namespace ep2 {
namespace obj {

using std::vector;
using std::for_each;
using std::tr1::bind;
using std::tr1::placeholders::_1;

static void setup_material (const Material& material) {
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.spec_exponent);
}

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
  vector<MaterialIndex>::const_iterator mit = data_->material_indexes().begin();
  vector<Face>::const_iterator          fit;
  for (fit = data_->faces().begin(); fit < data_->faces().end(); fit++) {
    if (mit < data_->material_indexes().end() &&
        fit - (data_->faces().begin()) == mit->begin) {
      setup_material(data_->materials().find(mit->name)->second);
      mit++;
    }
    render_face(*fit);
  }
}

} // namespace obj
} // namespace ep2

