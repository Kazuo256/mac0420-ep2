#ifndef EP2_RAIN_H_
#define EP2_RAIN_H_

#include "forcefield.h"
#include "simulation.h"
#include "scene.h"

#include <string>

namespace ep2 {

class Rain {
  public:
    Rain (const std::string& force_file, Scene::Ptr& scene) :
      force_file_(force_file),
      scene_(scene)           {}
    void init ();
  private:
    const std::string force_file_;
    Scene::Ptr        scene_;
    Simulation::Ptr   simul_;
};

}

#endif
