#ifndef EP2_MODEL_H_
#define EP2_MODEL_H_

#include <tr1/functional>
#include <tr1/memory>

#include <vector>

namespace ep2 {
namespace obj {

class Model {
  public:
    /// Type used to store the rendering function of the object.
    /** It can store either pointer to functions or callable objects that
     ** satisfy the given signature. */
    typedef std::tr1::function<void (void)> Renderer;
    /// Constructor.
    /** @param renderer The object's rendering function. */
    Model (const Renderer& renderer) :
      visible_(true),
      renderer_(renderer) {}
    /// Toggles object visibility.
    void toggle_visibility () {
      visible_ = !visible_;
    }
    ///
    void set_visible (bool visible) { visible_ = visible; }
    /// Renders this object.
    /** Must be called whithin a glut display callback. */
    void render () const;
  private:
    // Visibility flag.
    bool      visible_;
    // This object's rendering function.
    Renderer  renderer_;
};

} // namespace obj
} // namespace ep2

#endif
