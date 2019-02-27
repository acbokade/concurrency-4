#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "name.h"
#include "Game.hpp"
#include <string>

namespace stickman
{
	/**
	 * @brief      Class for help state.
	 */
	class HelpState : public State
	{
	public:
		/**
		 * @brief      Constructs the object.
		 *
		 * @param[in]  data  The data which contains information about the game
		 */
		HelpState(GameDataRef data);
		/**
		 * Stores a font
		 */
		sf::Font font;
		/**
		 * Stores some text to display
		 */
		sf::Text infoText,rulesText,rule1Text,rule2Text,rule3Text;
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
		/**
		 * @brief      Sets the text onto a particular position
		 *
		 * @param[in]  text  The text
		 * @param[in]  xPos  The x position
		 * @param[in]  yPos  The y position
		 * @param[in]  size  The size
		 * @param[in]  s     { parameter_description }
		 */
		void setText(sf::Text text,int xPos,int yPos,int size,string s);
		/**
		 * Sprite which stores the backsprite
		 */
		sf::Sprite backSprite;

	private:
		/**
		 * Takes the data of the game from the previous state
		 */
		GameDataRef _data;
	};
}