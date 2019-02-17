#include <sstream>
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace stickman
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
        this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON_1_FILEPATH);
        
		this->_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"),true);
        this->_title.setTexture(this->_data->assets.GetTexture("Game Title"));
        this->_title.setPosition((SCREEN_WIDTH/2)-(_title.getGlobalBounds().width/2),_title.getGlobalBounds().height/4);
        for(size_t i = 0; i < 3; i++)
        {
            this->_play_button[i].setTexture(this->_data->assets.GetTexture("Play Button"));
            this->_play_button[i].setPosition(_play_button[i].getGlobalBounds().width/2,(_title.getGlobalBounds().height+(i*_title.getGlobalBounds().height)));
        }
        
	}

	void MainMenuState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
            for(size_t i = 0; i < 3; i++)
            {
                if(this->_data->input.IsSpriteClicked(_play_button[i],sf::Mouse::Left,_data->window))
                    {
                        this->_data->machine.AddState(StateRef(new mainGame(_data)), true);
                    }
            }
            
		}
	}

	void MainMenuState::Update(float dt)
	{
        
	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Black);

		this->_data->window.draw( this->_background );
        this->_data->window.draw( this->_title );
        for(size_t i = 0; i < 3; i++)
        {
            this->_data->window.draw( this->_play_button[i] );
        }

		this->_data->window.display();
	}
}