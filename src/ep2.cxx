
#include "ep2.h"
#include "getglut.h"
#include "window.h"

namespace ep2 {

Window::Ptr win;

void init (int argc, char **argv) {
  // Init GLUT, also capturing glut-intended arguments.
  glutInit(&argc, argv);
  // <--- Insert argument handling here.
  // Everythin OK, let's do this!
  // Init GLUT.
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ALPHA);
  // Define default initial window size.
  Window::init_size(800, 600);
  // Create a window.
  win = Window::create("MAC0420 - EP2");
  win->init(10, 10, 10);
}

void run () {
  // Leave it to GLUT.
  glutMainLoop();
}

}
