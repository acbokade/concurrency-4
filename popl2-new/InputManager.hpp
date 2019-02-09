#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include "SFML/Graphics.hpp"

namespace Sonar
{
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow &window);

		sf::Vector2i GetMousePosition(sf::RenderWindow &window);
	};
}
#endif
