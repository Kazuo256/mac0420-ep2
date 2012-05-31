
#ifndef EP2_SCENE_H_
#define EP2_SCENE_H_

#include "task.h"
#include "transform.h"

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
    
    void pushtask (const Task& task);
    void updatetasks ();
    Root& root () { return root_; }
  private:
    Root  root_;
    Tasks tasks_;

    explicit Scene () {}
};

} //namespace ep2

#endif
