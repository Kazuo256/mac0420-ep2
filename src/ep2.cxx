
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
#include <cstdlib>

#define PI 3.14159265

namespace ep2 {

using std::tr1::bind;
using namespace std::tr1::placeholders;
using obj::Model;
using obj::Loader;

Window::Ptr win;

static Scene::Ptr make_scene (Window::Ptr win);
static bool load_models (Scene::Ptr scene, std::string modelfile, std::string collidefile),
            fog = false;
static Collidable::Ptr imeguy = Collidable::create(1.0, 1.0);
static double speed_of_the_sun = 10,
              speed_of_the_rain = 10;
static int  rain_number = 64;

static double rand_goroba () {
  return 1.0*rand()/RAND_MAX;
}

void init (int argc, char **argv) {
  // Init GLUT, also capturing glut-intended arguments.
  glutInit(&argc, argv);
  // Rand init
  srand(time(NULL));
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

static void rain_task (Scene::Ptr scene) {
  static int last = 0;
  int current_time = glutGet(GLUT_ELAPSED_TIME);
  int dt = current_time - last;
    Transform::TransformVec::iterator it;
  for ( it = scene->rain().transformvec().begin();
        it < scene->rain().transformvec().end();
        it++ ) {
    double move_rand = 0.25 + rand_goroba()/2;
    it->translate(Vec4D(0.0, -dt*speed_of_the_rain*move_rand*0.004, 0.0));
    if ( it->matrix()[3].y() < 0.0 ) {
      double old_y = it->matrix()[3].y();
      it->translate(Vec4D(0.0, -old_y+50.0, 0.0));
    }
  }
  last = current_time;
}

static void sun_task (Scene::Ptr scene) {
  static int last = 0;
  int current_time = glutGet(GLUT_ELAPSED_TIME);
  int dt = current_time - last;
  scene->sun().rotatex(dt*speed_of_the_sun*0.001);
  last = current_time;
  if (scene->sun().matrix()[3].y() < 0.0) {
    scene->sun().modelvec()[0].set_visible(false);
    glDisable(GL_LIGHT2);
  } else {
    scene->sun().modelvec()[0].set_visible(true);
    glEnable(GL_LIGHT2);
  }
}

void render_rain (Scene::Ptr scene) {
  double old[4];
  glGetDoublev(GL_CURRENT_COLOR, old);
  glBegin(GL_LINES);
  glColor4d(0.5, 1.0, 1.0, 0.7);
  glVertex3f(0.0, 0.0, 0.0);
  glColor4d(0.8, 1.0, 1.0, 0.2);
  glVertex3f(0.0, 0.5, 0.0);
  glEnd();
  glColor3dv(old);
}

static void createrain (Scene::Ptr scene, int rain_number) {
  for ( int j = 0; j < rain_number; j++ ) {
    for ( int i = 0; i < rain_number; i++ ) {
      Transform tform;
      Model rain = Model(Model::Renderer(bind(render_rain, scene)));
      double pos_rand = rand_goroba()*10;
      tform.set_position(Point4D(-125.0+i*(250.0/rain_number),50.0+pos_rand,-125.0+j*(250.0/rain_number)));
      tform.pushmodel(rain);
      scene->rain().pushtransform(tform);
    }
  }
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

static void increaserain (Scene::Ptr scene, int x, int y) {
  if ( rain_number <= 256 ) {
    scene->rain().transformvec().clear();
    rain_number += 8;
    createrain(scene, rain_number);
  }
}

static void decreaserain (Scene::Ptr scene, int x, int y) {
  if ( rain_number >= 0 ) {
    scene->rain().transformvec().clear();
    rain_number -= 8;
    createrain(scene, rain_number);
  }    
}

static void increasespeed (int x, int y) {
  speed_of_the_sun += 10.0;
  printf("Aumentei pra : %lf\n",speed_of_the_sun);
}

static void decreasespeed (int x, int y) {
  speed_of_the_sun -= 10.0;
  printf("diminui pra : %lf\n",speed_of_the_sun);
}

static void toogle_fog (int x, int y) {
  if ( fog == true ) {
    glDisable(GL_FOG);
    fog = false;
  } else {
    glEnable(GL_FOG);
    fog = true;
  }
}

void draw_shadow (Scene::Ptr scene) {
  scene->toggle_shadow();
  double aux[3];
  aux[0] = scene->sun().matrix()[3].val()[0];
  aux[1] = scene->sun().matrix()[3].val()[1];
  aux[2] = scene->sun().matrix()[3].val()[2];
  Transform::Matrix T1(Base4D::X(), Base4D::Y(), Base4D::Z(), Base4D(-aux[0], -aux[1], -aux[2], 1.0));
  Transform::Matrix M(Base4D(1.0, 0.0, 0.0, 0.0), 
                      Base4D(0.0, 1.0, 0.0, -1.0/aux[1]), 
                      Base4D(0.0, 0.0, 1.0, 0.0), 
                      Base4D(0.0, 0.0, 0.0, 0.0));
  Transform::Matrix T2(Base4D::X(), Base4D::Y(), Base4D::Z(), Base4D(aux[0], aux[1], aux[2], 1.0));
  Transform::Matrix T3(Base4D::X(), Base4D::Y(), Base4D::Z(), Base4D(0.0, 0.1, 0.0, 1.0));
  scene->root().composition(T1);
  scene->root().composition(M);
  scene->root().composition(T2);
  scene->root().composition(T3);
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);
  //glEnable(GL_STENCIL_TEST);
  //glClearStencil(0);
  glPushMatrix();
  glLoadIdentity();
  glColor4d(0.0, 0.0, 0.0, 1.0);
  scene->draw();
  glPopMatrix();
  //glDisable(GL_STENCIL_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glColor4d(1.0, 1.0, 1.0, 1.0);
  scene->root().set_identity();
}

void render_sun (Scene::Ptr scene) {
  float pos[] = { 0.0f, 0.0f, 1.0f, 0.0f },
        white[] = { 1.0f, 1.0f, 1.0f, 1.0f },
        yellow[] = { 1.0f, 1.0f, 0.4f, 1.0f };
  //double old[4];
  //glGetDoublev(GL_CURRENT_COLOR, old);
  //glColor3d(1.0, 1.0, 0.0);
  glLightfv(GL_LIGHT2, GL_POSITION, pos); 
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, yellow);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, yellow);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
  glutSolidSphere(1.0, 10, 10);
  //glColor3dv(old);
  draw_shadow(scene);
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

static void createfog () {
  GLfloat fcolor[4] = {0.7, 0.7, 0.7, 1.0};

  glClearColor(0.5f,0.5f,0.5f,1.0f);          // We'll Clear To The Color Of The Fog ( Modified )
 
  glFogi(GL_FOG_MODE, GL_EXP2);        // Fog Mode
  glFogfv(GL_FOG_COLOR, fcolor);            // Set Fog Color
  glFogf(GL_FOG_DENSITY, 0.01f);              // How Dense Will The Fog Be
  glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
  glFogf(GL_FOG_START, 1.0f);             // Fog Start Depth
  glFogf(GL_FOG_END, 5.0f);               // Fog End Depth
  if ( fog == true ) glEnable(GL_FOG);                   // Enables GL_FOG
}

static Scene::Ptr make_scene (Window::Ptr win) {
  Scene::Ptr scene = Scene::create();
    if (!load_models(scene, "ime.scene", "ime.collidables"))
    return Scene::Ptr();
  createrain(scene, rain_number);
  scene->camera().set_perspective(4.0/3.0);
  scene->camera().set_view(30.0, 30.0, 30.0);
  scene->camera().set_position(Point4D(0.0, 4.0, 7.0));
  scene->rain().set_position(Point4D(0.0, 0.0, 7.0));
  //scene->pushtask(Task(Task::Updater(bind(camera_task, win))));
  scene->pushtask(Task(Task::Updater(bind(sun_task, scene))));
  scene->pushtask(Task(Task::Updater(bind(rain_task, scene))));
  scene->register_keyevent('q', Scene::KeyEvent(bind(pausescene, scene, _1, _2)));
  scene->register_keyevent('w', Scene::KeyEvent(bind(moveW, scene, _1, _2)));
  scene->register_keyevent('a', Scene::KeyEvent(bind(moveA, scene, _1, _2)));
  scene->register_keyevent('s', Scene::KeyEvent(bind(moveS, scene, _1, _2)));
  scene->register_keyevent('d', Scene::KeyEvent(bind(moveD, scene, _1, _2)));
  scene->register_keyevent('1', Scene::KeyEvent(increasespeed));
  scene->register_keyevent('2', Scene::KeyEvent(decreasespeed));
  scene->register_keyevent('3', Scene::KeyEvent(bind(increaserain, scene, _1, _2)));
  scene->register_keyevent('4', Scene::KeyEvent(bind(decreaserain, scene, _1, _2)));
  scene->register_keyevent('f', Scene::KeyEvent(toogle_fog));
  //scene->camera().zoom(-5);
  createimeguy(scene);
  createfog();
  return scene;
}

static bool load_models (Scene::Ptr scene, std::string modelfile, std::string collidefile) {
  WorldLoader wl = WorldLoader(modelfile, collidefile);
  wl.loadworld(scene);
  Model sun = Model(Model::Renderer(bind(render_sun, scene)));
  Transform trans;
  trans.pushmodel(sun);
  trans.scale(Vec4D(1.0, 1.0, 1.0));
  trans.set_position(Point4D(0.0, 0.0, 70.0));
  scene->set_sun(trans);
  return true;
}

}
