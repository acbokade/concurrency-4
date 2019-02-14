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
    	gameState.ground = gameState.createGround(b2Vec2(400.f/SCALE, 550.f/SCALE));
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