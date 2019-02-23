#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "mainGame.hpp"
#include "Game.hpp"
#include <string>
#include "name.h"

namespace stickman
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data,string s,bool client);

		sf::Text playerText;
		sf::Font font;
		std::string playerInput;	
		sf::Text text1,text2;
		void Init();
		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		string playername;
		bool client;
        sf::Sprite _enter_button;
	};
}