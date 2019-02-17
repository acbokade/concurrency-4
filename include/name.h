#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "mainGame.hpp"
#include "Game.hpp"

namespace stickman
{
	class NameState : public State
	{
	public:
		NameState(GameDataRef data);

		sf::String playerInput;
        sf::Text playerText;
		void Init();
		void HandleInput();
		void Draw(float dt);
		void Update(float dt);

	private:
		GameDataRef _data;
		sf::Sprite _title;
        sf::Sprite _submit_button;
		sf::Sprite _background;
	};
}