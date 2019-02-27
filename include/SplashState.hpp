#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "name.h"

namespace stickman
{
	class SplashState : public State
	{
	public:
		SplashState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		sf::Clock _clock;

		sf::Sprite _background;
		sf::Sprite _logo;
		sf::Sprite _Press;

		sf::Sprite _create;
		sf::Sprite _name1;
		sf::Sprite _name2;
		sf::Sprite _name3;
		sf::Sprite _name4;
	};
}