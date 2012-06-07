
#include "collidable.h"

namespace ep2 {

void Collidable::pushcollidable (Collidable collidable) {
  collidables_.push_back(collidable);
}

void Collidable::pushtransform (Transform tform) {
  tformvec_.push_back(tform);
}

bool Collidable::willmove (Scene::Ptr scene, unsigned char key) {
  Vec4D dir = tformvec_[0].matrix()[2];
  if ( key == 'w' )
    dir = -dir;
  
  Collidables::iterator it;
  /*  See if "this" is colliding with all the collidables class 
      he can collide. */
  for ( it = collidables_.begin(); it < collidables_.end(); it++ )
    if ( iscolliding((*it), dir) == true )
      return false;
  tformvec_[0].translate(dir);
  scene->camera().set_position(tformvec_[0].matrix()[3]);
  return true;
}

bool Collidable::iscolliding (Collidable coll, Vec4D dir) {
  Transform::TransformVec::iterator it;
  if (coll.tformvec_.empty()) return false;
  for ( it = coll.tformvec_.begin(); it < coll.tformvec_.end(); it++ ) {
    if ( iscollidingwithmodel ( coll.width_, 
                                coll.length_, 
                                it->matrix()[3], 
                                dir) )
      return true;
  }
  return false;
}

bool Collidable::iscollidingwithmodel ( double w, 
                                        double l, 
                                        Base4D point, 
                                        Vec4D dir) {
    double x = point.x();
    double z = point.z();
    Point4D newpos = tformvec_[0].matrix()[3]+dir;
    // See if coll will collide with "this". 
    if (   ((newpos.x()-length_/2) > (x+l/2))  // Coll on the left.
        || ((x-l/2) > (newpos.x()+length_/2))  // Coll on the right.
        || ((newpos.z()-width_/2) > (z+w/2))    // Coll on bottom.
        || ((z-w/2) > ((newpos).z()+width_/2))  )// Coll on top
            return false;
    return true;
}

}
