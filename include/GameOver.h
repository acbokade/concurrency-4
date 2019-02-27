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
		 * @param[in]  data    The data which contains information about the game
		 * @param[in]  name    The name
		 * @param[in]  result  The result
		 */
		GameOver(GameDataRef data,std::string name,int result);
		/**
		 * Stores a font
		 */
		sf::Font font;
		/**
		 * Stores some text to display
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
		/**
		 * A string to store a name
		 */
		std::string name;
		/**
		 * A string to store the result
		 */
		int result;
		/**
		 * A sprite which has the play again button sprite
		 */
        sf::Sprite _play_again_button;
        /**
         * Different sprites
         */
	sf::Sprite baloon,baloon1,baloon2,baloon3,baloon4,baloon5;
	};
}
