
#include "ep2.h"
#include "model.h"
#include "task.h"

namespace ep2 {

void init (int argc, char **argv) {
  glutInit(&argc, argv);
}

void run () {
  // Leave it to GLUT.
  glutMainLoop();
}

}
