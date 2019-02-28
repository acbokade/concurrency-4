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
 * @brief      A struct passed for testing game functions
 */
struct mainGamel : testing::Test
{
	GameDataRef *data;
	Game *temp;
	std::string t1="a";
	bool t2=true;

	/**
	 * @brief      Constructor of struct
	 */
	mainGamel()
	{
		data=new GameDataRef;
		temp=new Game(*data,t1,t2,t1);
	}
	/**
	 * @brief      Destroys the object.
	 */
	virtual ~mainGamel()
	{
		delete data;
		delete temp;
	}
};

/**
 * Runs the test initializeData
 */
TEST_F(mainGamel,initializeData)
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
	if(temp->ground==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->wall1==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->wall2==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->wall3==NULL)success=0;
	EXPECT_EQ(1,success);
	sf::Vector2f a(620.f, 8.f);
	EXPECT_EQ(a,temp->groundSprite.getOrigin());
}

/**
 * Runs the test for the function initPlayer
 */
TEST_F(mainGamel,initPlayerTest)
{
	int success=0;
	temp->initPlayer(temp->player1,100.f,2);
	if(temp->player1->head!=NULL)success=1;
	EXPECT_EQ(1,success);
	if(temp->player1->body==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->player1->left_hand==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->player1->right_hand==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->player1->left_leg==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->player1->right_leg==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->player1->headJoint==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->player1->left_legJoint==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->player1->right_legJoint==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->player1->left_handJoint==NULL)success=0;
	EXPECT_EQ(1,success);
	if(temp->player1->right_handJoint==NULL)success=0;
	EXPECT_EQ(1,success);
	
}


struct testNameString
{
	std::string something;
};

struct setNameTestStruct:mainGamel,testing::WithParamInterface<testNameString>
{

};
/**
 * Runs the test for the setter function of health
 */
TEST_F(mainGamel,setHealthTest)
{
	for (int i = 1; i < 100; ++i)
	{
		temp->player1->setHealth(i);
		EXPECT_EQ(temp->player1->health,temp->player1->getHealth());
	}
	
}

/**
 * Runs the test for the setter function of name
 */
TEST_P(setNameTestStruct,setNameTest)
{
	auto as =GetParam();
	temp->player1->setName(as.something);
	EXPECT_EQ(temp->player1->name,temp->player1->getName());
}

INSTANTIATE_TEST_CASE_P(Default,setNameTestStruct,testing::Values(testNameString{"TestString1"},testNameString{"ksahdhksda"},testNameString{"okufahsidha"},testNameString{"gowqiyfjalUHUKJHd"},testNameString{"fksaiodhusnl"},testNameString{"KHKgYGYgHG"},testNameString{"uhfuhJHKUHguiGUg"}));

/**
 * test for generate gem function
 */
TEST_F(mainGamel,generateGem)
{
	temp->isPlaying=true;
	// temp->generateGem();
	// sf::Vector2f a(temp->gemSprite.getPosition());
	// EXPECT_LE(650.f,a.x);
	// EXPECT_LE(1200.f,a.y);
}

/**
 * Test for the distance function
 */
TEST_F(mainGamel,checkDistance)
{
	int x1=0,x2=0,y1=0,y2=0;
	for (int i = 0; i < 10; ++i)
	for (int j = 0; j < 10; ++j)
	for(int k=0;k<10;k++)
	for(int l=0;l<10;l++)
	{
		float tmp=temp->distance(i,k,j,l);
		float tmp2;
		if((j-i)>50)tmp2=51;
		else if((l-k)>50)tmp2=51;
		else tmp2=sqrt((j-i)*(j-i)+(l-k)*(l-k));
		EXPECT_EQ(tmp2,tmp);
	}
}

/**
 * @brief      An empty struct to derive from
 */
struct emptyStr : testing::Test
{

};
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
	playerdata(int a1,int a2,int a3,int a4)
	{
		data=new GameDataRef;
		temp=new Game(*data,t1,t2,t1);
		phealth1=a1;
		phealth2=a2;
		a=a3;
		b=a4;

	}
	virtual ~playerdata()
	{
		
	}
};
/**
 * @brief      This will be passed to the test as we want an interface to the previous struct
 */
struct testDecreaseHp : emptyStr,testing::WithParamInterface<playerdata>
{
	
};

/**
 * Performs a test with multiple inputs to check different test cases
 */
TEST_P(testDecreaseHp,decreaseHp)
{
	playerdata pdata=GetParam();
	pdata.temp->player1->setHealth(pdata.phealth1);
	pdata.temp->player2->setHealth(pdata.phealth2);
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
									playerdata{100,100,1,7},playerdata{100,100,7,1},
									playerdata{80,100,4,6},playerdata{100,80,6,4},
									playerdata{100,60,4,6},playerdata{60,100,6,4},
									playerdata{100,40,4,6},playerdata{40,100,6,4},
									playerdata{100,20,4,6},playerdata{20,100,6,4},
									playerdata{100,10,4,6},playerdata{10,100,6,4},
									playerdata{80,80,4,6},playerdata{80,80,6,4},
									playerdata{80,60,4,6},playerdata{60,80,6,4},
									playerdata{80,40,4,6},playerdata{40,80,6,4},
									playerdata{80,20,4,6},playerdata{20,80,6,4},
									playerdata{80,10,4,6},playerdata{10,80,6,4},
									playerdata{60,80,4,6},playerdata{80,60,6,4},
									playerdata{60,60,4,6},playerdata{60,60,6,4},
									playerdata{60,40,4,6},playerdata{40,60,6,4},
									playerdata{60,20,4,6},playerdata{20,60,6,4},
									playerdata{60,10,4,6},playerdata{10,60,6,4},
									playerdata{40,80,4,6},playerdata{80,40,6,4},
									playerdata{40,60,4,6},playerdata{60,40,6,4}/*,
									playerdata{40,40,4,6},playerdata{40,40,6,4},
									playerdata{40,20,4,6},playerdata{20,40,6,4},
									playerdata{40,10,4,6},playerdata{10,40,6,4},
									playerdata{20,80,4,6},playerdata{80,20,6,4},
									playerdata{20,60,4,6},playerdata{60,20,6,4},
									playerdata{20,40,4,6},playerdata{40,20,6,4},
									playerdata{20,20,4,6},playerdata{20,20,6,4},
									playerdata{20,10,4,6},playerdata{10,20,6,4},
									playerdata{10,80,4,6},playerdata{80,10,6,4},
									playerdata{10,60,4,6},playerdata{60,10,6,4},
									playerdata{10,40,4,6},playerdata{40,10,6,4},
									playerdata{10,20,4,6},playerdata{20,10,6,4},
									playerdata{10,10,4,6},playerdata{10,10,6,4},
									playerdata{80,100,6,3},playerdata{100,80,3,6},
									playerdata{100,60,6,3},playerdata{60,100,3,6},
									playerdata{100,40,6,3},playerdata{40,100,3,6},
									playerdata{100,20,6,3},playerdata{20,100,3,6},
									playerdata{100,10,6,3},playerdata{10,100,3,6},
									playerdata{80,80,6,3},playerdata{80,80,3,6},
									playerdata{80,60,6,3},playerdata{60,80,3,6},
									playerdata{80,40,6,3},playerdata{40,80,3,6},
									playerdata{80,20,6,3},playerdata{20,80,3,6},
									playerdata{80,10,6,3},playerdata{10,80,3,6},
									playerdata{60,80,6,3},playerdata{80,60,3,6},
									playerdata{60,60,6,3},playerdata{60,60,3,6},
									playerdata{60,40,6,3},playerdata{40,60,3,6},
									playerdata{60,20,6,3},playerdata{20,60,3,6},
									playerdata{60,10,6,3},playerdata{10,60,3,6},
									playerdata{40,80,6,3},playerdata{80,40,3,6},
									playerdata{40,60,6,3},playerdata{60,40,3,6},
									playerdata{40,40,6,3},playerdata{40,40,3,6},
									playerdata{40,20,6,3},playerdata{20,40,3,6},
									playerdata{40,10,6,3},playerdata{10,40,3,6},
									playerdata{20,80,6,3},playerdata{80,20,3,6},
									playerdata{20,60,6,3},playerdata{60,20,3,6},
									playerdata{20,40,6,3},playerdata{40,20,3,6},
									playerdata{20,20,6,3},playerdata{20,20,3,6},
									playerdata{20,10,6,3},playerdata{10,20,3,6},
									playerdata{10,80,6,3},playerdata{80,10,3,6},
									playerdata{10,60,6,3},playerdata{60,10,3,6},
									playerdata{10,40,6,3},playerdata{40,10,3,6},
									playerdata{10,20,6,3},playerdata{20,10,3,6},
									playerdata{10,10,6,3},playerdata{10,10,3,6},
									playerdata{80,100,4,5},playerdata{100,80,5,4},
									playerdata{100,60,4,5},playerdata{60,100,5,4},
									playerdata{100,40,4,5},playerdata{40,100,5,4},
									playerdata{100,20,4,5},playerdata{20,100,5,4},
									playerdata{100,10,4,5},playerdata{10,100,5,4},
									playerdata{80,80,4,5},playerdata{80,80,5,4},
									playerdata{80,60,4,5},playerdata{60,80,5,4},
									playerdata{80,40,4,5},playerdata{40,80,5,4},
									playerdata{80,20,4,5},playerdata{20,80,5,4},
									playerdata{80,10,4,5},playerdata{10,80,5,4},
									playerdata{60,80,4,5},playerdata{80,60,5,4},
									playerdata{60,60,4,5},playerdata{60,60,5,4},
									playerdata{60,40,4,5},playerdata{40,60,5,4},
									playerdata{60,20,4,5},playerdata{20,60,5,4},
									playerdata{60,10,4,5},playerdata{10,60,5,4},
									playerdata{40,80,4,5},playerdata{80,40,5,4},
									playerdata{40,60,4,5},playerdata{60,40,5,4},
									playerdata{40,40,4,5},playerdata{40,40,5,4},
									playerdata{40,20,4,5},playerdata{20,40,5,4},
									playerdata{40,10,4,5},playerdata{10,40,5,4},
									playerdata{20,80,4,5},playerdata{80,20,5,4},
									playerdata{20,60,4,5},playerdata{60,20,5,4},
									playerdata{20,40,4,5},playerdata{40,20,5,4},
									playerdata{20,20,4,5},playerdata{20,20,5,4},
									playerdata{20,10,4,5},playerdata{10,20,5,4},
									playerdata{10,80,4,5},playerdata{80,10,5,4},
									playerdata{10,60,4,5},playerdata{60,10,5,4},
									playerdata{10,40,4,5},playerdata{40,10,5,4},
									playerdata{10,20,4,5},playerdata{20,10,5,4},
									playerdata{10,10,4,5},playerdata{10,10,5,4},
									playerdata{80,100,1,5},playerdata{100,80,5,1},
									playerdata{100,60,1,5},playerdata{60,100,5,1},
									playerdata{100,40,1,5},playerdata{40,100,5,1},
									playerdata{100,20,1,5},playerdata{20,100,5,1},
									playerdata{100,10,1,5},playerdata{10,100,5,1},
									playerdata{80,80,1,5},playerdata{80,80,5,1},
									playerdata{80,60,1,5},playerdata{60,80,5,1},
									playerdata{80,40,1,5},playerdata{40,80,5,1},
									playerdata{80,20,1,5},playerdata{20,80,5,1},
									playerdata{80,10,1,5},playerdata{10,80,5,1},
									playerdata{60,80,1,5},playerdata{80,60,5,1},
									playerdata{60,60,1,5},playerdata{60,60,5,1},
									playerdata{60,40,1,5},playerdata{40,60,5,1},
									playerdata{60,20,1,5},playerdata{20,60,5,1},
									playerdata{60,10,1,5},playerdata{10,60,5,1},
									playerdata{40,80,1,5},playerdata{80,40,5,1},
									playerdata{40,60,1,5},playerdata{60,40,5,1},
									playerdata{40,40,1,5},playerdata{40,40,5,1},
									playerdata{40,20,1,5},playerdata{20,40,5,1},
									playerdata{40,10,1,5},playerdata{10,40,5,1},
									playerdata{20,80,1,5},playerdata{80,20,5,1},
									playerdata{20,60,1,5},playerdata{60,20,5,1},
									playerdata{20,40,1,5},playerdata{40,20,5,1},
									playerdata{20,20,1,5},playerdata{20,20,5,1},
									playerdata{20,10,1,5},playerdata{10,20,5,1},
									playerdata{10,80,1,5},playerdata{80,10,5,1},
									playerdata{10,60,1,5},playerdata{60,10,5,1},
									playerdata{10,40,1,5},playerdata{40,10,5,1},
									playerdata{10,20,1,5},playerdata{20,10,5,1},
									playerdata{10,10,1,5},playerdata{10,10,5,1},
									playerdata{80,100,3,5},playerdata{100,80,5,3},
									playerdata{100,60,3,5},playerdata{60,100,5,3},
									playerdata{100,40,3,5},playerdata{40,100,5,3},
									playerdata{100,20,3,5},playerdata{20,100,5,3},
									playerdata{100,10,3,5},playerdata{10,100,5,3},
									playerdata{80,80,3,5},playerdata{80,80,5,3},
									playerdata{80,60,3,5},playerdata{60,80,5,3},
									playerdata{80,40,3,5},playerdata{40,80,5,3},
									playerdata{80,20,3,5},playerdata{20,80,5,3},
									playerdata{80,10,3,5},playerdata{10,80,5,3},
									playerdata{60,80,3,5},playerdata{80,60,5,3},
									playerdata{60,60,3,5},playerdata{60,60,5,3},
									playerdata{60,40,3,5},playerdata{40,60,5,3},
									playerdata{60,20,3,5},playerdata{20,60,5,3},
									playerdata{60,10,3,5},playerdata{10,60,5,3},
									playerdata{40,80,3,5},playerdata{80,40,5,3},
									playerdata{40,60,3,5},playerdata{60,40,5,3},
									playerdata{40,40,3,5},playerdata{40,40,5,3},
									playerdata{40,20,3,5},playerdata{20,40,5,3},
									playerdata{40,10,3,5},playerdata{10,40,5,3},
									playerdata{20,80,3,5},playerdata{80,20,5,3},
									playerdata{20,60,3,5},playerdata{60,20,5,3},
									playerdata{20,40,3,5},playerdata{40,20,5,3},
									playerdata{20,20,3,5},playerdata{20,20,5,3},
									playerdata{20,10,3,5},playerdata{10,20,5,3},
									playerdata{10,80,3,5},playerdata{80,10,5,3},
									playerdata{10,60,3,5},playerdata{60,10,5,3},
									playerdata{10,40,3,5},playerdata{40,10,5,3},
									playerdata{10,20,3,5},playerdata{20,10,5,3},
									playerdata{10,10,3,5},playerdata{10,10,5,3},
									playerdata{80,100,2,8},playerdata{100,80,8,2},
									playerdata{100,60,2,8},playerdata{60,100,8,2},
									playerdata{100,40,2,8},playerdata{40,100,8,2},
									playerdata{100,20,2,8},playerdata{20,100,8,2},
									playerdata{100,10,2,8},playerdata{10,100,8,2},
									playerdata{80,80,2,8},playerdata{80,80,8,2},
									playerdata{80,60,2,8},playerdata{60,80,8,2},
									playerdata{80,40,2,8},playerdata{40,80,8,2},
									playerdata{80,20,2,8},playerdata{20,80,8,2},
									playerdata{80,10,2,8},playerdata{10,80,8,2},
									playerdata{60,80,2,8},playerdata{80,60,8,2},
									playerdata{60,60,2,8},playerdata{60,60,8,2},
									playerdata{60,40,2,8},playerdata{40,60,8,2},
									playerdata{60,20,2,8},playerdata{20,60,8,2},
									playerdata{60,10,2,8},playerdata{10,60,8,2},
									playerdata{40,80,2,8},playerdata{80,40,8,2},
									playerdata{40,60,2,8},playerdata{60,40,8,2},
									playerdata{40,40,2,8},playerdata{40,40,8,2},
									playerdata{40,20,2,8},playerdata{20,40,8,2},
									playerdata{40,10,2,8},playerdata{10,40,8,2},
									playerdata{20,80,2,8},playerdata{80,20,8,2},
									playerdata{20,60,2,8},playerdata{60,20,8,2},
									playerdata{20,40,2,8},playerdata{40,20,8,2},
									playerdata{20,20,2,8},playerdata{20,20,8,2},
									playerdata{20,10,2,8},playerdata{10,20,8,2},
									playerdata{10,80,2,8},playerdata{80,10,8,2},
									playerdata{10,60,2,8},playerdata{60,10,8,2},
									playerdata{10,40,2,8},playerdata{40,10,8,2},
									playerdata{10,20,2,8},playerdata{20,10,8,2},
									playerdata{10,10,2,8},playerdata{10,10,8,2},
									playerdata{80,100,7,2},playerdata{100,80,2,7},
									playerdata{100,60,7,2},playerdata{60,100,2,7},
									playerdata{100,40,7,2},playerdata{40,100,2,7},
									playerdata{100,20,7,2},playerdata{20,100,2,7},
									playerdata{100,10,7,2},playerdata{10,100,2,7},
									playerdata{80,80,7,2},playerdata{80,80,2,7},
									playerdata{80,60,7,2},playerdata{60,80,2,7},
									playerdata{80,40,7,2},playerdata{40,80,2,7},
									playerdata{80,20,7,2},playerdata{20,80,2,7},
									playerdata{80,10,7,2},playerdata{10,80,2,7},
									playerdata{60,80,7,2},playerdata{80,60,2,7},
									playerdata{60,60,7,2},playerdata{60,60,2,7},
									playerdata{60,40,7,2},playerdata{40,60,2,7},
									playerdata{60,20,7,2},playerdata{20,60,2,7},
									playerdata{60,10,7,2},playerdata{10,60,2,7},
									playerdata{40,80,7,2},playerdata{80,40,2,7},
									playerdata{40,60,7,2},playerdata{60,40,2,7},
									playerdata{40,40,7,2},playerdata{40,40,2,7},
									playerdata{40,20,7,2},playerdata{20,40,2,7},
									playerdata{40,10,7,2},playerdata{10,40,2,7},
									playerdata{20,80,7,2},playerdata{80,20,2,7},
									playerdata{20,60,7,2},playerdata{60,20,2,7},
									playerdata{20,40,7,2},playerdata{40,20,2,7},
									playerdata{20,20,7,2},playerdata{20,20,2,7},
									playerdata{20,10,7,2},playerdata{10,20,2,7},
									playerdata{10,80,7,2},playerdata{80,10,2,7},
									playerdata{10,60,7,2},playerdata{60,10,2,7},
									playerdata{10,40,7,2},playerdata{40,10,2,7},
									playerdata{10,20,7,2},playerdata{20,10,2,7},
									playerdata{10,10,7,2},playerdata{10,10,2,7},
									playerdata{80,100,7,1},playerdata{100,80,1,7},
									playerdata{100,60,7,1},playerdata{60,100,1,7},
									playerdata{100,40,7,1},playerdata{40,100,1,7},
									playerdata{100,20,7,1},playerdata{20,100,1,7},
									playerdata{100,10,7,1},playerdata{10,100,1,7},
									playerdata{80,80,7,1},playerdata{80,80,1,7},
									playerdata{80,60,7,1},playerdata{60,80,1,7},
									playerdata{80,40,7,1},playerdata{40,80,1,7},
									playerdata{80,20,7,1},playerdata{20,80,1,7},
									playerdata{80,10,7,1},playerdata{10,80,1,7},
									playerdata{60,80,7,1},playerdata{80,60,1,7},
									playerdata{60,60,7,1},playerdata{60,60,1,7},
									playerdata{60,40,7,1},playerdata{40,60,1,7},
									playerdata{60,20,7,1},playerdata{20,60,1,7},
									playerdata{60,10,7,1},playerdata{10,60,1,7},
									playerdata{40,80,7,1},playerdata{80,40,1,7},
									playerdata{40,60,7,1},playerdata{60,40,1,7},
									playerdata{40,40,7,1},playerdata{40,40,1,7},
									playerdata{40,20,7,1},playerdata{20,40,1,7},
									playerdata{40,10,7,1},playerdata{10,40,1,7},
									playerdata{20,80,7,1},playerdata{80,20,1,7},
									playerdata{20,60,7,1},playerdata{60,20,1,7},
									playerdata{20,40,7,1},playerdata{40,20,1,7},
									playerdata{20,20,7,1},playerdata{20,20,1,7},
									playerdata{20,10,7,1},playerdata{10,20,1,7},
									playerdata{10,80,7,1},playerdata{80,10,1,7},
									playerdata{10,60,7,1},playerdata{60,10,1,7},
									playerdata{10,40,7,1},playerdata{40,10,1,7},
									playerdata{10,20,7,1},playerdata{20,10,1,7},
									playerdata{10,10,7,1},playerdata{10,10,1,7}*/));

}


#endif