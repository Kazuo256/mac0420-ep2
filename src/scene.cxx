
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

void Scene::register_keyevent (unsigned char key, KeyEvent event) {
  key_events_[key] = event;
}

void Scene::check_keyevent (unsigned char key, int x, int y) {
  if (key_events_[key])
    key_events_[key] (x,y);
}

} //namespace ep2
