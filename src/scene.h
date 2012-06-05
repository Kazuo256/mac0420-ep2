
#ifndef EP2_SCENE_H_
#define EP2_SCENE_H_

#include "task.h"
#include "transform.h"
#include "getglut.h"
#include "camera.h"
#include "collidable.h"

#include <vector>
#include <string>
#include <map>
#include <tr1/memory>
#include <tr1/functional>

namespace ep2 {

class Scene {
  public:
    /// Reference-counting smart pointer for scene objects.
    typedef std::tr1::shared_ptr<Scene>         Ptr;
    /// Vector to store the tasks of a scene.
    typedef std::vector<Task>                   Tasks;
    /// Root that point ot the tree of the scene.
    typedef Transform                           Root;
    /// Keyboard event handler.
    typedef std::tr1::function<void (int, int)> KeyEvent;
    /// Collidables map.
    typedef std::map<std::string, Collidable>   CollTypes;
    /// Gets a reference to the window's camera.
    /** @return Camera& A reference to the window's camera. */
    Camera& camera() { return camera_; }
    ///
    bool active () const { return active_; }
    ///
    void set_active (bool active = true) { active_ = active; }
    ///
    void toggle_active () { active_ = !active_; }
    /// Add a new task to this scene.
    void pushtask (const Task& task);
    /// Update all tasks of this scene.
    void updatetasks ();
    /// Draw the models.
    void draw ();
    /// Return the root of this scene.
    Root& root () { return root_; }
    /// Adds an event to a keyboard input.
    /** @param key    Character key associated to the given event.
     ** @param event  The event that happens when the given key is pressed. */
    void register_keyevent (unsigned char key, KeyEvent event);
    ///
    void check_keyevent (unsigned char key, int x, int y);
    ///
    void insertcolltype (std::string key, Collidable coll);
    ///
    Collidable findcoll (std::string key);
    /// Creates a new scene object.
    CollTypes colltypes () { return colltypes_; }
    static Ptr create() {
      return Ptr(new Scene()); 
    }
  private:
    /// The root of the transforms Tree.
    Root                  root_;
    /// Vector of tasks.
    Tasks                 tasks_;
    // The scene's camera.
    Camera                camera_;
    // Whether the scene is active or not.
    bool                  active_;
    // Collidables types.
    CollTypes             colltypes_;
    // Keyboard events.
    std::vector<KeyEvent> key_events_;
    explicit Scene () :
      active_(true),
      key_events_(256, KeyEvent()) {}
};


} //namespace ep2

#endif
