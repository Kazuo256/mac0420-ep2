
#include "obj/texture.h"

#include <cstdio>

#include <il.h>
#include <ilut.h>

namespace ep2 {
namespace obj {

using std::string;

static void init_devil () {
  static bool check = false;
  if (!check) {
    ilInit();
    ilutRenderer(ILUT_OPENGL);
    ilutEnable(ILUT_OPENGL_CONV);
    check = true;
  }
}

Texture::Ptr Texture::load (const string& filepath) {
  init_devil();
  return Ptr();
}

Texture::Texture () {
  glGenTextures(1, &texname_);
  if (!texname_)
    puts("WARNNG: failed to generate texture name!");
}

Texture::~Texture () {
  if (texname_)
    glDeleteTextures(1, &texname_);
}

} // namespace obj
} // namespace ep2

