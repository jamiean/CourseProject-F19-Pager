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
include CMakeFiles/testSwitch2.4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/testSwitch2.4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/testSwitch2.4.dir/flags.make

CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.o: CMakeFiles/testSwitch2.4.dir/flags.make
CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.o: ../testSwitch2.4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.o -c /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/testSwitch2.4.cpp

CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/testSwitch2.4.cpp > CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.i

CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/testSwitch2.4.cpp -o CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.s

# Object files for target testSwitch2.4
testSwitch2_4_OBJECTS = \
"CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.o"

# External object files for target testSwitch2.4
testSwitch2_4_EXTERNAL_OBJECTS = \
"/home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/libvm_app.o"

testSwitch2.4: CMakeFiles/testSwitch2.4.dir/testSwitch2.4.cpp.o
testSwitch2.4: ../libvm_app.o
testSwitch2.4: CMakeFiles/testSwitch2.4.dir/build.make
testSwitch2.4: CMakeFiles/testSwitch2.4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable testSwitch2.4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/testSwitch2.4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/testSwitch2.4.dir/build: testSwitch2.4

.PHONY : CMakeFiles/testSwitch2.4.dir/build

CMakeFiles/testSwitch2.4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/testSwitch2.4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/testSwitch2.4.dir/clean

CMakeFiles/testSwitch2.4.dir/depend:
	cd /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3 /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3 /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug /home/ziqi/code/eecs_482/jamiean.jasonxu.ziqizh.3/cmake-build-debug/CMakeFiles/testSwitch2.4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/testSwitch2.4.dir/depend

