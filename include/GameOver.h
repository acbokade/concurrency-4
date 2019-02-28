#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "mainGame.hpp"
#include "Game.hpp"
#include <string>

namespace stickman
{
	/**
	 * @brief      Class for game over state.
	 */
	class GameOver : public State
	{
	public:
		/**
		 * @brief      Constructs the object.
		 *
		 * @param  data    The data which contains information about the game
		 * @param  name    Stores the name of winner
		 * @param  result  Stores the result if there is a win / tie.
		 */
		GameOver(GameDataRef data,std::string name,int result);
		/**
		 * Stores a font
		 */
		sf::Font font;
		/**
		 * Stores text to be displayed
		 */
        sf::Text gtext,gtext1;
	
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
		 *@brief A string to store a name
		 */
		std::string name;
		/**
		 *@brief A string to store the result
		 */
		int result;
		/**
		 *@brief A sprite which has the play again button sprite
		 */
        sf::Sprite _play_again_button;
        /**
         *@brief Different sprites for baloons to be diplayed
         */
	sf::Sprite baloon,baloon1,baloon2,baloon3,baloon4,baloon5;
	};
}
