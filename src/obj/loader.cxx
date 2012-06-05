
#include <cstdlib>
#include <vector>

#include "obj/loader.h"
#include "obj/parser.h"
#include "obj/model.h"
#include "obj/modeldata.h"
#include "obj/modelrenderer.h"

namespace ep2 {
namespace obj {

using std::string;
using std::vector;
using std::tr1::bind;
using std::tr1::unordered_map;
using namespace std::tr1::placeholders;

typedef void (Loader::*Handler) (ModelData::Ptr, const Command&);

#define OBJ_HANDLERTABLE_SIZE 5
#define MTL_HANDLERTABLE_SIZE 1
#define GET_HANDLER(name) &Loader::handle_##name

struct RawHandlerTable {
  const char* tag;
  Handler     handler;
};

static RawHandlerTable obj_handlers_table[OBJ_HANDLERTABLE_SIZE] = {
  {"o", GET_HANDLER(objname) },
  {"v", GET_HANDLER(vertex) },
  {"f", GET_HANDLER(face) },
  {"mtllib", GET_HANDLER(materialimport) },
  {"usemtl", GET_HANDLER(materialusage) }
};

static RawHandlerTable mtl_handlers_table[MTL_HANDLERTABLE_SIZE] = {
  {"newmtl", GET_HANDLER(newmaterial) }
};

Loader::Loader () {
  for (unsigned i = 0; i < OBJ_HANDLERTABLE_SIZE; i++)
    obj_handlers_[obj_handlers_table[i].tag] =
      bind(obj_handlers_table[i].handler, this, _1, _2);
  for (unsigned i = 0; i < MTL_HANDLERTABLE_SIZE; i++)
    mtl_handlers_[mtl_handlers_table[i].tag] =
      bind(mtl_handlers_table[i].handler, this, _1, _2);
}

Model Loader::load_model (const string& modelname) {
  Parser parser("models/"+modelname+".obj");
  ModelData::Ptr data = ModelData::create();
  while (true) {
    Command cmd;
    if (!parser.parse_command(cmd)) break;
    HandlerTable::iterator handler = obj_handlers_.find(cmd.front());
    if (handler != obj_handlers_.end())
      handler->second(data, cmd);
    else
      printf("Ignoring unsuported OBJ instruction '%s'.\n",
             cmd.front().c_str());
  }
  return Model(ModelRenderer(data));
}

void Loader::load_materiallib (ModelData::Ptr& data, const string& libname) {
  Parser parser("models/"+libname);
  while (true) {
    Command cmd;
    if (!parser.parse_command(cmd)) break;
    HandlerTable::iterator handler = mtl_handlers_.find(cmd.front());
    if (handler != mtl_handlers_.end())
      handler->second(data, cmd);
    else
      printf("Ignoring unsuported MTL instruction '%s'.\n",
             cmd.front().c_str());
  }
}

#define DEFINE_HANDLER(name) \
  void Loader::handle_##name (ModelData::Ptr data, \
                              const Command& cmd)

// OBJ handlers

DEFINE_HANDLER(objname) {
  // TODO: fix?
  if (cmd.size() >= 2)
    data->set_name(cmd[1]);
}

DEFINE_HANDLER(vertex) {
  double raw_vertex[4] = { 0.0, 0.0, 0.0, 1.0 };
  for (unsigned i = 0; i < 4 && i+1 < cmd.size(); i++)
    raw_vertex[i] = atof(cmd[i+1].c_str());
  data->add_vertex(Base4D(raw_vertex));
}

DEFINE_HANDLER(face) {
  Face                    face;
  Command::const_iterator it;
  for (it = cmd.begin()+1; it != cmd.end(); it++)
    face.push_back(strtoul(it->c_str(), NULL, 0));
  data->add_face(face);
}

DEFINE_HANDLER(materialimport) {
  string libname = cmd[1];
  load_materiallib(data, libname);
}

DEFINE_HANDLER(materialusage) {
  data->add_material_index(cmd[1]);
}

// MTL handlers

DEFINE_HANDLER(newmaterial) {
  // TODO
}

#undef DEFINE_HANDLER

} // namespace obj
} // namespace ep2


