
#ifndef EP2_WINDOW_H_
#define EP2_WINDOW_H_

#include <string>
#include <vector>
#include <utility>
#include <stack>
#include <tr1/unordered_map>
#include <tr1/memory>
#include <tr1/functional>

#include "window.h"
#include "scene.h"
#include "control/mouse.h"

#define WIN_REFRESH 16 /* more or less 60 fps */
#define MILI 1e-3

namespace ep2 {

/// Represents a graphic window.
class Window {
  public:
    /// Reference-counting smart pointer for window objects.
    typedef std::tr1::shared_ptr<Window>        Ptr;
    /// Scene vector.
    typedef std::stack<Scene::Ptr>              SceneStack;
    /// Initializes the window.
    /** Even if created, a window is only displayed if it has been initialized
     ** before. */
    void init ();
    /// Gets the window's resolution ratio.
    /** @return double The window's resolution ratio. */
    double ratio () const { return 1.0*width_/height_; }
    /// Sets this window as the current one, if needed.
    void set_current ();
    /// Defines the initial window size.
    static void init_size(int w, int h);
    /// Get the current scene
    Scene::Ptr currentscene () { return scenestack_.top(); }
    /// Pop the head of the scene stack.
    void popscene () { scenestack_.pop(); }
    /// Add a new scene to the actual window
    void pushscene (const Scene::Ptr& scene);
    /// Update the current Scene
    void update ();
    /// Creates a new window object.
    /** @param caption - The window's caption. */
    static Ptr create (const std::string& caption) {
      Ptr created(new Window(caption));
      windows_[created->id_] = created;
      return created;
    }
  private:
    // Glut window's id.
    int                       id_;
    // Viewport width.
    int                       width_;
    // Viewport height.
    int                       height_;
    // Mouse
    control::Mouse            mouse_;
    // Scenes vector
    SceneStack                scenestack_;
    // Initial window size.
    static int                init_width_, init_height_;
    // Reference base for all created windows.
    static std::tr1::unordered_map<int, Ptr> windows_;
    /// Constructor. See Window::create.
    explicit Window (const std::string& caption);
    /// Retrieves the current window.
    /** @return Window::Ptr Smart-pointer to the current window. */
    static Ptr current_window();
    /// Display callback function for all windows.
    /** Signature follows GLUT specifications. */
    static void display ();
    /// Idle callback function for all windows.
    /** Signature follows GLUT specifications. */
    static void timer_func (int value);
    /// Reshape callback function for all windows.
    /** Signature follows GLUT specifications. */
    static void reshape (int w, int h);
    /// Mouse callback function for all windows.
    /** Signature follows GLUT specifications. */
    static void mouse (int btn, int state, int x, int y);
    /// Mouse motion callback function for all windows.
    /** Signature follows GLUT specifications. */
    static void motion (int x, int y);
    /// Keyboard callsback function for all windows.
    /** Signature follows GLUT specifications. */
    static void keyboard (unsigned char key, int x, int y);
};

} // namespace ep1

#endif

