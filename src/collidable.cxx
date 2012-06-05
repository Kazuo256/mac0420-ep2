
#include "collidable.h"

namespace ep2 {

void Collidable::pushcollidable (Collidable collidable) {
  collidables_.push_back(collidable);
}

void Collidable::pushpos (Point4D pos) {
  pos_.push_back(pos);
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
  pos_[0] = pos_[0] + dir;
  return true;
}

bool Collidable::iscolliding (Collidable coll, Vec4D dir) {
  Point4D newpos = pos_[0]+dir;
  Pos::iterator it;
  for ( it = coll.pos_.begin(); it < coll.pos_.end(); it++ ) {
    double x = it->x();
    double y = it->y();
    // Se if coll will collide with "this". 
    if (((newpos).x()-length_/2) - (x+coll.length_/2) >= 0.0 ) // Coll on the left.
      if ((x-coll.length_/2) - ((newpos).x()+length_/2) >= 0.0 ) // Coll on the right.
        if (((newpos).y()-width_/2) - (y+coll.width_/2) >= 0.0 )  // Coll on bottom.
          if ((y+coll.width_/2) - ((newpos).y()-width_/2) >= 0.0 ) // Coll on top
            return false;
  }
  printf("Corre n\n");
  return true;
}

}
