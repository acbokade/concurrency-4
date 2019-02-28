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
		 * @param  data    Takes the data of the game from the previous state
		 * @param  s       Stores the name of player
		 * @param  client  Stores the information whether the system is client/server
		 */
		MainMenuState(GameDataRef data,string s,bool client);
		/**
     	* @brief  SFML text to be displayed as input is taken.
    	*/
		sf::Text playerText;
		/**
     	* @brief  SFML font to be loaded.
    	*/
		sf::Font font;
		/**
     	* @brief  String containing the ip to be connected.
    	*/
		std::string playerInput;
		/**
     	* @brief  SFML Text to be diplayed.
    	*/	
		sf::Text text1;
		/**
     	* @brief  SFML Text to be diplayed.
    	*/	
		sf::Text text2;
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
		 * @param  dt    The difference in frames to syncronise with framerate
		 */
		void Update(float dt);
		/**
		 * @brief      Virtual function draw which may be overloaded which may be used to draw something on screen on each iteration
		 *
		 * @param  dt    The difference in frames to syncronise with framerate
		 */
		void Draw(float dt);

	private:
		/**
		 *@brief Takes the data of the game from the previous state
		 */
		GameDataRef _data;
		/**
     	* @brief Stores the name of player.
    	*/
		string playername;
		/**
     	* @brief Stores whether the system is client/server.
    	*/
		bool client;
		/**
     	* @brief Sprite for enter button.
    	*/
        sf::Sprite _enter_button;
	};
}