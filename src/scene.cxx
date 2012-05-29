
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

} //namespace ep2
