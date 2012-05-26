
#ifndef EP2_OBJ_PARSER_H_
#define EP2_OBJ_PARSER_H_

#include <cstdio>

#include <string>
#include <vector>

namespace ep2 {
namespace obj {

typedef std::vector<std::string> Command;

class Parser {
  public:
    Parser (const std::string& filename);
    bool parse_command (Command& cmd);
  private:
    FILE *objfile;
    int next ();
};

} // namespace obj
} // namespace ep2

#endif

