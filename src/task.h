#ifndef EP2_TASK_H_
#define EP2_TASK_H_

#include <tr1/functional>
#include <tr1/memory>

#include "vec4D.h"
#include "obj/model.h"

namespace ep2 {

/// Represents a renderable object.
class Task {
  public:
    /// Type used to store the update function of the object.
    /** It can store either pointer to functions or callable objects that
     ** satisfy the given signature. */
    typedef std::tr1::function<void (void)>  Updater;
    /// Reference-counting smart pointer for renderable objects.
    typedef std::tr1::shared_ptr<Task>    Ptr;
    /// Updates this object.
    /** Must be called whithin a glut timed callback. */
    void update ();
    /// Creates a new renderable object and returns it as a smart pointer.
    /** This guarantees that the user will never have to worry about freeing
     ** its memory.
     ** @return Object::Ptr Reference-counting smart pointer to the new
     **                     object. */
    static Ptr create (const Updater& updater) {
      return Ptr(new Task(updater));
    }
  private:
    // This object's rendering function.
    Updater   updater_;
    explicit Task (const Updater updater) :
      updater_(updater) {}
};

} // namespace ep1

#endif

