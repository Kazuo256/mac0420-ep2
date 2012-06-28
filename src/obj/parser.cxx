
#include <cctype>

#include "obj/parser.h"

namespace ep2 {
namespace obj {

using std::string;

Parser::Parser (const string& filename) : objfile(NULL) {
  objfile = fopen(filename.c_str(), "r");
  if (!objfile)
    printf("WARNING! No such file '%s'.\n", filename.c_str());
}

Parser::~Parser () {
  if (objfile)
    fclose(objfile);
}

bool Parser::parse_command (Command& cmd) {
  if (!objfile)
    return false;
  int token;
  // search for first item
  do {
    // skip spaces and empty lines
    while ((token = next()) == ' ' || token == '\t' || token == '\n');
    // end of file, no items found.
    if (token == EOF) return false;
    // comment, skip line.
    if (token == '#') {
      while ((token = next()) != EOF && token != '\n');
      continue;
    } else break; // else something useful has been found.
  } while(true);
  // get command items
  do {
    string item;
    item += token;
    // read item
    while ((token = next()) != ' ' && token != '\t' &&
           token != '\n' && token != EOF && token != '#')
      item += token;
    // add item
    cmd.push_back(item);
    // skip spaces to next item
    if (token == ' ' || token == '\t') {
      while ((token = next()) == ' ' || token == '\t');
      // no more items, stop
      if (token == EOF || token == '\n') break;
      // not comment, then another item has begun
      if (token != '#') continue;
    }
    // comment, skip
    if (token == '#')
      while ((token = next()) != '\n' && token != EOF);
    // finishes at end of line or file
  } while (token != '\n' && token != EOF);
  // at least one item was found
  return true;
}

int Parser::next () { return fgetc(objfile); }

} // namespace obj
} // namespace ep2


