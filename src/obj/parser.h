
#ifndef EP2_OBJ_PARSER_H_
#define EP2_OBJ_PARSER_H_

#include <string>
#include <vector>

namespace ep2 {
namespace obj {

class Parser {
  public:
    typedef std::vector<const std::string>  Command;
    typedef std::vector<const Command>      CommandList;
    Parser () {}
    CommandList parse (const std::string& filename);
};

} // namespace obj
} // namespace ep2

#endif

