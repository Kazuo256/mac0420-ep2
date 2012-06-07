
cmake_minimum_required (VERSION 2.8)

project (ep2 CXX C)
include_directories (src)

find_package(OpenGL REQUIRED)
if (${OPENGL_FOUND})
  include_directories (${OPENGL_INCLUDE_DIR})
  message ("-- OpenGL includes: ${OPENGL_INCLUDE_DIR}")
else (${OPENGL_FOUND})
  message (FATAL_ERROR "OpenGL not found!")
endif (${OPENGL_FOUND})

find_package(GLUT REQUIRED)
if (${GLUT_FOUND})
  include_directories (${GLUT_INCLUDE_DIR})
  message ("-- Glut includes: ${GLUT_INCLUDE_DIR}")
else (${GLUT_FOUND})
  message (FATAL_ERROR "GLUT not found!")
endif (${GLUT_FOUND})

find_package(DevIL REQUIRED)
if (${IL_FOUND})
  include_directories (${IL_INCLUDE_DIR})
  message ("-- DevIL includes: ${IL_INCLUDE_DIR}")
else (${IL_FOUND})
  message (FATAL_ERROR "DevIL not found!")
endif (${IL_FOUND})

add_executable (ep2
  src/main.cxx
  src/ep2.cxx
  src/obj/model.cxx
  src/obj/modeldata.cxx
  src/obj/modelrenderer.cxx
  src/obj/parser.cxx
  src/obj/loader.cxx
  src/obj/worldloader.cxx
  src/obj/texture.cxx
  src/task.cxx
  src/vec4D.cxx
  src/point4D.cxx
  src/base4D.cxx
  src/transform.cxx
  src/scene.cxx
  src/window.cxx
  src/camera.cxx
  src/collidable.cxx
  src/control/mouse.cxx
)

target_link_libraries (ep2 ${OPENGL_LIBRARIES} ${GLUT_glut_LIBRARY} ${IL_LIBRARIES} ${ILUT_LIBRARIES})
set_target_properties (ep2 PROPERTIES COMPILE_FLAGS "-ansi -Wall -O0 -g")

