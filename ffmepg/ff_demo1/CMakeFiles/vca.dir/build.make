# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_SOURCE_DIR = /home/vca/C++_demo/ffmepg/ff_demo1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vca/C++_demo/ffmepg/ff_demo1

# Include any dependencies generated for this target.
include CMakeFiles/vca.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/vca.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/vca.dir/flags.make

CMakeFiles/vca.dir/vca.cpp.o: CMakeFiles/vca.dir/flags.make
CMakeFiles/vca.dir/vca.cpp.o: vca.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/vca/C++_demo/ffmepg/ff_demo1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/vca.dir/vca.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/vca.dir/vca.cpp.o -c /home/vca/C++_demo/ffmepg/ff_demo1/vca.cpp

CMakeFiles/vca.dir/vca.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/vca.dir/vca.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/vca/C++_demo/ffmepg/ff_demo1/vca.cpp > CMakeFiles/vca.dir/vca.cpp.i

CMakeFiles/vca.dir/vca.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/vca.dir/vca.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/vca/C++_demo/ffmepg/ff_demo1/vca.cpp -o CMakeFiles/vca.dir/vca.cpp.s

CMakeFiles/vca.dir/vca.cpp.o.requires:

.PHONY : CMakeFiles/vca.dir/vca.cpp.o.requires

CMakeFiles/vca.dir/vca.cpp.o.provides: CMakeFiles/vca.dir/vca.cpp.o.requires
	$(MAKE) -f CMakeFiles/vca.dir/build.make CMakeFiles/vca.dir/vca.cpp.o.provides.build
.PHONY : CMakeFiles/vca.dir/vca.cpp.o.provides

CMakeFiles/vca.dir/vca.cpp.o.provides.build: CMakeFiles/vca.dir/vca.cpp.o


# Object files for target vca
vca_OBJECTS = \
"CMakeFiles/vca.dir/vca.cpp.o"

# External object files for target vca
vca_EXTERNAL_OBJECTS =

vca: CMakeFiles/vca.dir/vca.cpp.o
vca: CMakeFiles/vca.dir/build.make
vca: CMakeFiles/vca.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/vca/C++_demo/ffmepg/ff_demo1/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable vca"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/vca.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/vca.dir/build: vca

.PHONY : CMakeFiles/vca.dir/build

CMakeFiles/vca.dir/requires: CMakeFiles/vca.dir/vca.cpp.o.requires

.PHONY : CMakeFiles/vca.dir/requires

CMakeFiles/vca.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/vca.dir/cmake_clean.cmake
.PHONY : CMakeFiles/vca.dir/clean

CMakeFiles/vca.dir/depend:
	cd /home/vca/C++_demo/ffmepg/ff_demo1 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vca/C++_demo/ffmepg/ff_demo1 /home/vca/C++_demo/ffmepg/ff_demo1 /home/vca/C++_demo/ffmepg/ff_demo1 /home/vca/C++_demo/ffmepg/ff_demo1 /home/vca/C++_demo/ffmepg/ff_demo1/CMakeFiles/vca.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/vca.dir/depend

