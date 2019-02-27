#include <sstream>
#include "GameOver.h"
#include "DEFINITIONS.hpp"
#include "name.h"

#include <iostream>

namespace stickman
{
	GameOver::GameOver(GameDataRef data,std::string name,int result) : _data(data)
	{
		this->name=name;
		this->result=result;
	}

	void GameOver::Init()
	{   
        this->font.loadFromFile("res/arial.ttf");
        this->_data->assets.LoadTexture("restart",Restart_FILEPATH);
        this->_play_again_button.setTexture(this->_data->assets.GetTexture("restart"));
        this->_play_again_button.setPosition(600,400);

       	this->_data->assets.LoadTexture("baloon1",SPLASH_SCENE_BALOON_FILEPATH);
        this->baloon.setTexture(this->_data->assets.GetTexture("baloon1"));
        this->baloon.setPosition(100,600);

        this->_data->assets.LoadTexture("baloon2",SPLASH_SCENE_BALOON1_FILEPATH);
        this->baloon3.setTexture(this->_data->assets.GetTexture("baloon2"));
        this->baloon3.setPosition(600,500);

        this->_data->assets.LoadTexture("baloon3",SPLASH_SCENE_BALOON_FILEPATH);
        this->baloon4.setTexture(this->_data->assets.GetTexture("baloon3"));
        this->baloon4.setPosition(900,700);

        this->_data->assets.LoadTexture("baloon4",SPLASH_SCENE_BALOON_FILEPATH);
        this->baloon2.setTexture(this->_data->assets.GetTexture("baloon4"));
        this->baloon2.setPosition(300,200);

        this->_data->assets.LoadTexture("baloon5",SPLASH_SCENE_BALOON1_FILEPATH);
        this->baloon1.setTexture(this->_data->assets.GetTexture("baloon5"));
        this->baloon1.setPosition(200,300);

        this->_data->assets.LoadTexture("baloon6",SPLASH_SCENE_BALOON1_FILEPATH);
        this->baloon5.setTexture(this->_data->assets.GetTexture("baloon6"));
        this->baloon5.setPosition(1100,400);

		this->gtext.setPosition(420,180);
		this->gtext.setCharacterSize(60);
		this->gtext.setFont(this->font);
	    this->gtext.setColor(sf::Color::White);
	    this->gtext.setString("GAME OVER!!!");

	    this->gtext1.setPosition(500,300);
		this->gtext1.setCharacterSize(60);
		this->gtext1.setFont(this->font);
	    this->gtext1.setColor(sf::Color::White);
	    if(result == 0)
	    	this->gtext1.setString("TIE");
	    else
	    	this->gtext1.setString(name+" Wins!!!");
        
	}

	void GameOver::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
            if(this->_data->input.IsSpriteClicked(_play_again_button,sf::Mouse::Left,_data->window))
            {
                this->_data->machine.AddState(StateRef(new NameState(_data)),true);
            }
		}
	}

	void GameOver::Update(float dt)
	{
        
	}

	void GameOver::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(32,32,32));

		this->_data->window.draw( this->baloon );
		this->baloon.move(0.f,-0.05);

		this->_data->window.draw( this->baloon2 );
		this->baloon2.move(0.f,-0.05);

		this->_data->window.draw( this->baloon3 );
		this->baloon3.move(0.f,-0.05);

		this->_data->window.draw( this->baloon4 );
		this->baloon4.move(0.f,-0.05);

		this->_data->window.draw( this->baloon5 );
		this->baloon5.move(0.f,-0.05);

		this->_data->window.draw( this->baloon1 );
		this->baloon1.move(0.f,-0.05);

        this->_data->window.draw( this->gtext);
        this->_data->window.draw( this->gtext1);
        this->_data->window.draw( this->_play_again_button );
        
		this->_data->window.display();
	}
}