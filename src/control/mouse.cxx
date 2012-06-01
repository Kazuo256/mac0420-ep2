
#include "getglut.h"
#include "control/mouse.h"

namespace ep2 {
namespace control {

void Mouse::move (int x, int y) {
  last_ = current_;
  current_.x = x;
  current_.y = y;
}

void Mouse::change_state (int button, int state) {
  bool new_state = (state == GLUT_DOWN);
  switch (button) {
    case GLUT_LEFT_BUTTON:
      left_ = new_state;
      break;
    case GLUT_MIDDLE_BUTTON:
      middle_ = new_state;
      break;
    case GLUT_RIGHT_BUTTON:
      right_ = new_state;
      break;
    default: break;
  }
}

} // namespace control
} // namespace ep2

