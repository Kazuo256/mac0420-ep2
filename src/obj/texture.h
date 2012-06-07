
#ifndef EP2_OBJ_TEXTURE_H_
#define EP2_OBJ_TEXTURE_H_

#include <string>
#include <tr1/memory>
#include <tr1/unordered_map>

#include "getglut.h"

namespace ep2 {
namespace obj {

class Texture {
  public:
    typedef std::tr1::shared_ptr<Texture>             Ptr;
    typedef std::tr1::unordered_map<std::string, Ptr> TexCache;
    static Ptr load (const std::string& filepath);
  private:
    GLuint texname_;
    static TexCache cache_;
    Texture ();
    ~Texture ();
};

} // namespace obj
} // namespace ep2

#endif

