
#include <cstdio>
#include <cmath>
#include <algorithm>

#include "getglut.h"
#include "window.h"
#include "vec4D.h"
#include "collidable.h"

namespace ep2 {

using std::vector;
using std::tr1::unordered_map;

int                             Window::init_width_,
                                Window::init_height_;
unordered_map<int, Window::Ptr> Window::windows_;

Window::Window (const std::string& caption) :
  width_ (init_width_), 
  height_(init_height_),
  frame_count_(0),
  fps_(0.0),
  previous_time_(0.0)  {
  id_ = glutCreateWindow(caption.c_str());
}

/// Initializes OpenGL stuff.
static void init_opengl (double ratio) {
  glEnable(GL_DEPTH_TEST);
  //camera.set_perspective(ratio);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glLineWidth(2.0);
  glEnable(GL_BLEND);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_COLOR_MATERIAL);
  glStencilFunc(GL_NOTEQUAL, 1, ~0);
  glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
  {
    float ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f },
          diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
  }
  {
    float ambient[] = { 0.3f, 0.3f, 0.2f, 1.0f },
          diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
  }
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::init () {
  glutSetWindow(id_);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutIdleFunc(idle);
  glutMouseFunc(mousefunc);
  glutMotionFunc(motion);
  glutKeyboardFunc(keyboard);
  //camera_.set_view(w, h, d);
  init_opengl(ratio());
}

void Window::init_size (int w, int h) {
  init_width_ = w;
  init_height_ = h;
  glutInitWindowSize(w, h);
}

void Window::popscene () {
  scenestack_.pop();
  if (currentscene() && currentscene()->active())
    glutTimerFunc(WIN_REFRESH, timer_func, 1);
}

void Window::pushscene (const Scene::Ptr& scene) {
  scenestack_.push(scene);
  if (currentscene() && currentscene()->active())
    glutTimerFunc(WIN_REFRESH, timer_func, 1);
}

void Window::set_current () {
  if (glutGetWindow() != id_)
    glutSetWindow(id_);
}

Window::Ptr Window::current_window () {
  return windows_[glutGetWindow()];
}

void Window::reshape(int w, int h) {
  // Get the current window.
  Ptr win = current_window();
  // Update window resolution info.
  win->width_ = w;
  win->height_ = h;
  // Adjust camera and viewport.
  win->currentscene()->camera().adjust(win->ratio());
  glViewport((GLint)0, (GLint)0, (GLint)w, (GLint)h); 
  // Display changes.
  glutPostRedisplay();
}

void Window::mousefunc (int btn, int state, int x, int y) {
  // Get the current window. 
  Ptr win = current_window();
  // Update mouse buttons' state.
  win->mouse_.change_state(btn, state);
  win->mouse_.move(x, y);
  // Display changes.
  glutPostRedisplay();
}

void Window::motion (int x, int y) {
  // Get the current window.
  Ptr win = current_window();
  // Calculate mouse motion.
  win->mouse_.move(x, y);
  // Display changes.
  glutPostRedisplay();
}

void Window::keyboard (unsigned char key, int x, int y) {
  // Get the current window.
  Ptr win = current_window();
  // Activate registered event.
  win->currentscene()->check_keyevent(key, x, y);
  // Default events.
  switch (key) {
    case 'q':
      //win->stop_ = !win->stop_;
      //if (win->stop_ == 0)  glutTimerFunc(WIN_REFRESH, timer_func, 1);
      break;
    default: break;
  }
  // Display changes.in
  glutPostRedisplay();
}

void setOrthographicProjection(Window::Ptr win) {    
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, win->width(), 0, win->height());
  glScalef(1, -1, 1);
  glTranslatef(0, -win->height(), 0);
  glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}

void renderBitmapString(float x, float y,char *string)
{  
  char *c;
      
  glRasterPos2f(x, y);
          
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
  }
}

void printfps (Window::Ptr win) {
  char out[64], fps[10];
  strcpy(out, "Current FPS:"); 
  sprintf(fps, "%f", win->fps());
  strcat(out, fps);
  
  double old[4];
  glGetDoublev(GL_CURRENT_COLOR, old);
  glColor3d(1.0, 1.0, 1.0);

  setOrthographicProjection(win);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  renderBitmapString(30.0, 30.0, out);
  glPopMatrix();
  glColor3dv(old);
  resetPerspectiveProjection();
}

void Window::display () {
  // Get the current window.
  Ptr win = current_window();
  // Prepare for drawing the scene.
  glMatrixMode(GL_MODELVIEW);   
  glLoadIdentity();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Call the draw from the current scene.
  win->currentscene()->draw();
  printfps(win);
  // Swap buffers to display result.
  glutSwapBuffers();
}

void Window::idle () {
  Ptr win = current_window();
  win->fpscalculator();
  glutPostRedisplay();
}

void Window::fpscalculator () {
  frame_count_++;
  
  double current_time = glutGet(GLUT_ELAPSED_TIME);

  int timeInterval = current_time - previous_time_;

  if ( timeInterval > 1000 ) {
    fps_ = frame_count_/(timeInterval/1000.0f);
    previous_time_ = current_time;
    frame_count_ = 0;
  }
}

void Window::timer_func (int value) {
  // Get the current window.
  Ptr win = current_window();
  // Update all objects.
  win->currentscene()->updatetasks();
  // Prepare for next update, if needed.
  //if (win->stop_ == 0)
    glutTimerFunc(WIN_REFRESH, timer_func, 1);
  // Display changes.
  glutPostRedisplay(); 
}

} // namespace ep2

