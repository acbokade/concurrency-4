#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "name.h"
#include "Game.hpp"
#include <string>

namespace stickman
{
	class HelpState : public State
	{
	public:
		HelpState(GameDataRef data);
		sf::Font font;
		sf::Text infoText,rulesText,rule1Text,rule2Text,rule3Text;
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void setText(sf::Text text,int xPos,int yPos,int size,string s);
		sf::Sprite backSprite;

	private:
		GameDataRef _data;
	};
}