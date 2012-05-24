
#include "ep2.h"
#include "obj/model.h"
#include "obj/parser.h"
#include "task.h"
#include "getglut.h"
#include "point4D.h"
#include "vec4D.h"
#include "transform.h"

namespace ep2 {

void init (int argc, char **argv) {
  glutInit(&argc, argv);
  obj::Parser parser("models/wall00-00.obj");
  while (true) {
    obj::Parser::Command cmd;
    if (!parser.parse_command(cmd)) break;
    for (unsigned i = 0; i < cmd.size(); i++)
      printf(cmd[i].c_str()), putchar(' ');
    putchar(10);
  }
}

void run () {
  // Leave it to GLUT.
  //glutMainLoop();
}

}
