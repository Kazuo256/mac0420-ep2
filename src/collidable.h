
#ifndef EP2_COLLIDABLE_H_
#define EP2_COLLIDABLE_H_

#include <cstdio>
#include <vector>
#include "point4D.h"
#include "vec4D.h"
#include "transform.h"

namespace ep2 {

class Collidable {
  public:
    typedef std::vector<Collidable>  Collidables;
    Collidable (double width, double length) :
      width_(width),
      length_(length) {}
    bool willmove (char key);
    void pushcollidable (Collidable collidable);
    void pushtransform (Transform tfrom); 
  private:
    double                    width_, length_;
    Collidables               collidables_;
    Transform::TransformVec   tformvec_;
    /// See if this is colliding with all models in coll.
    bool iscolliding (Collidable coll, Vec4D dir);
};

}//namespace ep2

#endif
