#include "Game.hpp"
#include <gtest/gtest.h>
//#include "tests.hpp"
#include "DEFINITIONS.hpp"

int main(int argc,char **argv)
{
	//testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
    
	stickman::Game2(SCREEN_WIDTH, SCREEN_HEIGHT, "Stickman Fighter");

	return EXIT_SUCCESS;
}