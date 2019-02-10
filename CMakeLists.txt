cmake_minimum_required (VERSION 3.0)
project (stickman)
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
set(SFML_DIR "SFML/lib/cmake/SFML")


add_subdirectory(Libraries)

include_directories(headers)

link_directories(headers)

find_package(SFML 2.5 COMPONENTS window system graphics audio network REQUIRED)

add_executable(stickman main.cpp)

target_link_libraries(stickman Libraries
				sfml-window
        			sfml-system
        			sfml-graphics
        			sfml-audio
        			sfml-network
				libBox2D.a
				)
