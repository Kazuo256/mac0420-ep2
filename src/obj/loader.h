
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
    Model load_model (const std::string& modelname);
    // OBJ handlers
    DECLARE_HANDLER (objname);
    DECLARE_HANDLER (vertex);
    DECLARE_HANDLER (texcoord);
    DECLARE_HANDLER (face);
    DECLARE_HANDLER (materialimport);
    DECLARE_HANDLER (materialusage);
    // MTL handlers
    DECLARE_HANDLER (newmaterial);
    DECLARE_HANDLER (ambient);
    DECLARE_HANDLER (diffuse);
    DECLARE_HANDLER (specular);
    DECLARE_HANDLER (emission);
    DECLARE_HANDLER (texture);
  private:
    HandlerTable  obj_handlers_,
                  mtl_handlers_;
    std::string   current_mtlname_;
    Material      current_material_;
    void load_materiallib (ModelData::Ptr& data, const std::string& libname);
};

#undef DECLARE_HANDLER

} // namespace obj
} // namespace ep2

#endif

