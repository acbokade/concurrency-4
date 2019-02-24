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
		sf::Text enterName;
		sf::Texture welcomeTexture;
		sf::Sprite welcomeSprite;
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
        sf::Sprite _host_button;
        sf::Sprite _join_button;
        sf::Sprite _help_button;
		sf::Sprite _background;
	};
}