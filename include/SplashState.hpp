#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "name.h"

namespace stickman
{
	/**
	 * @brief      Class for splash state.
	 */
	class SplashState : public State
	{
	public:
		/**
		 * @brief      Constructs the object.
		 *
		 * @param[in]  data  The data which contains information about the game
		 */
		SplashState(GameDataRef data);

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

		/**
		 * A clock which can be used to do some calculations
		 */
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