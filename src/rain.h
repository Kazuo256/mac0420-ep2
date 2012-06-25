#ifndef EP2_RAIN_H_
#define EP2_RAIN_H_

#include "scene.h"

#include <string>

namespace ep2 {

class Rain {
  public:
    Rain (Scene::Ptr scene) :
      scene_(scene)           {}
    void init ();
  private:
    Scene::Ptr        scene_;
};

}

#endif
