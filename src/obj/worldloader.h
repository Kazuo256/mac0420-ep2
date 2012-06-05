
#ifndef EP2_WORLDLOADER_H_
#define EP2_WORLDLOADER_H_

#include <cstdio>
#include <string>

#include "../scene.h"
#include "../transform.h"
#include "../collidable.h"
#include "model.h"
#include "loader.h"

namespace ep2 {

class WorldLoader {
  public:
    WorldLoader (std::string modelfile, std::string collidefile) :
    modelfile_(modelfile),
    collidefile_(collidefile) {}
    void loadworld (Scene::Ptr scene);
  private:
    std::string modelfile_,
                collidefile_;
    FILE        *pmfile,
                *pcfile;
    void loadcollidables (Scene::Ptr scene);
    void loadmodels (Scene::Ptr scene);
    void loadfiles ();
};


}//namespace ep2

#endif
