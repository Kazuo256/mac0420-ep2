# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/thiago/repositorios/mac0420-ep2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thiago/repositorios/mac0420-ep2

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running interactive CMake command-line interface..."
	/usr/bin/cmake -i .
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/thiago/repositorios/mac0420-ep2/CMakeFiles /home/thiago/repositorios/mac0420-ep2/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/thiago/repositorios/mac0420-ep2/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named ep2

# Build rule for target.
ep2: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ep2
.PHONY : ep2

# fast build rule for target.
ep2/fast:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/build
.PHONY : ep2/fast

src/base4D.o: src/base4D.cxx.o
.PHONY : src/base4D.o

# target to build an object file
src/base4D.cxx.o:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/base4D.cxx.o
.PHONY : src/base4D.cxx.o

src/base4D.i: src/base4D.cxx.i
.PHONY : src/base4D.i

# target to preprocess a source file
src/base4D.cxx.i:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/base4D.cxx.i
.PHONY : src/base4D.cxx.i

src/base4D.s: src/base4D.cxx.s
.PHONY : src/base4D.s

# target to generate assembly for a file
src/base4D.cxx.s:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/base4D.cxx.s
.PHONY : src/base4D.cxx.s

src/ep2.o: src/ep2.cxx.o
.PHONY : src/ep2.o

# target to build an object file
src/ep2.cxx.o:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/ep2.cxx.o
.PHONY : src/ep2.cxx.o

src/ep2.i: src/ep2.cxx.i
.PHONY : src/ep2.i

# target to preprocess a source file
src/ep2.cxx.i:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/ep2.cxx.i
.PHONY : src/ep2.cxx.i

src/ep2.s: src/ep2.cxx.s
.PHONY : src/ep2.s

# target to generate assembly for a file
src/ep2.cxx.s:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/ep2.cxx.s
.PHONY : src/ep2.cxx.s

src/main.o: src/main.cxx.o
.PHONY : src/main.o

# target to build an object file
src/main.cxx.o:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/main.cxx.o
.PHONY : src/main.cxx.o

src/main.i: src/main.cxx.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cxx.i:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/main.cxx.i
.PHONY : src/main.cxx.i

src/main.s: src/main.cxx.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cxx.s:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/main.cxx.s
.PHONY : src/main.cxx.s

src/obj/model.o: src/obj/model.cxx.o
.PHONY : src/obj/model.o

# target to build an object file
src/obj/model.cxx.o:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/obj/model.cxx.o
.PHONY : src/obj/model.cxx.o

src/obj/model.i: src/obj/model.cxx.i
.PHONY : src/obj/model.i

# target to preprocess a source file
src/obj/model.cxx.i:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/obj/model.cxx.i
.PHONY : src/obj/model.cxx.i

src/obj/model.s: src/obj/model.cxx.s
.PHONY : src/obj/model.s

# target to generate assembly for a file
src/obj/model.cxx.s:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/obj/model.cxx.s
.PHONY : src/obj/model.cxx.s

src/point4D.o: src/point4D.cxx.o
.PHONY : src/point4D.o

# target to build an object file
src/point4D.cxx.o:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/point4D.cxx.o
.PHONY : src/point4D.cxx.o

src/point4D.i: src/point4D.cxx.i
.PHONY : src/point4D.i

# target to preprocess a source file
src/point4D.cxx.i:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/point4D.cxx.i
.PHONY : src/point4D.cxx.i

src/point4D.s: src/point4D.cxx.s
.PHONY : src/point4D.s

# target to generate assembly for a file
src/point4D.cxx.s:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/point4D.cxx.s
.PHONY : src/point4D.cxx.s

src/task.o: src/task.cxx.o
.PHONY : src/task.o

# target to build an object file
src/task.cxx.o:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/task.cxx.o
.PHONY : src/task.cxx.o

src/task.i: src/task.cxx.i
.PHONY : src/task.i

# target to preprocess a source file
src/task.cxx.i:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/task.cxx.i
.PHONY : src/task.cxx.i

src/task.s: src/task.cxx.s
.PHONY : src/task.s

# target to generate assembly for a file
src/task.cxx.s:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/task.cxx.s
.PHONY : src/task.cxx.s

src/transform.o: src/transform.cxx.o
.PHONY : src/transform.o

# target to build an object file
src/transform.cxx.o:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/transform.cxx.o
.PHONY : src/transform.cxx.o

src/transform.i: src/transform.cxx.i
.PHONY : src/transform.i

# target to preprocess a source file
src/transform.cxx.i:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/transform.cxx.i
.PHONY : src/transform.cxx.i

src/transform.s: src/transform.cxx.s
.PHONY : src/transform.s

# target to generate assembly for a file
src/transform.cxx.s:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/transform.cxx.s
.PHONY : src/transform.cxx.s

src/vec4D.o: src/vec4D.cxx.o
.PHONY : src/vec4D.o

# target to build an object file
src/vec4D.cxx.o:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/vec4D.cxx.o
.PHONY : src/vec4D.cxx.o

src/vec4D.i: src/vec4D.cxx.i
.PHONY : src/vec4D.i

# target to preprocess a source file
src/vec4D.cxx.i:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/vec4D.cxx.i
.PHONY : src/vec4D.cxx.i

src/vec4D.s: src/vec4D.cxx.s
.PHONY : src/vec4D.s

# target to generate assembly for a file
src/vec4D.cxx.s:
	$(MAKE) -f CMakeFiles/ep2.dir/build.make CMakeFiles/ep2.dir/src/vec4D.cxx.s
.PHONY : src/vec4D.cxx.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... ep2"
	@echo "... rebuild_cache"
	@echo "... src/base4D.o"
	@echo "... src/base4D.i"
	@echo "... src/base4D.s"
	@echo "... src/ep2.o"
	@echo "... src/ep2.i"
	@echo "... src/ep2.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/obj/model.o"
	@echo "... src/obj/model.i"
	@echo "... src/obj/model.s"
	@echo "... src/point4D.o"
	@echo "... src/point4D.i"
	@echo "... src/point4D.s"
	@echo "... src/task.o"
	@echo "... src/task.i"
	@echo "... src/task.s"
	@echo "... src/transform.o"
	@echo "... src/transform.i"
	@echo "... src/transform.s"
	@echo "... src/vec4D.o"
	@echo "... src/vec4D.i"
	@echo "... src/vec4D.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

