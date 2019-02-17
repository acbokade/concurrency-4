#pragma once

#include "State.hpp"
#include "mainGame.hpp"
#include "Game.hpp"
#include <string>
#include "SFML/Graphics.hpp"
namespace stickman
{
	class NameState : public State
	{
	public:
		NameState(GameDataRef data);

        sf::Text playerText;
		sf::Font font;
		std::string playerInput;	
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