# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_SOURCE_DIR = /home/ajinkya/Desktop/concurrency

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ajinkya/Desktop/concurrency

# Include any dependencies generated for this target.
include CMakeFiles/stickman.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/stickman.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/stickman.dir/flags.make

CMakeFiles/stickman.dir/main.cpp.o: CMakeFiles/stickman.dir/flags.make
CMakeFiles/stickman.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajinkya/Desktop/concurrency/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/stickman.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stickman.dir/main.cpp.o -c /home/ajinkya/Desktop/concurrency/main.cpp

CMakeFiles/stickman.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stickman.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ajinkya/Desktop/concurrency/main.cpp > CMakeFiles/stickman.dir/main.cpp.i

CMakeFiles/stickman.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stickman.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ajinkya/Desktop/concurrency/main.cpp -o CMakeFiles/stickman.dir/main.cpp.s

CMakeFiles/stickman.dir/src/game.cpp.o: CMakeFiles/stickman.dir/flags.make
CMakeFiles/stickman.dir/src/game.cpp.o: src/game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajinkya/Desktop/concurrency/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/stickman.dir/src/game.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stickman.dir/src/game.cpp.o -c /home/ajinkya/Desktop/concurrency/src/game.cpp

CMakeFiles/stickman.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stickman.dir/src/game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ajinkya/Desktop/concurrency/src/game.cpp > CMakeFiles/stickman.dir/src/game.cpp.i

CMakeFiles/stickman.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stickman.dir/src/game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ajinkya/Desktop/concurrency/src/game.cpp -o CMakeFiles/stickman.dir/src/game.cpp.s

CMakeFiles/stickman.dir/src/player.cpp.o: CMakeFiles/stickman.dir/flags.make
CMakeFiles/stickman.dir/src/player.cpp.o: src/player.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ajinkya/Desktop/concurrency/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/stickman.dir/src/player.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/stickman.dir/src/player.cpp.o -c /home/ajinkya/Desktop/concurrency/src/player.cpp

CMakeFiles/stickman.dir/src/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/stickman.dir/src/player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ajinkya/Desktop/concurrency/src/player.cpp > CMakeFiles/stickman.dir/src/player.cpp.i

CMakeFiles/stickman.dir/src/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/stickman.dir/src/player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ajinkya/Desktop/concurrency/src/player.cpp -o CMakeFiles/stickman.dir/src/player.cpp.s

# Object files for target stickman
stickman_OBJECTS = \
"CMakeFiles/stickman.dir/main.cpp.o" \
"CMakeFiles/stickman.dir/src/game.cpp.o" \
"CMakeFiles/stickman.dir/src/player.cpp.o"

# External object files for target stickman
stickman_EXTERNAL_OBJECTS =

stickman: CMakeFiles/stickman.dir/main.cpp.o
stickman: CMakeFiles/stickman.dir/src/game.cpp.o
stickman: CMakeFiles/stickman.dir/src/player.cpp.o
stickman: CMakeFiles/stickman.dir/build.make
stickman: CMakeFiles/stickman.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ajinkya/Desktop/concurrency/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable stickman"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/stickman.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/stickman.dir/build: stickman

.PHONY : CMakeFiles/stickman.dir/build

CMakeFiles/stickman.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/stickman.dir/cmake_clean.cmake
.PHONY : CMakeFiles/stickman.dir/clean

CMakeFiles/stickman.dir/depend:
	cd /home/ajinkya/Desktop/concurrency && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ajinkya/Desktop/concurrency /home/ajinkya/Desktop/concurrency /home/ajinkya/Desktop/concurrency /home/ajinkya/Desktop/concurrency /home/ajinkya/Desktop/concurrency/CMakeFiles/stickman.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/stickman.dir/depend
