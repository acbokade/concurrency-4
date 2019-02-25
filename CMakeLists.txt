cmake_minimum_required (VERSION 3.0)
project (stickman)
set(CMAKE_CXX_STANDARD 11)
set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

add_subdirectory(src)

include_directories(include)

link_directories(include)

add_compile_options(-fPIC)

find_package(SFML 2.5 COMPONENTS window system graphics audio network REQUIRED)

add_executable(stickman main.cpp)

target_link_libraries(stickman src
				sfml-system
				sfml-window
        		sfml-graphics
        		sfml-audio
        		sfml-network
				libBox2D.a
				pthread
				)
