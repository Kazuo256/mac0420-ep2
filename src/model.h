#ifndef EP1_RENDER_H_
#define EP1_RENDER_H_

#include <tr1/functional>
#include <tr1/memory>

namespace ep2 {

class Model {
  public:
    /// Type used to store the rendering function of the object.
    /** It can store either pointer to functions or callable objects that
     ** satisfy the given signature. */
    typedef std::tr1::function<void (void)> Renderer;
    Model (const Renderer& renderer) :
      visible_(true),
      redenrer_(renderer) {}
    /// Toggles object visibility.
    void toggle_visibility () {
      visible_ = !visible_;
    }
    /// Renders this object.
    /** Must be called whithin a glut display callback. */
    void render ();
  private:
    // Visibility flag.
    bool      visible_;
    // This object's rendering function.
    Renderer  renderer_;
};

}
