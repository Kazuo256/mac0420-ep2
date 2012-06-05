
#ifndef EP2_COLLIDABLE_H_
#define EP2_COLLIDABLE_H_

#include <vector>
#include "point4D.h"
#include "vec4D.h"

namespace ep2 {

class Collidable {
  public:
    typedef std::vector<Collidable>  Collidables;
    Collidable (Point4D pos, double width, double length) :
      pos_(pos),
      width_(width),
      length_(length) {}
    bool willmove (char key);
    void pushcollidable (Collidable collidable);
  private:
    Point4D       pos_;
    double      width_, length_;
    Collidables collidables_;
    bool iscolliding (Collidable coll, Vec4D dir);
};

}//namespace ep2

#endif
