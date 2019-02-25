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
        this->_play_again_button.setTexture(this->_data->assets.GetTexture("Play Button"));
        this->_play_again_button.setPosition(600,400);

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
		this->_data->window.clear(sf::Color::Blue);
        this->_data->window.draw( this->gtext);
        this->_data->window.draw( this->gtext1);
        this->_data->window.draw( this->_play_again_button );
		this->_data->window.display();
	}
}