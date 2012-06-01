
#include "scene.h"

namespace ep2 {

void Scene::pushtask (const Task& task) {
  tasks_.push_back(task);
}

void Scene::updatetasks () {
  Tasks::iterator it;

  for (it=tasks_.begin(); it < tasks_.end(); it++)
    it->update();
}

void Scene::draw () {
  glPushMatrix();
  glMultMatrixd(root_.matrix()());
  recursivedraw(root_);
  glPopMatrix();
}

void Scene::recursivedraw (Transform transform) {
  glPushMatrix();
  glMultMatrixd(transform.matrix()());

  ModelVec::iterator it

  for (it = transform.

}

} //namespace ep2
