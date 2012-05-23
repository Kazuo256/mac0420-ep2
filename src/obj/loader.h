
#ifndef EP2_OBJ_LOADER_H_
#define EP2_OBJ_LOADER_H_

#include <string>

namespace ep2 {
namespace obj {

class Model;
class Model::Ptr;

class Loader {
  public:
    Loader () {}
    Model::Ptr load (const std::string& filename);
};

} // namespace obj
} // namespace ep2

#endif

