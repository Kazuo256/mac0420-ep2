
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

typedef void (Loader::*Handler) (ModelDataPtr&, const Parser::Command&);

struct HandlerTable {
  const char* tag;
  Handler     handler;
} handlers_table[10] = {
  {"v", &Loader::handle_vertex}
};

Loader::Loader () {
  
}

Model::Ptr Loader::load (const string& modelname) {
  Parser parser("models/"+modelname+".obj");
  ModelDataPtr data = ModelData::create();
  while (true) {
    obj::Parser::Command cmd;
    if (!parser.parse_command(cmd)) break;
    for (unsigned i = 0; i < cmd.size(); i++)
      printf("%s ", cmd[i].c_str());
    putchar(10);
  }
  return Model::create(ModelRenderer(data));
}

void Loader::handle_vertex (ModelDataPtr& data, const Parser::Command& cmd) {
  double raw_vertex[4] = { 0.0, 0.0, 0.0, 1.0 };
  for (unsigned i = 0; i < 4 && i+1 < cmd.size(); i++)
    raw_vertex[i] = atof(cmd[i+1].c_str());
  data->add_vertex(Base4D(raw_vertex));
}

} // namespace obj
} // namespace ep2


