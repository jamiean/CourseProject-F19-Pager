# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /home/ziqi/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.5233.144/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/ziqi/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/193.5233.144/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/testspec.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testspec.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testspec.dir/flags.make

CMakeFiles/testspec.dir/testspec.4.cpp.o: CMakeFiles/testspec.dir/flags.make
CMakeFiles/testspec.dir/testspec.4.cpp.o: ../testspec.4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testspec.dir/testspec.4.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testspec.dir/testspec.4.cpp.o -c /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/testspec.4.cpp

CMakeFiles/testspec.dir/testspec.4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testspec.dir/testspec.4.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/testspec.4.cpp > CMakeFiles/testspec.dir/testspec.4.cpp.i

CMakeFiles/testspec.dir/testspec.4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testspec.dir/testspec.4.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/testspec.4.cpp -o CMakeFiles/testspec.dir/testspec.4.cpp.s

# Object files for target testspec
testspec_OBJECTS = \
"CMakeFiles/testspec.dir/testspec.4.cpp.o"

# External object files for target testspec
testspec_EXTERNAL_OBJECTS = \
"/home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/libvm_app.o"

testspec: CMakeFiles/testspec.dir/testspec.4.cpp.o
testspec: ../libvm_app.o
testspec: CMakeFiles/testspec.dir/build.make
testspec: CMakeFiles/testspec.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testspec"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testspec.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testspec.dir/build: testspec

.PHONY : CMakeFiles/testspec.dir/build

CMakeFiles/testspec.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testspec.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testspec.dir/clean

CMakeFiles/testspec.dir/depend:
	cd /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3 /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3 /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug/CMakeFiles/testspec.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testspec.dir/depend

