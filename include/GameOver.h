#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "mainGame.hpp"
#include "Game.hpp"
#include <string>

namespace stickman
{
	class GameOver : public State
	{
	public:
		GameOver(GameDataRef data,std::string name,int result);
		sf::Font font;
        sf::Text gtext,gtext1;
	
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		std::string name;
		int result;
        sf::Sprite _play_again_button;
	sf::Sprite baloon,baloon1,baloon2,baloon3,baloon4,baloon5;
	};
}
