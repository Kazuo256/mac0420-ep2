
#ifndef EP2_OBJ_PARSER_H_
#define EP2_OBJ_PARSER_H_

#include <cstdio>

#include <string>
#include <vector>

namespace ep2 {
namespace obj {

class Parser {
  public:
    typedef std::vector<std::string>  Command;
    Parser (const std::string& filename);
    bool parse_command (Command& cmd);
  private:
    FILE *objfile;
    //bool parse_item (std::string& item);
    int next ();
    //void skip (unsigned mask);
    //void until (unsigned mask);
};

} // namespace obj
} // namespace ep2

#endif

