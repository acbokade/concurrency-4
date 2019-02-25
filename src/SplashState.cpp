#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "name.h"
#include <iostream>
#include <SFML/Graphics.hpp>
//#include <SFML/Keyboard.hpp>
int a=255;

namespace stickman
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}

	void SplashState::Init()
	{	
    	
		this->_data->assets.LoadTexture("Splash State Background", SPLASH_SCENE_BACKGROUND_FILEPATH);
		_background.setTexture(this->_data->assets.GetTexture("Splash State Background"),true);

		this->_data->assets.LoadTexture("Logo",SPLASH_SCENE_LOGO_FILEPATH);
		_logo.setTexture(this->_data->assets.GetTexture("Logo"),true);
		_logo.setOrigin(500.f,39.f);
    	_logo.setPosition(683.f,150.f);

    	this->_data->assets.LoadTexture("Press",SPLASH_SCENE_Press_FILEPATH);
		_Press.setTexture(this->_data->assets.GetTexture("Press"),true);
		_Press.setOrigin(500.f,39.f);
    	_Press.setPosition(683.f,250.f);

    	
	}

	void SplashState::HandleInput()
	{
		sf::Event event;

		while (this->_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
			{
				this->_data->window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
    			this->_data->machine.AddState(StateRef(new NameState(_data)),true);
			}
		}
	}

	void SplashState::Update(float dt)
	{
		//if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		//{
			// Switch To Main Menu
		//	this->_data->machine.AddState(StateRef(new NameState(_data)),true);
		//}
	}

	void SplashState::Draw(float dt)
	{
		//this->_data->window.clear(sf::Color::Black);
	
		//this->_data->window.draw(this->_logo);
		//int a=255;
    	
        	if(a<0){a=255;}
        	_Press.setColor(sf::Color(255,255,255,a));        
        	a--;
        	this->_data->window.clear(sf::Color::Black);
        	//this->_data->window.clear(sf::Color::Green);
        	this->_data->window.draw( this->_background );
       	 	this->_data->window.draw(this->_logo);
       	 	this->_data->window.draw(this->_Press);

       	 	this->_data->window.display();
    	

		//this->_data->window.display();
	}
}