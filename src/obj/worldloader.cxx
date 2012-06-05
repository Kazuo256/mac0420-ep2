

#include "obj/worldloader.h"

namespace ep2 {

using obj::Model;
using obj::Loader;

void WorldLoader::loadworld (Scene::Ptr scene) {
  loadfiles();
  loadmodels(scene);
}

void WorldLoader::loadmodels (Scene::Ptr scene) {
  char objname[64];
  while ( fscanf(pmfile, "%s", objname) != EOF ) {
    Model model = Loader().load(objname);
    Transform tform;
    tform.pushmodel(model);
    
    double buffer[4];
    Transform::Matrix matrix;
    for (int j = 0; j < 4; j++) {
      for (int i = 0; i < 4; i++) {
        fscanf(pmfile, "%lf", &buffer[i]);
        printf("%lf-",buffer[i]);
      }
      matrix[j].set_val(buffer);
    }
    tform.composition(matrix);
    scene->root().pushtransform(tform);
  }
}

void WorldLoader::loadfiles () {
  pmfile = fopen(modelfile_.c_str(), "r");
  pcfile = fopen(collidefile_.c_str(), "r");
}

}//namespace ep2

