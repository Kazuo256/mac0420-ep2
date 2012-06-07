
#ifndef EP2_COLLIDABLE_H_
#define EP2_COLLIDABLE_H_

#include <cstdio>
#include <vector>
#include <tr1/memory>

#include "point4D.h"
#include "vec4D.h"
#include "transform.h"
#include "scene.h"

namespace ep2 {

class Collidable {
  public:
    /// Reference-counting smart pointer for scene objects.
    typedef std::tr1::shared_ptr<Collidable>  Ptr;
    typedef std::vector<Collidable::Ptr>      Collidables;
    bool willmove (Scene::Ptr scene, unsigned char key);
    void pushcollidable (Collidable collidable);
    void pushtransform (Transform tform);
    void rotate (double ang);
    double width () { return width_; }
    double length () { return length_; }
    Transform::TransformVec tformvec() { return tformvec_; }
    static Ptr create(double width = 0.0, double length = 0.0) {
      return Ptr(new Collidable(width, length)); 
    }
  private:
    double        width_, length_;
    Collidables   collidables_;
    Transform::TransformVec  tformvec_;
    explicit Collidable (double width = 0.0, double length = 0.0) :
      width_(width),
      length_(length) {}
    /// See if this is colliding with all models in coll.
    bool iscolliding (Collidable coll, Vec4D dir);
    bool iscollidingwithmodel (double w, double l, Base4D point, Vec4D dir);
};

}//namespace ep2

#endif
