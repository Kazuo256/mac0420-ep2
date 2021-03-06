
#include "scene.h"
#include "collidable.h"
#include "obj/modelrenderer.h"

namespace ep2 {

using std::string;

void Scene::pushtask (const Task& task) {
  tasks_.push_back(task);
}

void Scene::updatetasks () {
  if (active_ == false) return;
  Tasks::iterator it;
  for (it=tasks_.begin(); it < tasks_.end(); it++)
    it->update();
}

void Scene::drawaux (Transform tform) {
  double matrix[16];

  glPushMatrix();
  tform.matrix().makematrix(matrix);
  glMultMatrixd(matrix);
  
  Transform::ModelVec::const_iterator it;
  for (it = tform.modelvec().begin(); it < tform.modelvec().end(); it++ )
    if (!shadow_)
      it->render();
    else shadow_ = !shadow_;

  Transform::TransformVec::const_iterator ite;
  for (ite = tform.transformvec().begin(); ite < tform.transformvec().end(); ite++ )
    drawaux((*ite));

  glPopMatrix();
}

void Scene::draw () {
  // Place the camera.
  camera_.place();
  {
    float pos[4] = {0.0, -1.0, 0.0, 0.0};
    glLightfv(GL_LIGHT1, GL_POSITION, pos);
  }
  if (!shadow_) {
    drawaux(root_);
    drawaux(sun_);
    drawaux(rain_);
  } else {
    drawaux(root_);
  }
}

void Scene::register_keyevent (unsigned char key, KeyEvent event) {
  key_events_[key] = event;
}

void Scene::check_keyevent (unsigned char key, int x, int y) {
  if (key_events_[key])
    key_events_[key] (x,y);
}

void Scene::add_collidable_obj (const string& coll_name,
                                const Transform& tform) {
  if (colltypes_.find(coll_name) == colltypes_.end())
    return; // TODO: warning
  colltypes_[coll_name]->pushtransform(tform);
}

void Scene::insertcolltype (const string& key, Collidable::Ptr coll) {
  colltypes_.insert( std::pair<std::string, Collidable::Ptr>(key, coll) );
}

} //namespace ep2
