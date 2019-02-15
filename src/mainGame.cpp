#include "mainGame.hpp"


namespace stickman
{
	mainGame::mainGame(GameDataRef data) : _data(data)
	{

	}

	void mainGame::Init()
	{
		//creating ground
		Game gameState(this->_data);
    	gameState.ground = gameState.createGround(b2Vec2(683.f/SCALE, 70.f/SCALE),0);
    	gameState.wall1 = gameState.createGround(b2Vec2(683.f/SCALE, 698.f/SCALE),0);
    	gameState.wall2 = gameState.createGround(b2Vec2(71.f/SCALE, 384.f/SCALE),90);
    	gameState.wall3 = gameState.createGround(b2Vec2(1295.f/SCALE, 384.f/SCALE),90);
    	gameState.gameLoop();
	}

	void mainGame::HandleInput()
	{
		
	}

	void mainGame::Update(float dt)
	{
        
	}

	void mainGame::Draw(float dt)
	{
		
	}
}