

#include "obj/worldloader.h"

namespace ep2 {

using obj::Model;
using obj::Loader;

void WorldLoader::loadworld (Scene::Ptr scene) {
  loadfiles();
  loadcollidables(scene);
  loadmodels(scene);
}

void WorldLoader::loadcollidables (Scene::Ptr scene) {
  char objname[64];
  while ( fscanf(pcfile, "%s", objname) != EOF ) {
    double length, width;
    fscanf(pcfile, "%lf %lf", &length, &width);
    Collidable coll(width, length);
    std::string collname = objname;
    scene->insertcolltype (collname, coll);
  }
}

void WorldLoader::loadmodels (Scene::Ptr scene) {
  char objname[64];
  while ( fscanf(pmfile, "%s", objname) != EOF ) {
    Model model = Loader().load_model(objname);
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
    std::string name = objname;
    tform.composition(matrix);
    scene->findcoll(name).pushtransform(tform);
    scene->root().pushtransform(tform);
  }
}

void WorldLoader::loadfiles () {
  pmfile = fopen(modelfile_.c_str(), "r");
  pcfile = fopen(collidefile_.c_str(), "r");
}

}//namespace ep2

