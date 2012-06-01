
#ifndef EP2_CONTROL_MOUSE_H_
#define EP2_CONTROL_MOUSE_H_

#include "point4D.h"
#include "vec4D.h"

namespace ep2 {
namespace control {

class Mouse {
  public:
    Mouse () :
      left_(false),
      middle_(false),
      right_(false) {}
    Point4D position () const { return Point4D(current_.x, current_.y); }
    Vec4D movement () const {
      return Vec4D(current_.x-last_.x, -(current_.y-last_.y));
    }
    bool left () const { return left_; }
    bool middle () const { return middle_; }
    bool right () const { return right_; }
    void move (int x, int y);
    void change_state (int button, int state);
  private:
    struct {
      int x, y;
    }     current_, last_;
    bool  left_, middle_, right_,;
};

} // namespace control
} // namespace ep2

#endif

