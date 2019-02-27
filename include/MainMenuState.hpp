#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "mainGame.hpp"
#include "Game.hpp"
#include <string>
#include "name.h"

namespace stickman
{
	/**
	 * @brief      Class for main menu state.
	 */
	class MainMenuState : public State
	{
	public:
		/**
		 * @brief      Constructs the object.
		 *
		 * @param[in]  data    Takes the data of the game from the previous state
		 * @param[in]  s       { parameter_description }
		 * @param[in]  client  The client
		 */
		MainMenuState(GameDataRef data,string s,bool client);

		sf::Text playerText;
		sf::Font font;
		std::string playerInput;	
		sf::Text text1,text2;
		/**
		 * @brief      Virtual function init that may be overloaded which runs at the start of the state
		 */
		void Init();
		/**
		 * @brief      Virtual function HandleInput that may be overloaded which may be used to handle some input
		 */
		void HandleInput();
		/**
		 * @brief      Virtual function Update which may be overloaded which may be used to update game logic
		 *
		 * @param[in]  dt    The difference in frames to syncronise with framerate
		 */
		void Update(float dt);
		/**
		 * @brief      Virtual function draw which may be overloaded which may be used to draw something on screen on each iteration
		 *
		 * @param[in]  dt    The difference in frames to syncronise with framerate
		 */
		void Draw(float dt);

	private:
		/**
		 * Takes the data of the game from the previous state
		 */
		GameDataRef _data;
		string playername;
		bool client;
        sf::Sprite _enter_button;
	};
}