# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /media/lukas/Data/IONX/Software/UPLS/shared/myqueue

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/lukas/Data/IONX/Software/UPLS/shared/myqueue/build

# Include any dependencies generated for this target.
include CMakeFiles/naqueue.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/naqueue.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/naqueue.dir/flags.make

CMakeFiles/naqueue.dir/test.cpp.o: CMakeFiles/naqueue.dir/flags.make
CMakeFiles/naqueue.dir/test.cpp.o: ../test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/lukas/Data/IONX/Software/UPLS/shared/myqueue/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/naqueue.dir/test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naqueue.dir/test.cpp.o -c /media/lukas/Data/IONX/Software/UPLS/shared/myqueue/test.cpp

CMakeFiles/naqueue.dir/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naqueue.dir/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/lukas/Data/IONX/Software/UPLS/shared/myqueue/test.cpp > CMakeFiles/naqueue.dir/test.cpp.i

CMakeFiles/naqueue.dir/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naqueue.dir/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/lukas/Data/IONX/Software/UPLS/shared/myqueue/test.cpp -o CMakeFiles/naqueue.dir/test.cpp.s

CMakeFiles/naqueue.dir/naqueue.cpp.o: CMakeFiles/naqueue.dir/flags.make
CMakeFiles/naqueue.dir/naqueue.cpp.o: ../naqueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/lukas/Data/IONX/Software/UPLS/shared/myqueue/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/naqueue.dir/naqueue.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/naqueue.dir/naqueue.cpp.o -c /media/lukas/Data/IONX/Software/UPLS/shared/myqueue/naqueue.cpp

CMakeFiles/naqueue.dir/naqueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/naqueue.dir/naqueue.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/lukas/Data/IONX/Software/UPLS/shared/myqueue/naqueue.cpp > CMakeFiles/naqueue.dir/naqueue.cpp.i

CMakeFiles/naqueue.dir/naqueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/naqueue.dir/naqueue.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/lukas/Data/IONX/Software/UPLS/shared/myqueue/naqueue.cpp -o CMakeFiles/naqueue.dir/naqueue.cpp.s

# Object files for target naqueue
naqueue_OBJECTS = \
"CMakeFiles/naqueue.dir/test.cpp.o" \
"CMakeFiles/naqueue.dir/naqueue.cpp.o"

# External object files for target naqueue
naqueue_EXTERNAL_OBJECTS =

naqueue: CMakeFiles/naqueue.dir/test.cpp.o
naqueue: CMakeFiles/naqueue.dir/naqueue.cpp.o
naqueue: CMakeFiles/naqueue.dir/build.make
naqueue: CMakeFiles/naqueue.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/lukas/Data/IONX/Software/UPLS/shared/myqueue/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable naqueue"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/naqueue.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/naqueue.dir/build: naqueue

.PHONY : CMakeFiles/naqueue.dir/build

CMakeFiles/naqueue.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/naqueue.dir/cmake_clean.cmake
.PHONY : CMakeFiles/naqueue.dir/clean

CMakeFiles/naqueue.dir/depend:
	cd /media/lukas/Data/IONX/Software/UPLS/shared/myqueue/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/lukas/Data/IONX/Software/UPLS/shared/myqueue /media/lukas/Data/IONX/Software/UPLS/shared/myqueue /media/lukas/Data/IONX/Software/UPLS/shared/myqueue/build /media/lukas/Data/IONX/Software/UPLS/shared/myqueue/build /media/lukas/Data/IONX/Software/UPLS/shared/myqueue/build/CMakeFiles/naqueue.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/naqueue.dir/depend

