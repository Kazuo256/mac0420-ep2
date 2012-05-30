
#include "ep2.h"
#include "getglut.h"
#include "window.h"

namespace ep2 {

Window::Ptr win;

void init (int argc, char **argv) {
  glutInit(&argc, argv);
  Window::init_size(800, 600);
  win = Window::create("MAC0420 - EP2");
  win->init(10, 10, 10);
}

void run () {
  // Leave it to GLUT.
  glutMainLoop();
}

}
