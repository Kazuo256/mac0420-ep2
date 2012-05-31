
#ifndef EP2_CAMERA_H_
#define EP2_CAMERA_H_

#include "vec4D.h"
#include "point4D.h"
#include "transform.h"

namespace ep2 {

/// Represents the 3D camera.
class Camera {
  public:
    /// Constructor.
    Camera () :
      perspective_(false) {}
    /// Sets the new camera's position.
    /** @param target The new target.  */
    void set_position (const Point4D& position);
    /// Moves the camera around the target.
    /** @param delta Camera movement in sphere coordinates. */
    void move (const Vec4D& movement);
    /// Sets the camera's view volume.
    /** @param width  Volume's width.
     ** @param height Volume's height.
     ** @param depth  Volume's depth. */
    void set_view (double width, double height, double depth) {
      view_ = Vec4D(width, height, depth);
    }
    /// Enframes the camera to the given target.
    /** @param target The reference target to enframe the camera. */
    void enframe (const Vec4D& target);
    /// Zooms the camera by the given variation.
    /** @param delta The zoom variation. */
    void zoom (double delta);
    /// Sets an orthogonal projection with the given ratio.
    /** @param ratio Orthogonal projection aspect ratio. */
    void set_ortho (double ratio);
    /// Sets an perspective projection with the given ratio.
    /** @param ratio Perspective projection aspect ratio. */
    void set_perspective (double ratio);
    /// Toggles between projections, using the given ratio.
    /** @param ratio The new projection aspect ratio. */
    void toggle_projection (double ratio);
    /// Adjusts camera aspect ratio.
    /** @param ratio The new camera's aspect ratio. */
    void adjust (double ratio);
    /// Places the camera in the 3D scene.
    void place () const;
  private:
    Base4D    view_;
    Transform transform_;
    bool  perspective_;
};

} // namespace ep1

#endif

