
#ifndef EP1_OBJ_LOADER_H_
#define EP1_OBJ_LOADER_H_

#include <string>

namespace ep2 {

class Model;
class Model::Ptr;

class ModelLoader {
  public:
    ModelLoader () {}
    Model::Ptr load (const std::string& filename);
};

} // namespace ep2

#endif

