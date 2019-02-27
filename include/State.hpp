#pragma once

namespace stickman
{
	/**
	 * @brief      Class for state which has functions which can be overloaded so that a particular state of the game can run using these functions.
	 */
	class State
	{
	public:
		/**
		 * @brief      A virtual fucntion which runs at the start when a state is loaded
		 */
		virtual void Init() = 0;

		/**
		 * @brief      A virtual function which may be used to handle input during each iteration
		 */
		virtual void HandleInput() = 0;
		/**
		 * @brief      A virtual funciton which may be used to update game logic
		 *
		 * @param[in]  dt    The difference in frames to syncronise with framerate
		 */
		virtual void Update(float dt) = 0;
		/**
		 * @brief      A virtual function which may be used to draw objects
		 *
		 * @param[in]  dt    The difference in frames to syncronise with framerate
		 */
		virtual void Draw(float dt) = 0;

		/**
		 * @brief      A function which may be used to pause a state
		 */
		virtual void Pause() { }
		/**
		 * @brief      A function which may be used to resume a state
		 */
		virtual void Resume() { }
	};
}