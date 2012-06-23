
#include <tr1/functional>

#include "getglut.h"
#include "simulation.h"

namespace ep2 {

using std::string;
using std::vector;
using std::tr1::bind;
using std::tr1::mem_fn;
using namespace std::tr1::placeholders;

void Simulation::init (const string& info_file) {
  vector<Vec4D> infos = utils::LoadForceFieldInfo(info_file.c_str());
  size_ = infos[0];
  dists_ = infos[1];
  field_ = ForceField(size_.x(), size_.y(), size_.z());
  field_.load(infos.begin()+2);
  add_particles(scene_->root());
}

/// Transforms from global coordinates to the force field's coordinates.
/** Actually, it also does the opposite.
 */
static Point4D transform_to_field (Point4D position) {
  Point4D ret(position.x(), -position.y(), -position.z()); 
  return ret;
} 

void Simulation::check_movement (Vec4D& move, const Point4D& pos) const {
  Point4D final_pos;

  final_pos = pos+move;
  if (final_pos.x() > (field_.width()-1)*dists_.x() || final_pos.x() < 0.0)
    move.set_x(0.0);
  if (-final_pos.y() > (field_.height()-1)*dists_.y() || -final_pos.y() < 0.0) 
    move.set_y(0.0);
  if (-final_pos.z() > (field_.depth()-1)*dists_.z() || -final_pos.z() < 0.0) 
    move.set_z(0.0);

}

void Simulation::update_particle (Transform& tform) {
  Vec4D delta_pos;
  Point4D pos_field;
  pos_field = transform_to_field(tform.position());
  delta_pos = field_.interpolate(pos_field);
  delta_pos = delta_pos;
  check_movement(delta_pos, tform.position());
  tform.translate(delta_pos);
}

/// Draws a sphere with the given radius.
static void sphere (double radius) {
  glColor4d(1.0, 0.00, 0.00, 0.7);
  gluSphere( gluNewQuadric(), radius, 6, 6);  
}

void Simulation::add_particles (Transform& tform) {
  int x, y, z;
  for (z = 0; z < field_.depth(); z++)
    for (y = 0; y < field_.height(); y++)
      for (x = 0; x < field_.width(); x++) {
        Point4D position(dists_.x()*x, -dists_.y()*y, -dists_.z()*z);
        Transform modeltform;
        modeltform.set_position(position);
        obj::Model particle = obj::Model(obj::Model::Renderer(
                                              bind(sphere, 0.01)));
        modeltform.pushmodel(particle);
        tform.pushtransform(modeltform);
      }
}

} // namespace ep2

