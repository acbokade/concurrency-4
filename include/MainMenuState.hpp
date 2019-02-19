#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "mainGame.hpp"
#include "Game.hpp"
#include "name.h"

namespace stickman
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data,string s,bool client);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		string playername;
		bool client;
		sf::Sprite _title;
        sf::Sprite _play_button[3];
		sf::Sprite _background;
	};
}