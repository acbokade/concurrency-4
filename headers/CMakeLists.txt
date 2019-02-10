cmake_minimum_required (VERSION 3.0)
project (stickman)
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

add_subdirectory(Libraries
		headers)

add_executable(stickman main.cpp)
target_link_libraries(stickman Libraries
				sfml-window
        			sfml-system
        			sfml-graphics
        			sfml-audio
        			sfml-network)
