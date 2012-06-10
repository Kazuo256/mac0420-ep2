
#include <tr1/functional>
#include <string>

#include "getglut.h"

#include "ep2.h"
#include "window.h"
#include "scene.h"
#include "transform.h"
#include "collidable.h"
#include "obj/model.h"
#include "obj/loader.h"
#include "obj/worldloader.h"
#include "obj/modelrenderer.h"

#include <tr1/memory>
#include <tr1/functional>
#include <cmath>

#define PI 3.14159265

namespace ep2 {

using std::tr1::bind;
using namespace std::tr1::placeholders;
using obj::Model;
using obj::Loader;

Window::Ptr win;

static Scene::Ptr make_scene (Window::Ptr win);
static bool load_models (Scene::Ptr scene, std::string modelfile, std::string collidefile);
static Collidable::Ptr imeguy = Collidable::create(1.0, 1.0);
static double speed_of_the_sun = 100;

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

//static void camera_task (Window::Ptr win) {
//  Point4D pos = win->mouse().position();
//  if (pos.y() > 250) 
//    win->currentscene()->camera().rotatex(1.0);
//  else if (pos.y() < 350)
//    win->currentscene()->camera().rotatex(-1.0);
//}

static void sun_task (Scene::Ptr scene) {
  double current_time = glutGet(GLUT_ELAPSED_TIME);
  current_time = fmod(current_time, (PI/180));
  scene->sun().rotatex(current_time*speed_of_the_sun);
  glLightfv(GL_LIGHT2, GL_POSITION, (float*)Point4D().val());
}

static void pausescene (Scene::Ptr scene, int x, int y) {
  scene->toggle_active();
}

static void moveW (Scene::Ptr scene, int x, int y) {
  if ( imeguy->willmove(scene, 'w') == true );
    //scene->camera().move(Vec4D(0.0, 0.0, -1));
}

static void moveA (Scene::Ptr scene, int x, int y) {
  scene->camera().rotatey(-15.0);
  imeguy->rotate(15.0);
}

static void moveS (Scene::Ptr scene, int x, int y) {
  if ( imeguy->willmove(scene, 's') == true );
    //scene->camera().move(Vec4D(0.0, 0.0, 1));
}

static void moveD (Scene::Ptr scene, int x, int y) {
  scene->camera().rotatey(15.0);
  imeguy->rotate(-15.0);
}

static void increasespeed (int x, int y) {
  speed_of_the_sun += 50.0;
  printf("Aumentei pra : %lf\n",speed_of_the_sun);
}

static void decreasespeed (int x, int y) {
  speed_of_the_sun -= 50.0;
  printf("diminui pra : %lf\n",speed_of_the_sun);
}

void render_sun () {
  double old[4];
  glGetDoublev(GL_CURRENT_COLOR, old);
  glColor3d(1.0, 1.0, 0.0);
  glutSolidSphere(2.0, 10, 10);
  glLightfv(GL_LIGHT2, GL_POSITION, (float*)Point4D().val()); 
  glColor3dv(old);
}

static void createimeguy (Scene::Ptr scene) {
  Transform tform;
  tform.translate(Vec4D(0.0, 4.0, 7.0));
  imeguy->pushtransform(tform);
  Scene::CollTypes::const_iterator it;
  for ( it = scene->colltypes().begin(); it != scene->colltypes().end(); it++ )
    if (it->second)
      imeguy->pushcollidable(it->second);
  scene->insertcolltype("imeguy", imeguy);
}

static Scene::Ptr make_scene (Window::Ptr win) {
  Scene::Ptr scene = Scene::create();
    if (!load_models(scene, "ime.scene", "ime.collidables"))
    return Scene::Ptr();
  scene->camera().set_perspective(4.0/3.0);
  scene->camera().set_view(30.0, 30.0, 30.0);
  scene->camera().set_position(Point4D(0.0, 4.0, 7.0));
  //scene->pushtask(Task(Task::Updater(bind(camera_task, win))));
  scene->pushtask(Task(Task::Updater(bind(sun_task, scene))));
  scene->register_keyevent('q', Scene::KeyEvent(bind(pausescene, scene, _1, _2)));
  scene->register_keyevent('w', Scene::KeyEvent(bind(moveW, scene, _1, _2)));
  scene->register_keyevent('a', Scene::KeyEvent(bind(moveA, scene, _1, _2)));
  scene->register_keyevent('s', Scene::KeyEvent(bind(moveS, scene, _1, _2)));
  scene->register_keyevent('d', Scene::KeyEvent(bind(moveD, scene, _1, _2)));
  scene->register_keyevent('1', Scene::KeyEvent(increasespeed));
  scene->register_keyevent('2', Scene::KeyEvent(decreasespeed));
  //scene->camera().zoom(-5);
  createimeguy(scene);
  return scene;
}

static bool load_models (Scene::Ptr scene, std::string modelfile, std::string collidefile) {
  WorldLoader wl = WorldLoader(modelfile, collidefile);
  wl.loadworld(scene);
  Model sun = Model(Model::Renderer(render_sun));
  Transform trans;
  trans.pushmodel(sun);
  trans.scale(Vec4D(0.5, 0.5, 0.5));
  trans.set_position(Point4D(0.0, 0.0, 70.0));
  scene->set_sun(trans);
  
  return true;
}

}
