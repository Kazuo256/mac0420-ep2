
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

namespace ep2 {

using std::tr1::bind;
using namespace std::tr1::placeholders;
using obj::Model;
using obj::Loader;

Window::Ptr win;

static Scene::Ptr make_scene (Window::Ptr win);
static bool load_models (Scene::Ptr scene, std::string modelfile, std::string collidefile);
static Collidable::Ptr imeguy = Collidable::create(1.0, 1.0);

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

static void camera_task (Scene::Ptr scene) {
  //scene->camera().set_position(imeguy.tformvec()[0].matrix()[3]);
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

void render_skybox () {
  obj::ModelRenderer::default_material();
  glBegin(GL_QUADS);
    // FRENTE = RED
    glColor3d(1.0, 0.0, 0.0);
    glVertex3d(1.0, 0.0, 1.0);
    glVertex3d(1.0, 2.0, 1.0);
    glVertex3d(-1.0, 2.0, 1.0);
    glVertex3d(-1.0, 0.0, 1.0);
    //ATRAS = GREEN
    glColor3d(0.0, 1.0, 0.0);
    glVertex3d(-1.0, 0.0, -1.0);
    glVertex3d(-1.0, 2.0, -1.0);
    glVertex3d(1.0, 2.0, -1.0);
    glVertex3d(1.0, 0.0, -1.0);
    //TOPO = AMA
    glColor3d(1.0, 1.0, 0.0);   
    glVertex3d(-1.0, 2.0, -1.0);
    glVertex3d(1.0, 2.0, -1.0);
    glVertex3d(1.0, 2.0, 1.0);
    glVertex3d(-1.0, 2.0, 1.0);
    //BAIXO = ROXO
    glColor3d(1.0, 0.0, 1.0);   
    glVertex3d(-1.0, 0.0, -1.0);
    glVertex3d(-1.0, 0.0, 1.0);
    glVertex3d(1.0, 0.0, 1.0);
    glVertex3d(1.0, 0.0, -1.0);
    //ESQ = PISCINA
    glColor3d(0.0, 1.0, 1.0);   
    glVertex3d(-1.0, 0.0, -1.0);
    glVertex3d(-1.0, 2.0, -1.0);
    glVertex3d(-1.0, 2.0, 1.0);
    glVertex3d(-1.0, 0.0, 1.0);
    //DIR = BLUE
    glColor3d(0.0, 0.0, 1.0);   
    glVertex3d(1.0, 0.0, -1.0);
    glVertex3d(1.0, 0.0, 1.0);
    glVertex3d(1.0, 2.0, 1.0);
    glVertex3d(1.0, 2.0, -1.0);
  glEnd();
  glColor3d(1.0, 1.0, 1.0);
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
  scene->pushtask(Task(Task::Updater(bind(camera_task, scene))));
  scene->register_keyevent('q', Scene::KeyEvent(bind(pausescene, scene, _1, _2)));
  scene->register_keyevent('w', Scene::KeyEvent(bind(moveW, scene, _1, _2)));
  scene->register_keyevent('a', Scene::KeyEvent(bind(moveA, scene, _1, _2)));
  scene->register_keyevent('s', Scene::KeyEvent(bind(moveS, scene, _1, _2)));
  scene->register_keyevent('d', Scene::KeyEvent(bind(moveD, scene, _1, _2)));
  //scene->camera().zoom(-5);
  createimeguy(scene);
  return scene;
}

static bool load_models (Scene::Ptr scene, std::string modelfile, std::string collidefile) {
  WorldLoader wl = WorldLoader(modelfile, collidefile);
  wl.loadworld(scene);
  Model skybox = Model(Model::Renderer(render_skybox));
  Transform trans;
  trans.pushmodel(skybox);
  trans.scale(Vec4D(120.0, 120.0, 50.0));
  scene->root().pushtransform(trans);
  return true;
}

}
