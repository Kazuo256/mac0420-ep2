

#include "obj/worldloader.h"

namespace ep2 {

using obj::Model;
using obj::Loader;

void WorldLoader::loadworld (Scene::Ptr scene) {
  char objname[64];
  loadfile();
  while ( fscanf(infile, "%s", objname) != EOF ) {
    Model model = Loader().load(objname);
    Transform tform;
    tform.pushmodel(model);
    
    double buffer[4];
    Transform::Matrix matrix;
    for (int j = 0; j < 4; j++) {
      printf("Coluna-%d\n", j);
      for (int i = 0; i < 4; i++) {
        fscanf(infile, "%lf", &buffer[i]);
        printf("%lf-",buffer[i]);
      }
      printf("\n");
      matrix[j].set_val(buffer);
    }
    tform.composition(matrix);
    scene->root().pushtransform(tform);
  }
}

void WorldLoader::loadfile () {
  infile = fopen(filename_.c_str(), "r");
}

}//namespace ep2

