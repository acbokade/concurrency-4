cmake_minimum_required (VERSION 3.0)
project (stickman)
set(CMAKE_CXX_STANDARD 11)

add_subdirectory(src)

include_directories(include ${GTEST_INCLUDE_DIRS})

link_directories(include)

add_compile_options(-fPIC)

find_package(GTest REQUIRED)

add_executable(stickman main.cpp)

target_link_libraries(stickman src
        		sfml-network
        		sfml-graphics
			sfml-window
			sfml-system
        		sfml-audio
			libBox2D.a
			pthread
			${GTEST_LIBRARIES}
				)
