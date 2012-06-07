
#ifndef EP2_COLLIDABLE_H_
#define EP2_COLLIDABLE_H_

#include <cstdio>
#include <vector>
#include <tr1/memory>
#include "point4D.h"
#include "vec4D.h"
#include "transform.h"

namespace ep2 {

class Scene;

class Collidable {
  public:
    typedef std::vector<Point4D>      Pos;
    typedef std::vector<Collidable>   Collidables;
    Collidable (double width = 0.0, double length = 0.0) :
      width_(width),
      length_(length) {}
    bool willmove (std::tr1::shared_ptr<Scene> scene, unsigned char key);
    void pushcollidable (Collidable collidable);
    void pushtransform (Transform tform);
    void rotate (double ang);
    double width () { return width_; }
    double length () { return length_; }
    Transform::TransformVec tformvec() { return tformvec_; }
  private:
    double        width_, length_;
    Collidables   collidables_;
    Transform::TransformVec  tformvec_;
    /// See if this is colliding with all models in coll.
    bool iscolliding (Collidable coll, Vec4D dir);
    bool iscollidingwithmodel (double w, double l, Base4D point, Vec4D dir);
};

}//namespace ep2

#endif
