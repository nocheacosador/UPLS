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
CMAKE_SOURCE_DIR = /media/lukas/Data/IONX/Software/UPLS/UPLS_Py

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build

# Include any dependencies generated for this target.
include src/CMakeFiles/lib_UPLS.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/lib_UPLS.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/lib_UPLS.dir/flags.make

src/CMakeFiles/lib_UPLS.dir/packet.cpp.o: src/CMakeFiles/lib_UPLS.dir/flags.make
src/CMakeFiles/lib_UPLS.dir/packet.cpp.o: ../src/packet.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/lib_UPLS.dir/packet.cpp.o"
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lib_UPLS.dir/packet.cpp.o -c /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/src/packet.cpp

src/CMakeFiles/lib_UPLS.dir/packet.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_UPLS.dir/packet.cpp.i"
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/src/packet.cpp > CMakeFiles/lib_UPLS.dir/packet.cpp.i

src/CMakeFiles/lib_UPLS.dir/packet.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_UPLS.dir/packet.cpp.s"
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/src/packet.cpp -o CMakeFiles/lib_UPLS.dir/packet.cpp.s

src/CMakeFiles/lib_UPLS.dir/serialport.cpp.o: src/CMakeFiles/lib_UPLS.dir/flags.make
src/CMakeFiles/lib_UPLS.dir/serialport.cpp.o: ../src/serialport.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/lib_UPLS.dir/serialport.cpp.o"
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lib_UPLS.dir/serialport.cpp.o -c /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/src/serialport.cpp

src/CMakeFiles/lib_UPLS.dir/serialport.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_UPLS.dir/serialport.cpp.i"
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/src/serialport.cpp > CMakeFiles/lib_UPLS.dir/serialport.cpp.i

src/CMakeFiles/lib_UPLS.dir/serialport.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_UPLS.dir/serialport.cpp.s"
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/src/serialport.cpp -o CMakeFiles/lib_UPLS.dir/serialport.cpp.s

src/CMakeFiles/lib_UPLS.dir/upls_controller.cpp.o: src/CMakeFiles/lib_UPLS.dir/flags.make
src/CMakeFiles/lib_UPLS.dir/upls_controller.cpp.o: ../src/upls_controller.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/lib_UPLS.dir/upls_controller.cpp.o"
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lib_UPLS.dir/upls_controller.cpp.o -c /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/src/upls_controller.cpp

src/CMakeFiles/lib_UPLS.dir/upls_controller.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lib_UPLS.dir/upls_controller.cpp.i"
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/src/upls_controller.cpp > CMakeFiles/lib_UPLS.dir/upls_controller.cpp.i

src/CMakeFiles/lib_UPLS.dir/upls_controller.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lib_UPLS.dir/upls_controller.cpp.s"
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/src/upls_controller.cpp -o CMakeFiles/lib_UPLS.dir/upls_controller.cpp.s

# Object files for target lib_UPLS
lib_UPLS_OBJECTS = \
"CMakeFiles/lib_UPLS.dir/packet.cpp.o" \
"CMakeFiles/lib_UPLS.dir/serialport.cpp.o" \
"CMakeFiles/lib_UPLS.dir/upls_controller.cpp.o"

# External object files for target lib_UPLS
lib_UPLS_EXTERNAL_OBJECTS =

src/lib_UPLS.a: src/CMakeFiles/lib_UPLS.dir/packet.cpp.o
src/lib_UPLS.a: src/CMakeFiles/lib_UPLS.dir/serialport.cpp.o
src/lib_UPLS.a: src/CMakeFiles/lib_UPLS.dir/upls_controller.cpp.o
src/lib_UPLS.a: src/CMakeFiles/lib_UPLS.dir/build.make
src/lib_UPLS.a: src/CMakeFiles/lib_UPLS.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library lib_UPLS.a"
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && $(CMAKE_COMMAND) -P CMakeFiles/lib_UPLS.dir/cmake_clean_target.cmake
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lib_UPLS.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/lib_UPLS.dir/build: src/lib_UPLS.a

.PHONY : src/CMakeFiles/lib_UPLS.dir/build

src/CMakeFiles/lib_UPLS.dir/clean:
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src && $(CMAKE_COMMAND) -P CMakeFiles/lib_UPLS.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/lib_UPLS.dir/clean

src/CMakeFiles/lib_UPLS.dir/depend:
	cd /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/lukas/Data/IONX/Software/UPLS/UPLS_Py /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/src /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src /media/lukas/Data/IONX/Software/UPLS/UPLS_Py/build/src/CMakeFiles/lib_UPLS.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/lib_UPLS.dir/depend

