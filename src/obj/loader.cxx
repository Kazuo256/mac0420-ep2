
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

#define HANDLERTABLE_SIZE 1
static struct RawHandlerTable {
  const char* tag;
  Handler     handler;
} handlers_table[HANDLERTABLE_SIZE] = {
  {"v", &Loader::handle_vertex}
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
      printf("No handler for '%s'.\n", cmd.front().c_str());
  }
  return Model::create(ModelRenderer(data));
}

void Loader::handle_vertex (ModelDataPtr data, const Command& cmd) {
  double raw_vertex[4] = { 0.0, 0.0, 0.0, 1.0 };
  for (unsigned i = 0; i < 4 && i+1 < cmd.size(); i++)
    raw_vertex[i] = atof(cmd[i+1].c_str());
  data->add_vertex(Base4D(raw_vertex));
}

} // namespace obj
} // namespace ep2


