
#include "obj/texture.h"

#include <cstdio>

namespace ep2 {
namespace obj {

using std::string;

Texture::Ptr Texture::load (const string& filepath) {
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

