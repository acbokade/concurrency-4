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
    	while(!gameState.isExiting)
    	{
			gameState.gameLoop();
    	}
        this->_data->machine.AddState(StateRef(new GameOver(_data,gameState.player1->name,0)), true);


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