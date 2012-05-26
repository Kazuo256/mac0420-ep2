
#ifndef EP2_OBJ_LOADER_H_
#define EP2_OBJ_LOADER_H_

#include <string>
#include <map>

#include <tr1/functional>
#include <tr1/unordered_map>

#include "obj/model.h"
#include "obj/modeldata_fwd.h"
#include "obj/parser.h"

namespace ep2 {
namespace obj {

#define DECLARE_HANDLER(name) \
  void handle_##name (ModelDataPtr data, const Command& cmd);

class Loader {
  public:
    typedef std::tr1::function<void (ModelDataPtr, const Command&)> CmdHandler;
    typedef std::tr1::unordered_map<std::string, CmdHandler> HandlerTable;
    Loader ();
    Model::Ptr load (const std::string& modelname);
    DECLARE_HANDLER(vertex);
  private:
    HandlerTable handlers_;
};

} // namespace obj
} // namespace ep2

#endif

