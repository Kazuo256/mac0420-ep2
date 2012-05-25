
#ifndef EP2_OBJ_LOADER_H_
#define EP2_OBJ_LOADER_H_

#include <string>

#include "obj/model.h"

namespace ep2 {
namespace obj {

class Loader {
  public:
    Loader () {}
    Model::Ptr load (const std::string& modelname);
};

} // namespace obj
} // namespace ep2

#endif

