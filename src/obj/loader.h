
#ifndef EP2_OBJ_LOADER_H_
#define EP2_OBJ_LOADER_H_

#include <string>
#include <map>

#include <tr1/functional>

#include "obj/model.h"
#include "obj/modeldata_fwd.h"
#include "obj/parser.h"

namespace ep2 {
namespace obj {

class Loader {
  public:
    typedef std::tr1::function<void (ModelDataPtr&)> CmdHandler;
    Loader ();
    Model::Ptr load (const std::string& modelname);
    void handle_vertex (ModelDataPtr& data, const Parser::Command& cmd);
  private:
    std::map<std::string, CmdHandler> handlers_;
};

} // namespace obj
} // namespace ep2

#endif

