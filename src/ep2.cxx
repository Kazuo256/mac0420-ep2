
#include <tr1/functional>
#include <string>

#include "getglut.h"

#include "ep2.h"
#include "window.h"
#include "scene.h"
#include "transform.h"
#include "obj/model.h"
#include "obj/loader.h"
#include "obj/worldloader.h"

namespace ep2 {

using std::tr1::bind;
using namespace std::tr1::placeholders;
using obj::Model;
using obj::Loader;

Window::Ptr win;

static Scene::Ptr make_scene (Window::Ptr win);
static bool load_models (Scene::Ptr scene, std::string fname);

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
  win->pushscene(make_scene(win));
  win->init();
}

void run () {
  // Leave it to GLUT.
  glutMainLoop();
}

static void movement_task (Scene::Ptr scene, Window::Ptr win) {
  //double x = win->mouse().movement().x();
  //scene->camera().rotatey(x);
}

static void pausescene (Scene::Ptr scene, int x, int y) {
  scene->toggle_active();
}

static void moveW (Scene::Ptr scene, int x, int y) {
  scene->camera().move(Vec4D(0.0, 0.0, -1));
}

static void moveA (Scene::Ptr scene, int x, int y) {
  scene->camera().rotatey(-15.0);
}

static void moveS (Scene::Ptr scene, int x, int y) {
  scene->camera().move(Vec4D(0.0, 0.0, 1));
}

static void moveD (Scene::Ptr scene, int x, int y) {
  scene->camera().rotatey(15.0);
}

void render_skybox () {
  glBegin(GL_QUADS);
    // FRENTE = RED
    glColor3d(1.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 1.0);
    glVertex3d(1.0, 1.0, 1.0);
    glVertex3d(0.0, 1.0, 1.0);
    glVertex3d(0.0, 0.0, 1.0);
    //ATRAS = GREEN
    glColor3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(1.0, 1.0, 0.0);
    glVertex3d(1.0, 0.0, 0.0);
    //TOPO = AMA
    glColor3d(1.0, 1.0, 0.0);   
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(1.0, 1.0, 0.0);
    glVertex3d(1.0, 1.0, 1.0);
    glVertex3d(0.0, 1.0, 1.0);
    //BAIXO = ROXO
    glColor3d(1.0, 0.0, 1.0);   
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, 1.0);
    glVertex3d(1.0, 0.0, 1.0);
    glVertex3d(1.0, 0.0, 0.0);
    //ESQ = PISCINA
    glColor3d(0.0, 1.0, 1.0);   
    glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, 1.0, 1.0);
    glVertex3d(0.0, 0.0, 1.0);
    //DIR = BLUE
    glColor3d(0.0, 0.0, 1.0);   
    glVertex3d(1.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 1.0);
    glVertex3d(1.0, 1.0, 1.0);
    glVertex3d(1.0, 1.0, 0.0);
  glEnd();
  glColor3d(1.0, 1.0, 1.0);
}

static Scene::Ptr make_scene (Window::Ptr win) {
  Scene::Ptr scene = Scene::create();
  if (!load_models(scene, "ime.scene"))
    return Scene::Ptr();
  scene->camera().set_perspective(4.0/3.0);
  scene->camera().set_view(10.0, 10.0, 10.0);
  scene->camera().move(Vec4D(0.0, 3.0, 7.0));
  //scene->pushtask(Task(Task::Updater(bind(camera_task, scene, win))));
  scene->register_keyevent('q', Scene::KeyEvent(bind(pausescene, scene, _1, _2)));
  scene->register_keyevent('w', Scene::KeyEvent(bind(moveW, scene, _1, _2)));
  scene->register_keyevent('a', Scene::KeyEvent(bind(moveA, scene, _1, _2)));
  scene->register_keyevent('s', Scene::KeyEvent(bind(moveS, scene, _1, _2)));
  scene->register_keyevent('d', Scene::KeyEvent(bind(moveD, scene, _1, _2)));
  //scene->camera().zoom(-5);
  return scene;
}

static bool load_models (Scene::Ptr scene, std::string fname) {
  WorldLoader wl = WorldLoader(fname);
  wl.loadworld(scene);
  printf("OI\n");
  /*for (int i = 0; i < 10; i++) {
    Model model = Loader().load("wall00-00");
    Transform tform;
    tform.translate(Vec4D(2.0*i, 0.0, 0.0));
    tform.pushmodel(model);
    scene->root().pushtransform(tform);
  }*/
  Model skybox = Model(Model::Renderer(render_skybox));
  Transform trans;
  trans.pushmodel(skybox);
  trans.scale(Vec4D(100.0, 100.0, 100.0));
  scene->root().pushtransform(trans);
  scene->root().dump();
  return true;
}

}
