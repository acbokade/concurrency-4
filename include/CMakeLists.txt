cmake_minimum_required (VERSION 3.0)
project (stickman)

add_subdirectory(src
		include)

add_executable(stickman main.cpp)
target_link_libraries(stickman src
					sfml-window
        			sfml-system
        			sfml-graphics
        			sfml-audio
        			sfml-network)
