
#ifndef EP2_WORLDLOADER_H_
#define EP2_WORLDLOADER_H_

#include <cstdio>
#include <string>

#include "../scene.h"
#include "../transform.h"
#include "model.h"
#include "loader.h"

namespace ep2 {

class WorldLoader {
  public:
    WorldLoader (std::string filename) :
    filename_(filename)  {}
  void loadworld (Scene::Ptr scene);
  private:
    std::string filename_;
    FILE        *infile;
    void loadfile();
};


}//namespace ep2

#endif
