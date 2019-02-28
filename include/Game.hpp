#pragma once

#include <memory>
#include <string>
#include "SFML/Graphics.hpp"
#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

namespace stickman
{
	/**
	 * @brief      This contains the objects required by the game as the whole like the state machine which switches states and different managers to make loading different things easier.
	 */
	struct GameData
	{
		StateMachine machine;
		sf::RenderWindow window;
		AssetManager assets;
		InputManager input;
	};

	/**
	 * Creating container for raw pointers for the struct game data 
	 */
	typedef std::shared_ptr<GameData> GameDataRef;

	/**
	 * @brief      Class for game which initializes the different properties related to the game like resolution and so on.
	 */
	class Game2
	{
	public:
		/**
		 * @brief      Creates the window with the given resolution,framerate and title while also adding the first state
		 *
		 * @param  width   The width of screen
		 * @param  height  The height of screen
		 * @param  title   The title of window screen
		 */
		Game2(int width, int height, std::string title);

	private:
		/**
		 *@brief Updates run at 60 fps
		 */
		const float dt = 1.0f / 60.0f;
		/**
		 *@brief clock for time calculations
		 */
		sf::Clock _clock;

		/**
		 *@brief Wraps the game data in a shared pointer
		 */
		GameDataRef _data = std::make_shared<GameData>();

		/**
		 * @brief      This function keeps running throughout the duration of the game
		 */
		void Run();
	};
}
