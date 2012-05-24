
#include <cctype>

#include "obj/parser.h"

namespace ep2 {
namespace obj {

using std::string;

Parser::Parser (const string& filename) : objfile(NULL) {
  objfile = fopen(filename.c_str(), "r");
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
      while ((token = next()) != EOF || token != '\n');
      continue;
    } else break; // else something useful has been found.
  } while(true);
  // get command items
  do {
    string item;
    item += token;
    // read item
    while ((token == next()) != ' ' && token != '\t' &&
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

//struct token {
//  int val;
//  token () : val(0) {}
//  token& next (FILE *in) { val = fgetc(in); return *this; }
//  token& undo (FILE *in) { ungetc(val, in); return *this; }
//  unsigned type () const {
//    switch(val) {
//      case EOF: return eof();
//      case '\n': return eol();
//      case '#': return comment();
//      case ' ':
//      case '\t': return space();
//      default: return any();
//    }
//  }
//  static unsigned eof () { return 0x1; }
//  static unsigned eol () { return 0x2; }
//  static unsigned comment () { return 0x4; }
//  static unsigned space () { return 0x8; }
//  static unsigned any () { return 0x10; }
//};

int Parser::next () { return fgetc(objfile); }

/*
void Parser::skip (unsigned mask) {
  token t;
  for (t.next(objfile); t.type() & mask; t.next(objfile));
  t.undo(objfile);
}

void Parser::until (unsigned mask) {
  token t;
  for (t.next(objfile); !(t.type() & mask); t.next(objfile));
  t.undo(objfile);
}

static bool is_item_token (int token) {
  return !isspace(token) && token != EOF;
}

bool Parser::skip_to_item () {
  int token;
  while (!is_item_token(token = fgetc(objfile)));

}

void Parser::skip_space () {
  int token;
  while (isspace(token = fgetc(objfile)));
  ungetc(token, objfile);
}

void Parser::skip_line () {
  while (!feof(objfile) && fgetc(objfile) != '\n');
}
*/

} // namespace obj
} // namespace ep2


