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
		//this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
        this->_data->assets.LoadTexture("Play Button", ENTER_BUTTON_1_FILEPATH);

		//this->_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"),true);
        this->_title.setTexture(this->_data->assets.GetTexture("Game Title"));
        this->_title.setPosition((SCREEN_WIDTH/2)-(_title.getGlobalBounds().width/2),_title.getGlobalBounds().height/4);
        this->_host_button.setTexture(this->_data->assets.GetTexture("Play Button"));
        this->_host_button.setPosition(550,400);
        this->_join_button.setTexture(this->_data->assets.GetTexture("Play Button"));
        this->_join_button.setPosition(550,500);

        this->welcomeTexture.loadFromFile("res/welcome.png");
        this->welcomeSprite.setTexture(welcomeTexture);
        this->welcomeSprite.setPosition(300,50);

    	this->font.loadFromFile("res/arial.ttf");
    	this->enterName.setPosition(420,180);
		this->enterName.setCharacterSize(60);
    	this->enterName.setFont(this->font);
        this->enterName.setColor(sf::Color::Red);
        this->enterName.setString("Enter your Name");
		this->playerText.setPosition(500,300);
		this->playerText.setCharacterSize(40);
    	this->playerText.setFont(this->font);
        this->playerText.setColor(sf::Color::Red);
        
	}

	void NameState::HandleInput()
	{
		sf::Event event;
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
	                if(event.text.unicode == 8 && playerInput.size()>0 )
                        playerInput.pop_back();
                    else
                        playerInput +=(char)event.text.unicode;
	            }
            }
            if(this->_data->input.IsSpriteClicked(_host_button,sf::Mouse::Left,_data->window))
            {
                this->_data->machine.AddState(StateRef(new MainMenuState(_data,playerInput,false)), true);
            }
            else if(this->_data->input.IsSpriteClicked(_join_button,sf::Mouse::Left,_data->window))
            {
                this->_data->machine.AddState(StateRef(new MainMenuState(_data,playerInput,true)), true);
            }
			playerText.setString(playerInput);
        }
	}
	void NameState::Update(float dt)
	{
        
	}
	void NameState::Draw(float dt)
	{
		
		this->_data->window.clear(sf::Color(0,153,255));
		//this->_data->window.draw( this->_background );
        this->_data->window.draw( this->_join_button );
        this->_data->window.draw( this->_host_button );
        this->_data->window.draw( this->playerText);   
        this->_data->window.draw( this->enterName); 
        this->_data->window.draw( this->welcomeSprite);     
		this->_data->window.display();
	}
}