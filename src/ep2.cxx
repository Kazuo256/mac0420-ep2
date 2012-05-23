
#include "ep2.h"
#include "obj/model.h"
#include "task.h"
#include "getglut.h"

namespace ep2 {

void init (int argc, char **argv) {
  glutInit(&argc, argv);
}

void run () {
  // Leave it to GLUT.
  glutMainLoop();
}

}
