cmake_minimum_required (VERSION 3.0)
project (stickman)
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
set(CMAKE_CXX_STANDARD 11)


add_subdirectory(src)

include_directories(include)

link_directories(include)

add_executable(stickman main.cpp)

target_link_libraries(stickman src
				sfml-window
        			sfml-system
        			sfml-graphics
        			sfml-audio
        			sfml-network-d
				libBox2D.a
				pthread
				)
