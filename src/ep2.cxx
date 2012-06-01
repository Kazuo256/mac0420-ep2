
#include "getglut.h"

#include "ep2.h"
#include "window.h"
#include "scene.h"

namespace ep2 {

Window::Ptr win;

static Scene::Ptr make_scene ();
static bool load_models (Scene::Ptr scene);

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
  // TODO: check correct view size.
  win->pushscene(make_scene());
  win->init();
}

void run () {
  // Leave it to GLUT.
  glutMainLoop();
}

static Scene::Ptr make_scene () {
  Scene::Ptr scene = Scene::create();
  if (!load_models(scene))
    return Scene::Ptr();
  scene->camera().set_perspective(1.0);
  scene->camera().set_view(10.0, 10.0, 10.0);
  return scene;
}

static bool load_models (Scene::Ptr scene) {
  return true;
}

}
