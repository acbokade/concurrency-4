#include <sstream>
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace stickman
{
	MainMenuState::MainMenuState(GameDataRef data,string s,bool client) : _data(data)
	{
		this->playername=s;
		this->client=client;
	}

	void MainMenuState::Init()
	{
		/*this->_data->assets.LoadTexture("Main Menu Background", MAIN_MENU_BACKGROUND_FILEPATH);
        this->_data->assets.LoadTexture("Game Title", GAME_TITLE_FILEPATH);
        this->_data->assets.LoadTexture("Play Button", PLAY_BUTTON_1_FILEPATH);
        
		this->_background.setTexture(this->_data->assets.GetTexture("Main Menu Background"),true);
        this->_title.setTexture(this->_data->assets.GetTexture("Game Title"));
        this->_title.setPosition((SCREEN_WIDTH/2)-(_title.getGlobalBounds().width/2),_title.getGlobalBounds().height/4);*/
        
        this->font.loadFromFile("res/arial.ttf");
    	this->text1.setPosition(420,180);
		this->text1.setCharacterSize(60);
    	this->text1.setFont(this->font);
        this->text1.setColor(sf::Color::Red);
        this->_enter_button.setTexture(this->_data->assets.GetTexture("Play Button"));
        this->_enter_button.setPosition(550,400);
        if(this->client==false)
        	{
        		this->text1.setString("Your IP Address is : ");
        		sf::IpAddress ip;
        		ip = sf::IpAddress::getLocalAddress();
        		std::string myip = ip.toString();
        		this->text2.setString(myip); 
        	}
        else
        	this->text1.setString("Enter the IP Address : ");
		this->text2.setPosition(500,300);
		this->text2.setCharacterSize(40);
		this->text2.setFont(this->font);
    	this->text2.setColor(sf::Color::Red);
        
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
			if(this->client)
			{		
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
	            if(this->_data->input.IsSpriteClicked(_enter_button,sf::Mouse::Left,_data->window))
	            {
	                this->_data->machine.AddState(StateRef(new mainGame(_data,this->playername,this->client,this->playerInput)), true);
	            }
				text2.setString(playerInput);
            }
            else
            {
            	this->_data->machine.AddState(StateRef(new mainGame(_data,this->playername,this->client,"noip")), true);
            }
		}
	}

	void MainMenuState::Update(float dt)
	{
        
	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear(sf::Color::Blue);

		//this->_data->window.draw( this->_background );
        this->_data->window.draw( this->text1);
        this->_data->window.draw( this->text2);
        if(this->client)
        	this->_data->window.draw( this->_enter_button );

		this->_data->window.display();
	}
}