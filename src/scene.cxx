
#include "scene.h"

namespace ep2 {

void Scene::pushtask (const Task& task) {
  tasks_.push_back(task);
}

void Scene::updatetasks () {
  if (active_ == false) return;
  Tasks::iterator it;
  for (it=tasks_.begin(); it < tasks_.end(); it++)
    it->update();
}

void drawaux (Transform tform) {
  double matrix[16];

  glPushMatrix();
  tform.matrix().makematrix(matrix);
  glMultMatrixd(matrix);
  
  Transform::ModelVec::const_iterator it;
  for (it = tform.modelvec().begin(); it < tform.modelvec().end(); it++ )
    it->render();
  
  Transform::TransformVec::const_iterator ite;
  for (ite = tform.transformvec().begin(); ite < tform.transformvec().end(); ite++ )
    drawaux((*ite));

  glPopMatrix();
}

void Scene::draw () {
  //glTranslated(0.0, 0.0, -5.0);
  //glutSolidCube(1.0);
  drawaux(root_);
}

void Scene::register_keyevent (unsigned char key, KeyEvent event) {
  key_events_[key] = event;
}

void Scene::check_keyevent (unsigned char key, int x, int y) {
  if (key_events_[key])
    key_events_[key] (x,y);
}

Collidable Scene::findcoll (std::string key) {
  CollTypes::iterator it;
  it = colltypes_.find(key);
  return it->second;
}

void Scene::insertcolltype (std::string key, Collidable coll) {
  colltypes_.insert( std::pair<std::string, Collidable>(key, coll) );
}

} //namespace ep2
