#pragma once

#include "SFML/Graphics.hpp"

namespace stickman
{
	/**
	 * @brief      Class for input manager.
	 */
	class InputManager
	{
	public:
		/**
		 * @brief      Constructs the object.
		 */
		InputManager() {}
		/**
		 * @brief      Destroys the object.
		 */
		~InputManager() {}

		/**
		 * @brief      Determines if sprite is clicked.
		 *
		 * @param[in]  object  The sprite with which we are checking
		 * @param[in]  button  The button which should be pressed
		 * @param      window  The window on which the game is running
		 *
		 * @return     True if sprite clicked, False otherwise.
		 */
		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);

		/**
		 * @brief      Gets the mouse position.
		 *
		 * @param      window  The window on which the game is running
		 *
		 * @return     The mouse position.
		 */
		sf::Vector2i GetMousePosition(sf::RenderWindow &window);
	};
}
