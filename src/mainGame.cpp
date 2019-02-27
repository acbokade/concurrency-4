#include "mainGame.hpp"


namespace stickman
{
	mainGame::mainGame(GameDataRef data,string s,bool client,string ip) : _data(data)
	{
		this->s=s;
		this->client=client;
		this->ip=ip;
	}

	void mainGame::Init()
	{
		//creating ground
		Game gameState(this->_data,s,client,ip);
    	gameState.ground = gameState.createGround(b2Vec2(683.f/SCALE, 70.f/SCALE),0);
    	gameState.wall1 = gameState.createGround(b2Vec2(683.f/SCALE, 698.f/SCALE),0);
    	gameState.wall2 = gameState.createGround(b2Vec2(71.f/SCALE, 384.f/SCALE),90);
    	gameState.wall3 = gameState.createGround(b2Vec2(1295.f/SCALE, 384.f/SCALE),90);
    	gameState.connect();
    	while(gameState.player1Rounds <= 2 && gameState.player2Rounds <= 2 && !gameState.isExiting)
    	{
    		gameState.gameLoop();
    	}
    	if(!gameState.isExiting)
    	{
            if(gameState.player1Rounds == 3 && gameState.player2Rounds < 3)
            {
                this->_data->machine.AddState(StateRef(new GameOver(_data,gameState.player1->name,1)), true);
            }
            else if(gameState.player1Rounds < 3 && gameState.player2Rounds == 3)
            {
                this->_data->machine.AddState(StateRef(new GameOver(_data,gameState.player2->name,1)), true);
            }
            else
            {
                this->_data->machine.AddState(StateRef(new GameOver(_data,"noname",0)), true); 
            }
    	}

    	//gameState.socket.disconnect();
    	//gameState.tcplistener.close();
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