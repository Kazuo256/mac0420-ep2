
#include "collidable.h"

namespace ep2 {

bool Collidable::willmove (char key) {
  Vec4D dir;
  if ( key == 'w' )
    dir = Vec4D(0.0, 0.0, -1);
  else dir = Vec4D(0.0, 0.0, 1);

  Collidables::iterator it;
  
  for ( it = collidables_.begin(); it < collidables_.end(); it++ )
    if ( iscolliding((*it), dir) == true )
      return false;
  return true;
}

bool Collidable::iscolliding (Collidable coll, Vec4D dir) {
  Point4D newpos = pos_+dir;
  // Se if coll will collide with "this". 
  if (((newpos).x()-length_/2) - ((coll.pos_).x()+coll.length_/2) >= 0.0 ) // Coll on the left.
    if (((coll.pos_).x()-coll.length_/2) - ((newpos).x()+length_/2) >= 0.0 ) // Coll on the right.
      if (((newpos).y()-width_/2) - ((coll.pos_).y()+coll.width_/2) >= 0.0 )  // Coll on bottom.
        if (((coll.pos_).y()+coll.width_/2) - ((newpos).y()-width_/2) >= 0.0 ) // Coll on top
          return false;
  return true;
}

}
