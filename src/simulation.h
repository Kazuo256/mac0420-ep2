
#ifndef EP2_SIMULATION_H_
#define EP2_SIMULATION_H_

#include <string>
#include <vector>

#include <tr1/memory>

#include "vec4D.h"
#include "point4D.h"
#include "scene.h"
#include "forcefield.h"
#include "obj/model.h"
#include "utils.h"

namespace ep2 {

/// Represents a particle simulation environment.
class Simulation {
  public:
    /// Reference-counting smart pointer for simulation objects.
    typedef std::tr1::shared_ptr<Simulation> Ptr;
    /// Creates a new Simulation object.
    /** @param win    The window used to display the simulation.
     ** @param ratio  Size ratio used to render the simulation elements.
     ** @return Simulation::Ptr A smart-pointer to a simulation object. */
    static Ptr create (const Scene::Ptr& scene, double ratio) {
      return Ptr(new Simulation(scene, ratio));
    }
    /// Initializes the simulation from the given information file.
    /** Even if created, a simulation only runs if it has been initialized
     ** before.
     ** The information file must follow the specification found in
     ** <b>EP1-2012.pdf</b>.
     ** @param info_file Path to the simulation information file. */
    void init (const std::string& info_file);
    /// Toggles forces display visibility.
    void show_hide_forces ();
  private:
    double                    ratio_;
    Vec4D                     size_,
                              dists_;
    Scene::Ptr                scene_;
    ForceField                field_;
    std::vector<obj::Model>   particles_;
    /// Constructor. See Simulation::create.
    explicit Simulation (const Scene::Ptr& scene, double ratio) :
      ratio_(ratio), scene_(scene) {}
    /// Adds all particles to the simulation.
    void add_particles (Transform& tform);
    /// Updates a particle object.
    /** Calculates the force field speed at its position and applies the
     ** movement, making sure the particle stays within the simulation bounds.
     ** @param particle The particle object being updated. */
    void update_particle (Transform& tform);
    /// Checks a given movement at a given position.
    /** If the movement would move something beyond the simulation bounds, the
     ** necessary modifications are made to ensure that such a thing does not
     ** happen.
     ** @param move A reference to the movement vector. Its value may be
                    changed to avoid trespassing boundaries.
     ** @param pos  The position at which the movement happens. */
    void check_movement (Vec4D& move, const Point4D& pos) const;
};

} // namespace ep1

#endif

