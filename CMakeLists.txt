
cmake_minimum_required (VERSION 2.8)

project (ep2 CXX C)
include_directories (src)

find_package(OpenGL REQUIRED)
if (${OPENGL_FOUND})
  include_directories (${OPENGL_INCLUDE_DIR})
else (${OPENGL_FOUND})
  message (FATAL_ERROR "OpenGL not found!")
endif (${OPENGL_FOUND})

find_package(GLUT REQUIRED)
if (${GLUT_FOUND})
  include_directories (${GLUT_INCLUDE_DIR})
else (${GLUT_FOUND})
  message (FATAL_ERROR "GLUT not found!")
endif (${GLUT_FOUND})

add_executable (ep2
  src/main.cxx
  src/ep2.cxx
  src/obj/model.cxx
  src/obj/parser.cxx
  src/task.cxx
  src/vec4D.cxx
  src/point4D.cxx
  src/base4D.cxx
  src/transform.cxx
)
target_link_libraries (ep2 ${OPENGL_LIBRARIES} ${GLUT_glut_LIBRARY})
set_target_properties (ep2 PROPERTIES COMPILE_FLAGS "-ansi -Wall -O2")
message(${OPENGL_LIBRARIES} ${GLUT_glut_LIBRARY})
