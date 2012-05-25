
#include <vector>

#include "obj/loader.h"
#include "obj/parser.h"

namespace ep2 {
namespace obj {

using std::string;

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

} // namespace obj
} // namespace ep2


