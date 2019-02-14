#pragma once
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "player.h"
#include "game.h"
#include <sstream>
#include "State.hpp"
#include "Game.hpp"
#include <bits/stdc++.h>
using namespace std;
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
const float SCALE = 30.f;

namespace stickman
{
	class mainGame : public State
	{
	public:
		mainGame(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;
		sf::Sprite _title;
        sf::Sprite _play_button[3];
		sf::Sprite _background;
	};
}