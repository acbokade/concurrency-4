cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)

project(sample)

include_directories(Box2D)

link_directories(Box2D/Build/bin/x86_64/Debug)

set(SOURCE_FILES check1.cpp)

add_executable(
	sample
	${SOURCE_FILES}
)

target_link_libraries(sample
        sfml-window
        sfml-system
        sfml-graphics
        sfml-audio
        sfml-network
        libBox2D.a)