#include <sstream>
#include "name.h"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"

#include <iostream>
namespace stickman
{
	NameState::NameState(GameDataRef data) : _data(data)
	{

	}

	void NameState::Init()
	{
		this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
        this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON_1_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"),true);
        this->_title.setTexture(this->_data->assets.GetTexture("Game Title"));
        this->_title.setPosition((SCREEN_WIDTH/2)-(_title.getGlobalBounds().width/2),_title.getGlobalBounds().height/4);
        this->_submit_button.setTexture(this->_data->assets.GetTexture("Play Button"));
        this->_submit_button.setPosition(_submit_button.getGlobalBounds().width/2,(_title.getGlobalBounds().height));
        
	}

	void NameState::HandleInput()
	{
		sf::Event event;
		playerText.setPosition(60,300);
        playerText.setColor(sf::Color::Red);
     	while(this->_data->window.pollEvent(event))
        {
        	if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
            if (event.type == sf::Event::TextEntered)
            {
	            if(event.text.unicode < 128)
	            {
	                playerInput +=event.text.unicode;
	                playerText.setString(playerInput);
	            }
            }
            if(this->_data->input.IsSpriteClicked(_submit_button,sf::Mouse::Left,_data->window))
            {
                this->_data->machine.AddState(StateRef(new MainMenuState(_data)), true);
            }
        }
	}
	void NameState::Update(float dt)
	{
        
	}
	void NameState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::White);

		this->_data->window.draw( this->_background );
        this->_data->window.draw( this->_submit_button );
        this->_data->window.draw( this->playerText);
		this->_data->window.display();
	}
}