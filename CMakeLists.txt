cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 11)

project(stickman)

include_directories(include)

link_directories(linker)

set(SOURCE_FILES
	main.cpp
	include/game.h src/game.cpp
	include/player.h src/player.cpp
	)

add_executable(
	stickman ${SOURCE_FILES}
)

target_link_libraries(stickman
        sfml-window
        sfml-system
        sfml-graphics
        sfml-audio
        sfml-network
        libBox2D.a)
