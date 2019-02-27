#ifndef tem_h
#define temp_h
#include "game.h"
#include <gtest/gtest.h>
#include <gtest/gtest.h>
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "player.h"
#include "myListener.h"
#include "SFML/Network.hpp"
#include <queue>
#include <time.h>
#include <sys/time.h>
#include <thread>
#include <queue>
#include <mutex>
#include "State.hpp"
#include "Game.hpp"
#include <utility>
#include <bits/stdc++.h>

namespace stickman{

/**
 * @brief      A struct passed for testing
 */
struct mainGame : testing::Test
{
	GameDataRef *data;
	Game *temp;
	std::string t1="a";
	bool t2=true;

	/**
	 * @brief      Constructor of struct
	 */
	mainGame()
	{
		data=new GameDataRef;
		temp=new Game(*data,t1,t2,t1);
	}
	/**
	 * @brief      Destroys the object.
	 */
	~mainGame()
	{
		delete data;
		delete temp;
	}
};

/**
 * Runs the test initializeData
 */
TEST_F(mainGame,initializeData)
{
	int success=0;
	if(temp->player1!=NULL)success=1;
	EXPECT_EQ(1,success);
	if(temp->player2==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->window==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->world==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->listener==NULL)success=0;
	EXPECT_EQ(1,success);
	sf::Vector2f a(620.f, 8.f);
	EXPECT_EQ(a,temp->groundSprite.getOrigin());
}

/**
 * @brief      Struct for testing player data
 */
struct playerdata
{
	int phealth1=100;
	int phealth2=100;
	int a,b;
	std::string t1="a";
	bool t2=true;
	GameDataRef *data;
	Game *temp;
	playerdata()
	{
		data=new GameDataRef;
		temp=new Game(*data,t1,t2,t1);
	}
	playerdata(int a1,int a2,int a3,int a4)
	{
		data=new GameDataRef;
		temp=new Game(*data,t1,t2,t1);
		phealth1=a1;
		phealth2=a2;
		a=a3;
		b=a4;

	}
	~playerdata()
	{
		
	}
};
/**
 * @brief      This will be passed to the test as we want an interface to the previous struct
 */
struct testDecreaseHp : mainGame,testing::WithParamInterface<playerdata>
{

};

/**
 * Performs a test with multiple inputs to check different test cases
 */
TEST_P(testDecreaseHp,decreaseHp)
{
	playerdata pdata=GetParam();
	pdata.temp->player1->setHealth(100);
	pdata.temp->player2->setHealth(100);
	int damage1=0,damage2=0;
	if( (pdata.a==1 && pdata.b==5) || (pdata.a==5 && pdata.b==1) )
	{
		damage1=5;
		damage2=5;
	}
	else if( (pdata.a==1 && pdata.b==7) || (pdata.a==7 && pdata.b==1) )
	{
		damage1=5;
	}
	else if( (pdata.a==2 && pdata.b==8) || (pdata.a==8 && pdata.b==2) )
	{
		damage1=3;
	}
	else if( (pdata.a==2 && pdata.b==7) || (pdata.a==7 && pdata.b==2) )
	{
		damage1=3;
	}
	else if( (pdata.a==3 && pdata.b==5) || (pdata.a==5 && pdata.b==3) )
	{
		damage2=5;
	}
	else if( (pdata.a==4 && pdata.b==5) || (pdata.a==5 && pdata.b==4) )
	{
		damage2=5;
	}
	else if( (pdata.a==3 && pdata.b==6) || (pdata.a==6 && pdata.b==3) )
	{
		damage2=3;
	}
	else if( (pdata.a==4 && pdata.b==6) || (pdata.a==6 && pdata.b==4) )
	{
		damage2=3;
	}
	pdata.temp->decrease_hp(pdata.a,pdata.b);
	EXPECT_EQ(pdata.phealth1-damage1,pdata.temp->player1->getHealth());
	EXPECT_EQ(pdata.phealth2-damage2,pdata.temp->player2->getHealth());
}

/**
 * Passes the test cases for the test
 */
INSTANTIATE_TEST_CASE_P(Default,testDecreaseHp,testing::Values(playerdata{100,100,1,5},playerdata{100,100,5,1},
									playerdata{100,100,4,6},playerdata{100,100,6,4},
									playerdata{100,100,6,3},playerdata{100,100,3,6},
									playerdata{100,100,4,5},playerdata{100,100,5,4},
									playerdata{100,100,3,5},playerdata{100,100,5,3},
									playerdata{100,100,2,8},playerdata{100,100,8,2},
									playerdata{100,100,7,2},playerdata{100,100,2,7},
									playerdata{100,100,1,7},playerdata{100,100,7,1}));

}


#endif