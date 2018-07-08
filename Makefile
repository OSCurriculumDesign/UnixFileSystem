# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hallwood/Code/devenv/UnixFileSystem

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hallwood/Code/devenv/UnixFileSystem

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/hallwood/Code/devenv/UnixFileSystem/CMakeFiles /home/hallwood/Code/devenv/UnixFileSystem/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/hallwood/Code/devenv/UnixFileSystem/CMakeFiles 0
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
# Target rules for targets named unix_file_sys

# Build rule for target.
unix_file_sys: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 unix_file_sys
.PHONY : unix_file_sys

# fast build rule for target.
unix_file_sys/fast:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/build
.PHONY : unix_file_sys/fast

cpp/block.o: cpp/block.cpp.o

.PHONY : cpp/block.o

# target to build an object file
cpp/block.cpp.o:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/block.cpp.o
.PHONY : cpp/block.cpp.o

cpp/block.i: cpp/block.cpp.i

.PHONY : cpp/block.i

# target to preprocess a source file
cpp/block.cpp.i:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/block.cpp.i
.PHONY : cpp/block.cpp.i

cpp/block.s: cpp/block.cpp.s

.PHONY : cpp/block.s

# target to generate assembly for a file
cpp/block.cpp.s:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/block.cpp.s
.PHONY : cpp/block.cpp.s

cpp/format.o: cpp/format.cpp.o

.PHONY : cpp/format.o

# target to build an object file
cpp/format.cpp.o:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/format.cpp.o
.PHONY : cpp/format.cpp.o

cpp/format.i: cpp/format.cpp.i

.PHONY : cpp/format.i

# target to preprocess a source file
cpp/format.cpp.i:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/format.cpp.i
.PHONY : cpp/format.cpp.i

cpp/format.s: cpp/format.cpp.s

.PHONY : cpp/format.s

# target to generate assembly for a file
cpp/format.cpp.s:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/format.cpp.s
.PHONY : cpp/format.cpp.s

cpp/ialloc.o: cpp/ialloc.cpp.o

.PHONY : cpp/ialloc.o

# target to build an object file
cpp/ialloc.cpp.o:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/ialloc.cpp.o
.PHONY : cpp/ialloc.cpp.o

cpp/ialloc.i: cpp/ialloc.cpp.i

.PHONY : cpp/ialloc.i

# target to preprocess a source file
cpp/ialloc.cpp.i:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/ialloc.cpp.i
.PHONY : cpp/ialloc.cpp.i

cpp/ialloc.s: cpp/ialloc.cpp.s

.PHONY : cpp/ialloc.s

# target to generate assembly for a file
cpp/ialloc.cpp.s:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/ialloc.cpp.s
.PHONY : cpp/ialloc.cpp.s

cpp/igetput.o: cpp/igetput.cpp.o

.PHONY : cpp/igetput.o

# target to build an object file
cpp/igetput.cpp.o:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/igetput.cpp.o
.PHONY : cpp/igetput.cpp.o

cpp/igetput.i: cpp/igetput.cpp.i

.PHONY : cpp/igetput.i

# target to preprocess a source file
cpp/igetput.cpp.i:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/igetput.cpp.i
.PHONY : cpp/igetput.cpp.i

cpp/igetput.s: cpp/igetput.cpp.s

.PHONY : cpp/igetput.s

# target to generate assembly for a file
cpp/igetput.cpp.s:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/igetput.cpp.s
.PHONY : cpp/igetput.cpp.s

cpp/name.o: cpp/name.cpp.o

.PHONY : cpp/name.o

# target to build an object file
cpp/name.cpp.o:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/name.cpp.o
.PHONY : cpp/name.cpp.o

cpp/name.i: cpp/name.cpp.i

.PHONY : cpp/name.i

# target to preprocess a source file
cpp/name.cpp.i:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/name.cpp.i
.PHONY : cpp/name.cpp.i

cpp/name.s: cpp/name.cpp.s

.PHONY : cpp/name.s

# target to generate assembly for a file
cpp/name.cpp.s:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/name.cpp.s
.PHONY : cpp/name.cpp.s

cpp/varseg.o: cpp/varseg.cpp.o

.PHONY : cpp/varseg.o

# target to build an object file
cpp/varseg.cpp.o:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/varseg.cpp.o
.PHONY : cpp/varseg.cpp.o

cpp/varseg.i: cpp/varseg.cpp.i

.PHONY : cpp/varseg.i

# target to preprocess a source file
cpp/varseg.cpp.i:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/varseg.cpp.i
.PHONY : cpp/varseg.cpp.i

cpp/varseg.s: cpp/varseg.cpp.s

.PHONY : cpp/varseg.s

# target to generate assembly for a file
cpp/varseg.cpp.s:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/cpp/varseg.cpp.s
.PHONY : cpp/varseg.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/unix_file_sys.dir/build.make CMakeFiles/unix_file_sys.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... unix_file_sys"
	@echo "... edit_cache"
	@echo "... cpp/block.o"
	@echo "... cpp/block.i"
	@echo "... cpp/block.s"
	@echo "... cpp/format.o"
	@echo "... cpp/format.i"
	@echo "... cpp/format.s"
	@echo "... cpp/ialloc.o"
	@echo "... cpp/ialloc.i"
	@echo "... cpp/ialloc.s"
	@echo "... cpp/igetput.o"
	@echo "... cpp/igetput.i"
	@echo "... cpp/igetput.s"
	@echo "... cpp/name.o"
	@echo "... cpp/name.i"
	@echo "... cpp/name.s"
	@echo "... cpp/varseg.o"
	@echo "... cpp/varseg.i"
	@echo "... cpp/varseg.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

