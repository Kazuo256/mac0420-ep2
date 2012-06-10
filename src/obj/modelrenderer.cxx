
#include "obj/modelrenderer.h"

#include <cstdio>
#include <algorithm>
#include <tr1/functional>

#include "getglut.h"
#include "vec4D.h"
#include "point4D.h"
#include "obj/texture.h"

namespace ep2 {
namespace obj {

using std::string;
using std::vector;
using std::for_each;
using std::tr1::bind;
using std::tr1::placeholders::_1;
using std::tr1::unordered_map;

static void setup_material (const Material& material) {
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material.ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material.diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material.specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material.emission);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material.spec_exponent);
  if (material.texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, material.texture->name());
  }
}

void ModelRenderer::default_material () {
  setup_material(Material());
}

void ModelRenderer::vertex (const VertexData& v) {
  if (v.tex) {
    Base4D vt = data_->texture_vertices()[v.tex-1];
    glTexCoord2d(vt.x(), vt.y());
  }
  glVertex4dv(data_->vertices()[v.vtx-1].val());
}

void ModelRenderer::render_face (const Face& face) {
  if (face.size() < 3) return;
  glBegin(GL_TRIANGLES);
  {
    Face::const_iterator it;
    for (it = face.begin()+1; it+1 !=face.end(); it++)
      render_triangle(face.front(), *it, *(it+1));
  }
  glEnd();
}

void ModelRenderer::render_triangle (const VertexData& v1,
                                     const VertexData& v2,
                                     const VertexData& v3) {
  Point4D a = data_->vertices()[v1.vtx-1],
          b = data_->vertices()[v2.vtx-1],
          c = data_->vertices()[v3.vtx-1];
  Vec4D norm = Vec4D::normal(a,b,c);
  glNormal3d(norm.x(), norm.y(), norm.z());
  vertex(v1);
  vertex(v2);
  vertex(v3);
}

void ModelRenderer::operator () () {
  vector<MaterialIndex>::const_iterator mit = data_->material_indexes().begin();
  vector<Face>::const_iterator          fit;
  for (fit = data_->faces().begin(); fit < data_->faces().end(); fit++) {
    if (mit < data_->material_indexes().end() &&
        fit - (data_->faces().begin()) == mit->begin) {
      MaterialLib::const_iterator m = data_->materials().find(mit->name);
      if (m != data_->materials().end())
        setup_material(m->second);
      mit++;
    }
    render_face(*fit);
  }
}

} // namespace obj
} // namespace ep2

