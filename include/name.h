#pragma once

#include "State.hpp"
#include "mainGame.hpp"
#include <HelpState.hpp>
#include "Game.hpp"
#include <string>
#include "SFML/Graphics.hpp"
namespace stickman
{
	/**
	 * @brief      Class for name state which takes the name of player and gives the option
	 *             of chosing whether to host a server/ join a server.
	 */
	class NameState : public State
	{
	public:
		/**
		 * @brief      Constructs the object.
		 *
		 * @param  data    Takes the data of the game from the previous state
		 */
		NameState(GameDataRef data);
		/*
		* @brief SFML text of "enter the name".
		*/
		sf::Text enterName;
		/*
		* @brief SFML Texture to be loaded.
		*/
		sf::Texture welcomeTexture;
		/*
		* @brief SFML sprite for welcome image.
		*/
		sf::Sprite welcomeSprite;
		/*
		* @brief SFML text which is displayed as input is taken.
		*/
        sf::Text playerText;
        /*
		* @brief SFML Font to be loaded.
		*/
		sf::Font font;
		/*
		* @brief Stores the player's name.
		*/
		std::string playerInput;	
		/**
		 * @brief      Virtual function init that may be overloaded which runs at the start of the state
		 */
		void Init();
		/**
		* @brief      Virtual function HandleInput that may be overloaded which may be used to handle some input
		*/
		void HandleInput();
		/**
		 * @brief      Virtual function draw which may be overloaded which may be used to draw something on screen on each iteration
		 *
		 * @param  dt    The difference in frames to syncronise with framerate
		 */
		void Draw(float dt);
		/**
		 * @brief      Virtual function Update which may be overloaded which may be used to update game logic
		 *
		 * @param  dt    The difference in frames to syncronise with framerate
		 */
		void Update(float dt);

	private:
		/**
		 *@brief Takes the data of the game from the previous state
		 */
		GameDataRef _data;
		/**
		 *@brief SFML sprite for host button.
		 */
        sf::Sprite _host_button;
        /**
		 *@brief SFML sprite for join button.
		 */
        sf::Sprite _join_button;
        /**
		 *@brief SFML sprite for help button.
		 */
        sf::Sprite _help_button;
	};
}