
#include <cstdlib>
#include <vector>

#include "obj/loader.h"
#include "obj/modeldata.h"
#include "obj/modelrenderer.h"

namespace ep2 {
namespace obj {

using std::string;
using std::vector;
using std::tr1::bind;
using std::tr1::unordered_map;
using namespace std::tr1::placeholders;

typedef void (Loader::*Handler) (ModelDataPtr, const Command&);

#define HANDLERTABLE_SIZE 5
#define GET_HANDLER(name) &Loader::handle_##name

static struct RawHandlerTable {
  const char* tag;
  Handler     handler;
} handlers_table[HANDLERTABLE_SIZE] = {
  {"o", GET_HANDLER(objname) },
  {"v", GET_HANDLER(vertex) },
  {"f", GET_HANDLER(face) },
  {"mtllib", GET_HANDLER(materialimport) },
  {"usemtl", GET_HANDLER(materialusage) }
};

Loader::Loader () {
  for (unsigned i = 0; i < HANDLERTABLE_SIZE; i++)
    handlers_[handlers_table[i].tag] =
      bind(handlers_table[i].handler, this, _1, _2);
}

Model::Ptr Loader::load (const string& modelname) {
  Parser parser("models/"+modelname+".obj");
  ModelDataPtr data = ModelData::create();
  while (true) {
    Command cmd;
    if (!parser.parse_command(cmd)) break;
    HandlerTable::iterator handler = handlers_.find(cmd.front());
    if (handler != handlers_.end())
      handler->second(data, cmd);
    else
      printf("Ignoring unsuported OBJ instruction '%s'.\n",
             cmd.front().c_str());
  }
  return Model::create(ModelRenderer(data));
}

#define DEFINE_HANDLER(name) \
  void Loader::handle_##name (ModelDataPtr data, \
                              const Command& cmd)

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
  
}

DEFINE_HANDLER(materialimport) {

}

DEFINE_HANDLER(materialusage) {

}

#undef DEFINE_HANDLER

} // namespace obj
} // namespace ep2


