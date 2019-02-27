#include <sstream>
#include "SplashState.hpp"
#include "DEFINITIONS.hpp"
#include "MainMenuState.hpp"
#include "name.h"
#include <iostream>
#include <SFML/Graphics.hpp>
//#include <SFML/Keyboard.hpp>
int a=255;
//splash name mainmenustate gameover splashstate.h definition gameover.h
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
		_logo.setColor(sf::Color(245,255,250));
    	_logo.setPosition(683.f,150.f);

    	this->_data->assets.LoadTexture("Press",SPLASH_SCENE_Press_FILEPATH);
		_Press.setTexture(this->_data->assets.GetTexture("Press"),true);
		_Press.setOrigin(500.f,39.f);
    	_Press.setPosition(683.f,250.f);

    	this->_data->assets.LoadTexture("Create",SPLASH_SCENE_CREATE_FILEPATH);
		_create.setTexture(this->_data->assets.GetTexture("Create"),true);
		_create.setOrigin(150.f,10.f);
    	_create.setPosition(683.f,525.f);

    	this->_data->assets.LoadTexture("name1",SPLASH_SCENE_NAME1_FILEPATH);
		_name1.setTexture(this->_data->assets.GetTexture("name1"),true);
		_name1.setOrigin(100.f,10.f);
    	_name1.setPosition(683.f,555.f);

    	this->_data->assets.LoadTexture("name2",SPLASH_SCENE_NAME2_FILEPATH);
		_name2.setTexture(this->_data->assets.GetTexture("name2"),true);
		_name2.setOrigin(100.f,10.f);
    	_name2.setPosition(683.f,580.f);

    	this->_data->assets.LoadTexture("name3",SPLASH_SCENE_NAME3_FILEPATH);
		_name3.setTexture(this->_data->assets.GetTexture("name3"),true);
		_name3.setOrigin(100.f,10.f);
    	_name3.setPosition(683.f,605.f);

    	this->_data->assets.LoadTexture("name4",SPLASH_SCENE_NAME4_FILEPATH);
		_name4.setTexture(this->_data->assets.GetTexture("name4"),true);
		_name4.setOrigin(100.f,10.f);
    	_name4.setPosition(683.f,630.f);
    	
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
        	this->_data->window.clear(sf::Color::White);
        	//this->_data->window.clear(sf::Color::Green);
        	this->_data->window.draw( this->_background );
       	 	this->_data->window.draw(this->_logo);
       	 	this->_data->window.draw(this->_Press);
       	 	this->_data->window.draw(this->_create);
       	 	this->_data->window.draw(this->_name1);
       	 	this->_data->window.draw(this->_name2);
       	 	this->_data->window.draw(this->_name3);
       	 	this->_data->window.draw(this->_name4);

       	 	this->_data->window.display();
    	

		//this->_data->window.display();
	}
}