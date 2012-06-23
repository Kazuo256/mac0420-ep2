
#include "getglut.h"
#include "utils.h"

namespace ep2 {

namespace utils { 

using std::vector;

vector<ep2::Vec4D> LoadForceFieldInfo (const std::string& file_name) {
  FILE                *pfile;
  vector<ep2::Vec4D>  infos;
  double              X, Y, Z, distX, distY, distZ;
  int                 nX, nY, nZ, count;
  char                buffer[BUFFER_SIZE];
  
  pfile = fopen(file_name.c_str(), "r");
  if (pfile == NULL) {
    printf("Arquivo não encontrado. Finalizando programa.\n");
    exit(EXIT_FAILURE);
  }

  if(!fgets(buffer, BUFFER_SIZE, pfile)) {
    puts("Input problem.");
    exit(EXIT_FAILURE);
  }
  sscanf(buffer, "%d %d %d", &nX, &nY, &nZ);
  infos.push_back(Vec4D(nX, nY, nZ));

  if(!fgets(buffer, BUFFER_SIZE, pfile)) {
    puts("Input problem.");
    exit(EXIT_FAILURE);
  }
  sscanf(buffer, "%lf %lf %lf", &distX, &distY, &distZ);
  infos.push_back(Vec4D(distX, distY, distZ));

  for (count = 0; count < nX*nY*nZ; count++) {
    if(!fgets(buffer, BUFFER_SIZE, pfile)) {
      puts("Input problem.");
      exit(EXIT_FAILURE);
    }
    sscanf(buffer, "%lf %lf %lf", &X, &Y, &Z);
    infos.push_back(Vec4D(X, Y, Z));     
  }
  
  return infos;
  }

}

}
