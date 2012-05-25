#ifndef EP2_MODEL_H_
#define EP2_MODEL_H_

#include <tr1/functional>
#include <tr1/memory>

#include <vector>

namespace ep2 {

class Model {
  public:
    /// Type used to store the rendering function of the object.
    /** It can store either pointer to functions or callable objects that
     ** satisfy the given signature. */
    typedef std::tr1::function<void (void)> Renderer;
    /// Reference-counting smart pointer for renderable objects.
    typedef std::tr1::shared_ptr<Model>     Ptr;
    /// Toggles object visibility.
    void toggle_visibility () {
      visible_ = !visible_;
    }
    /// Renders this object.
    /** Must be called whithin a glut display callback. */
    void render ();
    /// Creates a new renderable object and returns it as a smart pointer.
    /** This guarantees that the user will never have to worry about freeing
     ** its memory.
     ** @param renderer The object's rendering function.
     ** @return Object::Ptr Reference-counting smart pointer to the new
     **                     object. */
    static Ptr create (const Renderer& renderer) {
      return Ptr(new Model(renderer));
    }
  private:
    Model (const Renderer& renderer) :
      visible_(true),
      renderer_(renderer) {}
    // Visibility flag.
    bool      visible_;
    // This object's rendering function.
    Renderer  renderer_;
};

}

#endif
