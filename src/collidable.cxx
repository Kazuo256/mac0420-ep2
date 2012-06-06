
#include "collidable.h"

namespace ep2 {

void Collidable::pushcollidable (Collidable collidable) {
  collidables_.push_back(collidable);
}

void Collidable::pushtransform (Transform tform) {
  tformvec_.push_back(tform);
}

bool Collidable::willmove (char key) {
  Vec4D dir;
  if ( key == 'w' )
    dir = Vec4D(0.0, 0.0, -1);
  else dir = Vec4D(0.0, 0.0, 1);
  
  Collidables::iterator it;
  /*  See if "this" is colliding with all the collidables class 
      he can collide. */
  for ( it = collidables_.begin(); it < collidables_.end(); it++ )
    if ( iscolliding((*it), dir) == true )
      return false;
  tformvec_[0].matrix()[3] = tformvec_[0].matrix()[3] + dir;
  return true;
}

bool Collidable::iscolliding (Collidable coll, Vec4D dir) {
  Point4D newpos = tformvec_[0].matrix()[3]+dir;
  Transform::TransformVec::iterator it;
  for ( it = coll.tformvec_.begin(); it < coll.tformvec_.end(); it++ ) {
    double x = it->matrix()[3].x();
    double z = it->matrix()[3].z();
    // See if coll will collide with "this". 
    if (   ((newpos.x()-length_/2) > (x+coll.length_/2))  // Coll on the left.
        || ((x-coll.length_/2) > (newpos.x()+length_/2))  // Coll on the right.
        || ((newpos.z()-width_/2) > (z+coll.width_/2))    // Coll on bottom.
        || ((z-coll.width_/2) > ((newpos).z()+width_/2))  )// Coll on top
            return false;
  }
  return true;
}

}
