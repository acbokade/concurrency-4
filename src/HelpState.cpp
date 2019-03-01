#include <sstream>
#include "HelpState.hpp"
#include "name.h"
#include "DEFINITIONS.hpp"
#include <iostream>
#include <string>

namespace stickman
{
	HelpState::HelpState(GameDataRef data) : _data(data)
	{

	}

	void HelpState::Init()
	{ 
		this->_data->assets.LoadTexture("Back Button", BACK_BUTTON); 
        if(!this->font.loadFromFile("res/Ubuntu-R.ttf"))
			std::cerr<<"Failed to load font!"<<std::endl;
        this->backSprite.setTexture(this->_data->assets.GetTexture("Back Button"));
        this->backSprite.setPosition(50,50);
        this->infoText.setPosition(50,200);
		this->infoText.setCharacterSize(25);
		this->infoText.setFont(this->font);
	    this->infoText.setColor(sf::Color::Red);
        string s = string("This is a multiplayer addictive fighting game.\n\nYou can move player up, down, right, left using Up, Down, Right, Left arrow keys\nrespectively.\n")+
	    string("You can rotate player clockwise using \"D\" key and anticlockwise using \"A\" key.\n\nGame will finish when either one of them wins 2 rounds and he will be the winner.\nInitial health of each player is 100.")+
	    string(" One whose health becomes 0 first will lose the round\nand other wins that round. If it happens simultaneously, it will result in tie.")+
	    string("\n\nDamage due to collision of head of First Player and head of Second")+
	    string(" Player is 5 to each.\nDamage due to collision of head of First Player")+
	    string(" and hands or legs of Second Player is 5 to\nFirst Player and vice versa.\nDamage due to collision of body of First Player and hands or legs of Second Player ")+
	    string("is 3 to\nFirst Player and vice versa.\n\n A gem appears after every 5 seconds at random location.\n If a player's head overlaps with the gem,")+
	    string("then its health points get increased by 5 points.");
	    this->infoText.setString(s);
	}

	void HelpState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
            if(this->_data->input.IsSpriteClicked(backSprite,sf::Mouse::Left,_data->window))
            {
                this->_data->machine.AddState(StateRef(new NameState(_data)),true);
            }
		}
	}

	void HelpState::Update(float dt)
	{
        
	}

	void HelpState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color(0,153,255));
		this->_data->window.draw(backSprite);
        this->_data->window.draw(this->infoText);
        this->_data->window.draw(this->rulesText);
        this->_data->window.draw(this->rule1Text);
        this->_data->window.draw(this->rule2Text);
        this->_data->window.draw(this->rule3Text);
		this->_data->window.display();
	}
}