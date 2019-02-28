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
    	gameState.connect();
    	while(gameState.player1Rounds <= 2 && gameState.player2Rounds <= 2 && !gameState.isExiting)
    	{
    		gameState.gameLoop();
    	}
    	if(!gameState.isExiting)
    	{
            gameState.tcplistener.close();
            gameState.tcplistener1.close();
            gameState.sendSocket.disconnect();
            gameState.listenSocket.disconnect();
            gameState.isExiting = true;
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