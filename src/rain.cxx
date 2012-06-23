#include "rain.h"

namespace ep2 {

void Rain::init () { 
  simul_ = Simulation::create(scene_, 1); 
  simul_->init(force_file_);
}

}
