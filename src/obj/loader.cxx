
#include <vector>

#include "obj/loader.h"
#include "obj/parser.h"
#include "obj/modeldata.h"

namespace ep2 {
namespace obj {

using std::string;
using std::tr1::bind;

typedef void (Loader::*handler_t) (ModelDataPtr&);

struct HandlerTable {
  const char* tag;
  handler_t   handler;
} handlers_table[10] = {
  {"v", &Loader::handle_vertex}
};

Loader::Loader () {
  
}

Model::Ptr Loader::load (const string& modelname) {
  obj::Parser parser("models/"+modelname+".obj");
  while (true) {
    obj::Parser::Command cmd;
    if (!parser.parse_command(cmd)) break;
    for (unsigned i = 0; i < cmd.size(); i++)
      printf("%s ", cmd[i].c_str());
    putchar(10);
  }
  return Model::Ptr();
}

void Loader::handle_vertex (ModelDataPtr& data) {

}

} // namespace obj
} // namespace ep2


