
#include <tr1/functional>

#include "getglut.h"

#include "ep2.h"
#include "window.h"
#include "scene.h"
#include "transform.h"
#include "obj/model.h"
#include "obj/loader.h"

namespace ep2 {

using std::tr1::bind;
using namespace std::tr1::placeholders;
using obj::Model;
using obj::Loader;

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

static void draw_cube () {
  glutSolidCube(1.0);
}

static void camera_task (Scene::Ptr scene) {
  scene->camera().move(Vec4D(0.1, 0.0, 0.0));
}

static void pausescene (Scene::Ptr scene, int x, int y) {
  scene->toggle_active();
}

static Scene::Ptr make_scene () {
  Scene::Ptr scene = Scene::create();
  if (!load_models(scene))
    return Scene::Ptr();
  scene->camera().set_perspective(4.0/3.0);
  scene->camera().set_view(10.0, 10.0, 10.0);
  scene->camera().move(Vec4D(0.0, 3.0, 7.0));
  scene->pushtask(Task(Task::Updater(bind(camera_task, scene))));
  scene->register_keyevent('q',Scene::KeyEvent(bind(pausescene, scene, _1, _2))); 
  //scene->camera().zoom(-5);
  return scene;
}

static bool load_models (Scene::Ptr scene) {
  Model model = Loader().load("wall00-00");
  //Model model = Model(Model::Renderer(draw_cube));
  scene->root().pushmodel(model);
  scene->root().dump();
  return true;
}

}
