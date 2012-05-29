
#include "ep2.h"
#include "obj/loader.h"
#include "obj/model.h"
#include "task.h"
#include "getglut.h"
#include "point4D.h"
#include "vec4D.h"
#include "transform.h"

namespace ep2 {

void init (int argc, char **argv) {
  glutInit(&argc, argv);
  obj::Loader().load("wall00-00");
}

void run () {
  // Leave it to GLUT.
  //glutMainLoop();
}

}
