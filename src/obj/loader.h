
#ifndef EP2_OBJ_LOADER_H_
#define EP2_OBJ_LOADER_H_

#include <string>
#include <map>

#include <tr1/functional>
#include <tr1/unordered_map>

#include "obj/parser.h"
#include "obj/modeldata.h"

namespace ep2 {
namespace obj {

class Model;

#define DECLARE_HANDLER(name) \
  void handle_##name (ModelData::Ptr data, const Command& cmd);

class Loader {
  public:
    typedef std::tr1::function<void (ModelData::Ptr, const Command&)> CmdHandler;
    typedef std::tr1::unordered_map<std::string, CmdHandler> HandlerTable;
    Loader ();
    Model load (const std::string& modelname);
    DECLARE_HANDLER(objname);
    DECLARE_HANDLER(vertex);
    DECLARE_HANDLER(face);
    DECLARE_HANDLER(materialimport);
    DECLARE_HANDLER(materialusage);
  private:
    HandlerTable handlers_;
};

#undef DECLARE_HANDLER

} // namespace obj
} // namespace ep2

#endif

