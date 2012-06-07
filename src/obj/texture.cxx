
#include "obj/texture.h"

#include <cstdio>

#include <il.h>
#define ILUT_USE_OPENGL
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

static ILuint load_image (const string& filepath) {
  ILuint imgname;
  ilGenImages(1, &imgname);
  ilBindImage(imgname);
  ilLoadImage(filepath.c_str()); 
  return imgname;
}

Texture::Cache Texture::cache_;

Texture::Ptr Texture::get (const string& filepath) {
  Texture::Ptr cached = cache_[filepath];
  if (cached) return cached;
  else return load(filepath);
}

Texture::Ptr Texture::load (const string& filepath) {
  init_devil();
  ILuint imgname = load_image(filepath);
  GLuint texname = ilutGLBindTexImage();
  if (!texname) {
    puts("WARNNG: Failed to generate and bind texture.");
    return Ptr();
  }
  Ptr texture = Ptr(new Texture(texname));
  cache_[filepath] = texture;
  ilDeleteImages(1, &imgname);
  return texture;
}

Texture::~Texture () {
  if (texname_)
    glDeleteTextures(1, &texname_);
}

} // namespace obj
} // namespace ep2

