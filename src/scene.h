
#ifndef EP2_SCENE_H_
#define EP2_SCENE_H_

#include "task.h"
#include "transform.h"
#include "getglut.h"

#include <vector>
#include <tr1/memory>

namespace ep2 {

class Scene {
  public:
    /// Reference-counting smart pointer for scene objects.
    typedef std::tr1::shared_ptr<Scene> Ptr;
    /// Vector to store the tasks of a scene.
    typedef std::vector<Task>           Tasks;
    /// Root that point ot the tree of the scene.
    typedef Transform                   Root;
    
    static Ptr create() {
      return Ptr(new Scene); 
    }
    /// Add a new task to this scene.
    void pushtask (const Task& task);
    /// Update all tasks of this scene.
    void updatetasks ();
    /// Draw the models.
    void draw ();
    /// Return the root of this scene.
    Root& root () { return root_; }
  private:
    /// The root of the transforms Tree.
    Root  root_;
    /// Vector of tasks.
    Tasks tasks_;
    
    void recursivedraw (Transform transform);

    explicit Scene () {}
};


} //namespace ep2

#endif
