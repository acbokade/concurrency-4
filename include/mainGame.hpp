#pragma once
#include "SFML/Graphics.hpp"
#include "Box2D/Box2D.h"
#include "player.h"
#include "game.h"
#include <sstream>
#include "State.hpp"
#include "Game.hpp"
#include "GameOver.h"
#include <bits/stdc++.h>
using namespace std;
#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
const float SCALE = 30.f;

namespace stickman
{
	/**
	 * @brief      Class for main game.
	 */
	class mainGame : public State
	{
	public:
		/**
		 * @brief      Constructs the object.
		 *
		 * @param[in]  data    The data which contains information about the game
		 * @param[in]  s       { parameter_description }
		 * @param[in]  client  The client
		 * @param[in]  ip      { parameter_description }
		 */
		mainGame(GameDataRef data,string s,bool client,string ip);

		/**
		 * @brief      Virtual function init that may be overloaded which runs at the start of the state
		 */
		void Init();
		/**
		 * @brief      Virtual function HandleInput that may be overloaded which may be used to handle some input
		 */
		void HandleInput();
		/**
		 * @brief      Virtual function Update which may be overloaded which may be used to update game logic
		 *
		 * @param[in]  dt    The difference in frames to syncronise with framerate
		 */
		void Update(float dt);
		/**
		 * @brief      Virtual function draw which may be overloaded which may be used to draw something on screen on each iteration
		 *
		 * @param[in]  dt    The difference in frames to syncronise with framerate
		 */
		void Draw(float dt);

	private:
		/**
		 * Takes the data of the game from the previous state
		 */
		GameDataRef _data;
		string s;
		bool client;
		sf::Sprite _title;
		string ip;
        sf::Sprite _play_button[3];
		sf::Sprite _background;
	};
}